/*
 * (C) Copyright 2003
 * Kyle Harris, kharris@nexus-tech.net
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
#include <command.h>
#include <asm/io.h>
#include <malloc.h>
#include <initcall.h>
#include <version.h>

int do_ls(int argc, char *argv[]) {
  printf("%s\n", BMS_COMMIT_ID);
  printf("%s\n", BMS_COMPILE_INFO);
  return 0;
}

int do_reset(int argc, char *argv[]) {
  // system_reset();
  return 0;
}

int do_time(int argc, char *argv[]) {
  int i  = 0x3fffffff;
  int t0 = 0, t1;
  while (i--) {
    t1 = get_timer(0);
    if (t1 - t0 > 1000) {
      printf("ms: %d\n", t1);
      t0 = t1;
    }
  }
  return 0;
}

int do_ml(int argc, char *argv[]) {
  __sOINFo();
  return 0;
}

int do_sleep(int argc, char *argv[]) {
  unsigned long sec = simple_strtoul(argv[1], NULL, 10);
  udelay(sec * 1000000);
  printf("sleep OK.\n");
  return 0;
}

#if 0
int do_pads(int argc, char *argv[])
{
	int id1, st, id2, i;
	if(argc < 3) {
		printf("pads sub-command index\n");
		return 0;
	}

	id1 = simple_strtoul(argv[2], NULL, 10);
	id2 = id1;

	if(argc > 3)
	  id2 = simple_strtoul(argv[3], NULL, 10);

	if(id1 < 0 || id2 < 0) {
		printf("valid pads index range from 0 to ~.\n");
		return 0;
	}

	for(i = id1; i <= id2; i++) {
		if(strncmp(argv[1], "in", 2) == 0) {
			pads_chmod(i, PADS_MODE_IN, 0);
			printf("pads(%d) level: %d\n", i, pads_getpin(i));
		}
		else if(strncmp(argv[1], "high", 4) == 0)
		  pads_chmod(i, PADS_MODE_OUT, 1);
		else if(strncmp(argv[1], "low", 3) == 0)
		  pads_chmod(i, PADS_MODE_OUT, 0);
		else if(strncmp(argv[1], "func", 4) == 0)
		  pads_chmod(i, PADS_MODE_CTRL, 0);
		else if(strncmp(argv[1], "st", 2) == 0) {
			st = pads_states(i);
			printf("pads(%d) states: %s\n", i,
						st? ((st == 1)? "in": "out")
						: "function");
		} else {
			printf("unsupported sub-command\n");
			return 0;
		}
	}

	return 0;
}
#endif

void command_skeleton_init(void) {
  register_command("ls", do_ls);
  register_command("reset", do_reset);
  register_command("ml", do_ml);
  register_command("sleep", do_sleep);
  register_command("time", do_time);
  // register_command("pads", do_pads);
}

module_init(command_skeleton_init);
