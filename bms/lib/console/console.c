/*
 * (C) Copyright 2000
 * Paolo Scaffardi, AIRVENT SAM s.p.a - RIMINI(ITALY), arsenio@tin.it
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

#include <common.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <exports.h>
#include <console.h>

int getc(void) {
  /* Send directly to the handler */
  return console_getc();
}

int tstc(void) {
  /* Send directly to the handler */
  return console_tstc();
}

void putc(const char c) {
  /* Send directly to the handler */
  console_putc(c);
}

static int puts_enabled = 1;
void puts_enable(int en) { puts_enabled = !!en; }

void puts(const char *s) {
  if (!puts_enabled)
    return;

  /* Send directly to the handler */
  console_puts(s);
}

char *gets_s(char *s, int len) {
  char *p = s;
  int i;

  for (i = 0; i < len; i++) {
    *p = getc();
    putc(*p);
    if (*p == '\r' || *p == '\n') {
      *p = '\0';
      break;
    }
    p++;
  }
  *p = '\0';

  return s;
}

void vprintf(const char *fmt, va_list args) {
  uint i;
  char printbuffer[CONFIG_SYS_PBSIZE];
  (void)i;
  /* For this to work, printbuffer must be larger than
   * anything we ever want to print.
   */
  i = vsprintf(printbuffer, fmt, args);

  /* Print the string */
  puts(printbuffer);
}

/* test if ctrl-c was pressed */
static int ctrlc_disabled    = 0; /* see disable_ctrl() */
static int ctrlc_was_pressed = 0;
int ctrlc(void) {
  if (!ctrlc_disabled) {
    if (tstc()) {
      switch (getc()) {
      case 0x03: /* ^C - Control C */
        ctrlc_was_pressed = 1;
        return 1;
      default:
        break;
      }
    }
  }
  return 0;
}

/* pass 1 to disable ctrlc() checking, 0 to enable.
 * returns previous state
 */
int disable_ctrlc(int disable) {
  int prev = ctrlc_disabled; /* save previous state */

  ctrlc_disabled = disable;
  return prev;
}

int had_ctrlc(void) { return ctrlc_was_pressed; }

void clear_ctrlc(void) { ctrlc_was_pressed = 0; }

inline void dbg(const char *fmt, ...) {}
