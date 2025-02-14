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
#include <command.h>
#include <malloc.h>
#include <post.h>
#include <initcall.h>
#include <linux/list.h>

#define MAX_CMD_NAME 16

struct command_node {
  const char *cmd;
  int (*entry)(int argc, char *argv[]);
  struct list_head list;
} cmd_pool;

int register_command(const char *cmd, void *entry) {
  struct command_node *c;

  if (!cmd || !entry)
    return -1;

  c = malloc(sizeof(struct command_node));

  if (!c)
    return -2;

  c->cmd   = cmd;
  c->entry = entry;

  list_add_tail(&c->list, &cmd_pool.list);

  //	printf("registered command: %s\n", cmd);
  return 0;
}

int run_command(const char *cmd, int argc, char *argv[]) {
  struct command_node *c;

  list_for_each_entry(c, &cmd_pool.list, list) {
    if (strncmp(c->cmd, cmd, MAX_CMD_NAME) == 0)
      return c->entry(argc, argv);
  }

  printf("no command '%s' found\n", cmd);
  return 0;
}

int command_show(int argc, char *argvp[]) {
  struct command_node *c;
  int count = 1;

  list_for_each_entry(c, &cmd_pool.list, list) {
    printf("%16s", c->cmd);
    if (count % 5)
      printf("\n");

    count++;
  }

  return 0;
}

void command_init(void) {
  INIT_LIST_HEAD(&cmd_pool.list);

  /* register the first command */
  register_command("help", command_show);
}

core_init(command_init);

/****************************************************************************/

static void process_macros(const char *input, char *output) {
  char c, prev;
  const char *varname_start = NULL;
  int inputcnt              = strlen(input);
  int outputcnt             = CONFIG_SYS_CBSIZE;
  int state                 = 0; /* 0 = waiting for '$'  */

  /* 1 = waiting for '(' or '{' */
  /* 2 = waiting for ')' or '}' */
  /* 3 = waiting for '''  */
#ifdef DEBUG_PARSER
  char *output_start = output;

  printf("[PROCESS_MACROS] INPUT len %d: \"%s\"\n", strlen(input), input);
#endif

  prev = '\0'; /* previous character   */

  while (inputcnt && outputcnt) {
    c = *input++;
    inputcnt--;

    if (state != 3) {
      /* remove one level of escape characters */
      if ((c == '\\') && (prev != '\\')) {
        if (inputcnt-- == 0)
          break;
        prev = c;
        c    = *input++;
      }
    }

    switch (state) {
    case 0: /* Waiting for (unescaped) $    */
      if ((c == '\'') && (prev != '\\')) {
        state = 3;
        break;
      }
      if ((c == '$') && (prev != '\\')) {
        state++;
      } else {
        *(output++) = c;
        outputcnt--;
      }
      break;
    case 1: /* Waiting for (        */
      if (c == '(' || c == '{') {
        state++;
        varname_start = input;
      } else {
        state       = 0;
        *(output++) = '$';
        outputcnt--;

        if (outputcnt) {
          *(output++) = c;
          outputcnt--;
        }
      }
      break;
    case 2: /* Waiting for )        */
      if (c == ')' || c == '}') {
        int i;
        char envname[CONFIG_SYS_CBSIZE], *envval;
        int envcnt = input - varname_start - 1; /* Varname # of chars */

        /* Get the varname */
        for (i = 0; i < envcnt; i++) {
          envname[i] = varname_start[i];
        }
        envname[i] = 0;
        (void)envname;

        /* Get its value */
        //				envval = getenv (envname);
        envval = NULL;

        /* Copy into the line if it exists */
        if (envval != NULL)
          while ((*envval) && outputcnt) {
            *(output++) = *(envval++);
            outputcnt--;
          }
        /* Look for another '$' */
        state = 0;
      }
      break;
    case 3: /* Waiting for '        */
      if ((c == '\'') && (prev != '\\')) {
        state = 0;
      } else {
        *(output++) = c;
        outputcnt--;
      }
      break;
    }
    prev = c;
  }

  if (outputcnt)
    *output = 0;
  else
    *(output - 1) = 0;

#ifdef DEBUG_PARSER
  printf("[PROCESS_MACROS] OUTPUT len %d: \"%s\"\n", strlen(output_start),
         output_start);
#endif
}

/****************************************************************************
 * returns:
 *	1  - command executed, repeatable
 *	0  - command executed but not repeatable, interrupted commands are
 *	     always considered not repeatable
 *	-1 - not executed (unrecognized, bootd recursion or too many args)
 *           (If cmd is NULL or "" or longer than CONFIG_SYS_CBSIZE-1 it is
 *           considered unrecognized)
 *
 * WARNING:
 *
 * We must create a temporary copy of the command since the command we get
 * may be the result from getenv(), which returns a pointer directly to
 * the environment data, which may change magicly when the command we run
 * creates or modifies environment variables (like "bootp" does).
 */

int parse_command(const char *cmd, int flag) {
  char cmdbuf[CONFIG_SYS_CBSIZE]; /* working copy of cmd		*/
  char *token;                    /* start of token in cmdbuf	*/
  char *sep;                      /* end of token (separator) in cmdbuf */
  char finaltoken[CONFIG_SYS_CBSIZE];
  char *str = cmdbuf;
  char *argv[CONFIG_SYS_MAXARGS + 1]; /* NULL terminated	*/
  int argc, inquotes;
  int rc = 1;

  clear_ctrlc(); /* forget any previous Control C */

  if (!cmd || !*cmd) {
    return -1; /* empty command */
  }

  if (strlen(cmd) >= CONFIG_SYS_CBSIZE) {
    puts("## Command too long!\n");
    return -1;
  }

  strcpy(cmdbuf, cmd);

  /* Process separators and check for invalid
   * repeatable commands
   */
  while (*str) {

    /*
     * Find separator, or string end
     * Allow simple escape of ';' by writing "\;"
     */
    for (inquotes = 0, sep = str; *sep; sep++) {
      if ((*sep == '\'') && (*(sep - 1) != '\\'))
        inquotes = !inquotes;

      if (!inquotes && (*sep == ';') && /* separator		*/
          (sep != str) &&               /* past string start	*/
          (*(sep - 1) != '\\'))         /* and NOT escaped	*/
        break;
    }

    /*
     * Limit the token to data between separators
     */
    token = str;
    if (*sep) {
      str  = sep + 1; /* start of command for next pass */
      *sep = '\0';
    } else
      str = sep; /* no more commands for next pass */

    /* find macros in this token and replace them */
    process_macros(token, finaltoken);

    /* Extract arguments */
    if ((argc = parse_line(finaltoken, argv)) == 0) {
      rc = -1; /* no command at all */
      continue;
    }

    /* Try testbench command */
    rc = run_command(argv[0], argc, argv);

    /* Did the user stop this? */
    if (had_ctrlc())
      return -1; /* if stopped then not repeatable */
  }

  return rc;
}

/****************************************************************************/
