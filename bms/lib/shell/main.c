/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Add to readline cmdline-editing by
 * (C) Copyright 2005
 * JinHua Luo, GuangDong Linux Center, <luo.jinhua@gd-linux.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* #define	DEBUG	*/

#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <testbench.h>

#include <post.h>

char console_buffer[CONFIG_SYS_CBSIZE]; /* console I/O buffer	*/

void main_loop(void) {
  int len;
  /*
   * Main Loop for Monitor Command Processing
   */
  for (;;) {
    len = readline(CONFIG_SYS_PROMPT);

    if (len == -1)
      puts("\n");
    else if (len > 0)
      parse_command(console_buffer, 0);
  }
}

/*
 * cmdline-editing related codes from vivi.
 * Author: Janghoon Lyu <nandy@mizi.com>
 */

#define putnstr(str, n)                                                        \
  do {                                                                         \
    printf("%.*s", (int)n, str);                                               \
  } while (0)

#define CTL_CH(c) ((c) - 'a' + 1)

#define MAX_CMDBUF_SIZE 256

#define CTL_BACKSPACE   ('\b')
#define DEL             ((char)255)
#define DEL7            ((char)127)
#define CREAD_HIST_CHAR ('!')

#define getcmd_putch(ch) putc(ch)
#define getcmd_getch()   getc()
#define getcmd_cbeep()   getcmd_putch('\a')

#define HIST_MAX  4
#define HIST_SIZE MAX_CMDBUF_SIZE

static int hist_max     = 0;
static int hist_add_idx = 0;
static int hist_cur     = -1;
unsigned hist_num       = 0;

char *hist_list[HIST_MAX];
char hist_lines[HIST_MAX][HIST_SIZE];

static void hist_init(void) {
  int i;

  hist_max     = 0;
  hist_add_idx = 0;
  hist_cur     = -1;
  hist_num     = 0;

  for (i = 0; i < HIST_MAX; i++) {
    hist_list[i]    = hist_lines[i];
    hist_list[i][0] = '\0';
  }
}

static void cread_add_to_hist(char *line) {
  strcpy(hist_list[hist_add_idx], line);

  if (++hist_add_idx >= HIST_MAX)
    hist_add_idx = 0;

  if (hist_add_idx > hist_max)
    hist_max = hist_add_idx;

  hist_num++;
}

static char *hist_prev(void) {
  char *ret;
  int old_cur;

  if (hist_cur < 0)
    return NULL;

  old_cur = hist_cur;
  if (--hist_cur < 0)
    hist_cur = hist_max;

  if (hist_cur == hist_add_idx) {
    hist_cur = old_cur;
    ret      = NULL;
  } else
    ret = hist_list[hist_cur];

  return (ret);
}

static char *hist_next(void) {
  char *ret;

  if (hist_cur < 0)
    return NULL;

  if (hist_cur == hist_add_idx)
    return NULL;

  if (++hist_cur > hist_max)
    hist_cur = 0;

  if (hist_cur == hist_add_idx) {
    ret = "";
  } else
    ret = hist_list[hist_cur];

  return (ret);
}

#define BEGINNING_OF_LINE()                                                    \
  {                                                                            \
    while (num) {                                                              \
      getcmd_putch(CTL_BACKSPACE);                                             \
      num--;                                                                   \
    }                                                                          \
  }

#define ERASE_TO_EOL()                                                         \
  {                                                                            \
    if (num < eol_num) {                                                       \
      int tmp;                                                                 \
      for (tmp = num; tmp < eol_num; tmp++)                                    \
        getcmd_putch(' ');                                                     \
      while (tmp-- > num)                                                      \
        getcmd_putch(CTL_BACKSPACE);                                           \
      eol_num = num;                                                           \
    }                                                                          \
  }

#define REFRESH_TO_EOL()                                                       \
  {                                                                            \
    if (num < eol_num) {                                                       \
      wlen = eol_num - num;                                                    \
      putnstr(buf + num, wlen);                                                \
      num = eol_num;                                                           \
    }                                                                          \
  }

static void cread_add_char(char ichar, int insert, unsigned long *num,
                           unsigned long *eol_num, char *buf,
                           unsigned long len) {
  unsigned long wlen;

  /* room ??? */
  if (insert || *num == *eol_num) {
    if (*eol_num > len - 1) {
      getcmd_cbeep();
      return;
    }
    (*eol_num)++;
  }

  if (insert) {
    wlen = *eol_num - *num;
    if (wlen > 1) {
      memmove(&buf[*num + 1], &buf[*num], wlen - 1);
    }

    buf[*num] = ichar;
    putnstr(buf + *num, wlen);
    (*num)++;
    while (--wlen) {
      getcmd_putch(CTL_BACKSPACE);
    }
  } else {
    /* echo the character */
    wlen      = 1;
    buf[*num] = ichar;
    putnstr(buf + *num, wlen);
    (*num)++;
  }
}

static void cread_add_str(char *str, int strsize, int insert,
                          unsigned long *num, unsigned long *eol_num, char *buf,
                          unsigned long len) {
  while (strsize--) {
    cread_add_char(*str, insert, num, eol_num, buf, len);
    str++;
  }
}

static int cread_line(const char *const prompt, char *buf, unsigned int *len) {
  unsigned long num     = 0;
  unsigned long eol_num = 0;
  unsigned long rlen;
  unsigned long wlen;
  char ichar;
  int insert  = 1;
  int esc_len = 0;
  int rc      = 0;
  char esc_save[8];
  (void)rlen;

  while (1) {
    rlen  = 1;
    ichar = getcmd_getch();

    if ((ichar == '\n') || (ichar == '\r')) {
      printf("\n");
      break;
    }

    /*
     * handle standard linux xterm esc sequences for arrow key, etc.
     */
    if (esc_len != 0) {
      if (esc_len == 1) {
        if (ichar == '[') {
          esc_save[esc_len] = ichar;
          esc_len           = 2;
        } else {
          cread_add_str(esc_save, esc_len, insert, &num, &eol_num, buf, *len);
          esc_len = 0;
        }
        continue;
      }

      switch (ichar) {

      case 'D': /* <- key */
        ichar   = CTL_CH('b');
        esc_len = 0;
        break;
      case 'C': /* -> key */
        ichar   = CTL_CH('f');
        esc_len = 0;
        break;  /* pass off to ^F handler */
      case 'H': /* Home key */
        ichar   = CTL_CH('a');
        esc_len = 0;
        break;  /* pass off to ^A handler */
      case 'A': /* up arrow */
        ichar   = CTL_CH('p');
        esc_len = 0;
        break;  /* pass off to ^P handler */
      case 'B': /* down arrow */
        ichar   = CTL_CH('n');
        esc_len = 0;
        break; /* pass off to ^N handler */
      default:
        esc_save[esc_len++] = ichar;
        cread_add_str(esc_save, esc_len, insert, &num, &eol_num, buf, *len);
        esc_len = 0;
        continue;
      }
    }

    switch (ichar) {
    case 0x1b:
      if (esc_len == 0) {
        esc_save[esc_len] = ichar;
        esc_len           = 1;
      } else {
        puts("impossible condition #876\n");
        esc_len = 0;
      }
      break;

    case CTL_CH('a'):
      BEGINNING_OF_LINE();
      break;
    case CTL_CH('c'): /* ^C - break */
      *buf = '\0';    /* discard input */
      return (-1);
    case CTL_CH('f'):
      if (num < eol_num) {
        getcmd_putch(buf[num]);
        num++;
      }
      break;
    case CTL_CH('b'):
      if (num) {
        getcmd_putch(CTL_BACKSPACE);
        num--;
      }
      break;
    case CTL_CH('d'):
      if (num < eol_num) {
        wlen = eol_num - num - 1;
        if (wlen) {
          memmove(&buf[num], &buf[num + 1], wlen);
          putnstr(buf + num, wlen);
        }

        getcmd_putch(' ');
        do {
          getcmd_putch(CTL_BACKSPACE);
        } while (wlen--);
        eol_num--;
      }
      break;
    case CTL_CH('k'):
      ERASE_TO_EOL();
      break;
    case CTL_CH('e'):
      REFRESH_TO_EOL();
      break;
    case CTL_CH('o'):
      insert = !insert;
      break;
    case CTL_CH('x'):
    case CTL_CH('u'):
      BEGINNING_OF_LINE();
      ERASE_TO_EOL();
      break;
    case DEL:
    case DEL7:
    case 8:
      if (num) {
        wlen = eol_num - num;
        num--;
        memmove(&buf[num], &buf[num + 1], wlen);
        getcmd_putch(CTL_BACKSPACE);
        putnstr(buf + num, wlen);
        getcmd_putch(' ');
        do {
          getcmd_putch(CTL_BACKSPACE);
        } while (wlen--);
        eol_num--;
      }
      break;
    case CTL_CH('p'):
    case CTL_CH('n'): {
      char *hline;

      esc_len = 0;

      if (ichar == CTL_CH('p'))
        hline = hist_prev();
      else
        hline = hist_next();

      if (!hline) {
        getcmd_cbeep();
        continue;
      }

      /* nuke the current line */
      /* first, go home */
      BEGINNING_OF_LINE();

      /* erase to end of line */
      ERASE_TO_EOL();

      /* copy new line into place and display */
      strcpy(buf, hline);
      eol_num = strlen(buf);
      REFRESH_TO_EOL();
      continue;
    }
    default:
      cread_add_char(ichar, insert, &num, &eol_num, buf, *len);
      break;
    }
  }
  *len         = eol_num;
  buf[eol_num] = '\0'; /* lose the newline */

  if (buf[0] && buf[0] != CREAD_HIST_CHAR)
    cread_add_to_hist(buf);
  hist_cur = hist_add_idx;

  return (rc);
}

/****************************************************************************/

/*
 * Prompt for input and read a line.
 * If  CONFIG_BOOT_RETRY_TIME is defined and retry_time >= 0,
 * time out when time goes past endtime (timebase time in ticks).
 * Return:	number of read characters
 *		-1 if break
 *		-2 if timed out
 */
int readline(const char *const prompt) {
  return readline_into_buffer(prompt, console_buffer);
}

int readline_into_buffer(const char *const prompt, char *buffer) {
  char *p          = buffer;
  unsigned int len = MAX_CMDBUF_SIZE;
  int rc;
  static int initted = 0;

  /*
   * History uses a global array which is not
   * writable until after relocation to RAM.
   * Revert to non-history version if still
   * running from flash.
   */
  if (!initted) {
    hist_init();
    initted = 1;
  }

  puts(prompt);

  rc = cread_line(prompt, p, &len);
  return rc < 0 ? rc : len;
}

/****************************************************************************/

/****************************************************************************/

int parse_line(char *line, char *argv[]) {
  int nargs = 0;

#ifdef DEBUG_PARSER
  printf("parse_line: \"%s\"\n", line);
#endif
  while (nargs < CONFIG_SYS_MAXARGS) {

    /* skip any white space */
    while ((*line == ' ') || (*line == '\t')) {
      ++line;
    }

    if (*line == '\0') { /* end of line, no more args	*/
      argv[nargs] = NULL;
#ifdef DEBUG_PARSER
      printf("parse_line: nargs=%d\n", nargs);
#endif
      return (nargs);
    }

    argv[nargs++] = line; /* begin of argument string	*/

    /* find end of string */
    while (*line && (*line != ' ') && (*line != '\t')) {
      ++line;
    }

    if (*line == '\0') { /* end of line, no more args	*/
      argv[nargs] = NULL;
#ifdef DEBUG_PARSER
      printf("parse_line: nargs=%d\n", nargs);
#endif
      return (nargs);
    }

    *line++ = '\0'; /* terminate current arg	 */
  }

  printf("** Too many args (max. %d) **\n", CONFIG_SYS_MAXARGS);

#ifdef DEBUG_PARSER
  printf("parse_line: nargs=%d\n", nargs);
#endif
  return (nargs);
}
