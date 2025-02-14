/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

/*
 * Memory Functions
 *
 * Copied from FADS ROM, Dan Malek (dmalek@jlc.net)
 */

#include <common.h>
#include <command.h>
#include <initcall.h>

#define MEM_DEFAULT_LEN 160
int do_mem_md(int argc, char *argv[]) {
  ulong addr = 0, length = MEM_DEFAULT_LEN;

  if (argc < 2) {
    printf("memory display\n"
           "md address length\n");
    return 1;
  }

  /* Address is specified since argc > 1
   */
  addr = simple_strtoul(argv[1], NULL, 16);

  /* If another parameter, it is the length to display.
   * Length is the number of objects, not number of bytes.
   */
  if (argc > 2)
    length = simple_strtoul(argv[2], NULL, 16);

  /* Print the lines. */
  print_buffer(addr, (void *)addr, 4, length / 4, 4);

  return 0;
}

int do_mem_mw(int argc, char *argv[]) {
  ulong addr, writeval, count;

  if ((argc < 3) || (argc > 4)) {
    printf("memory write (fill)\n"
           "mw address value length\n");
    return 1;
  }

  /* Address is specified since argc > 1
   */
  addr = simple_strtoul(argv[1], NULL, 16);

  /* Get the value to write.
   */
  writeval = simple_strtoul(argv[2], NULL, 16);

  /* Count ? */
  if (argc == 4) {
    count = simple_strtoul(argv[3], NULL, 16);
  } else {
    count = 1;
  }

  while (count-- > 0) {
    *((ulong *)addr) = (ulong)writeval;
    addr += 4;
  }

  return 0;
}

int do_mem_cmp(int argc, char *argv[]) {
  ulong addr1, addr2, length, ngood, count;
  int rcode = 0;

  if (argc != 4) {
    printf("memory compare\n"
           "cmp addr1 addr2 length\n");
    return 1;
  }

  addr1  = simple_strtoul(argv[1], NULL, 16);
  addr2  = simple_strtoul(argv[2], NULL, 16);
  length = simple_strtoul(argv[3], NULL, 16);
  count  = ((length + 3) & ~3) / 4;

  ngood = 0;

  while (count-- > 0) {
    ulong word1 = *(ulong *)addr1;
    ulong word2 = *(ulong *)addr2;
    if (word1 != word2) {
      printf("word at 0x%08lx (0x%08lx) "
             "!= word at 0x%08lx (0x%08lx)\n",
             addr1, word1, addr2, word2);
      rcode = 1;
      break;
    }
    ngood++;
    addr1 += 4;
    addr2 += 4;
  }

  printf("Total of %ld words were the same\n", ngood);
  return rcode;
}

int do_mem_cp(int argc, char *argv[]) {
  ulong addr, dest, length, count;

  if (argc != 4) {
    printf("memory copy\n"
           "cp source target length\n");
    return 1;
  }

  addr   = simple_strtoul(argv[1], NULL, 16);
  dest   = simple_strtoul(argv[2], NULL, 16);
  length = simple_strtoul(argv[3], NULL, 16);
  count  = ((length + 3) & ~3) / 4;

  if (!count)
    return 0;

  while (count-- > 0) {
    *((ulong *)dest) = *((ulong *)addr);
    addr += 4;
    dest += 4;
  }

  return 0;
}

void command_mem_init(void) {
  register_command("mw", do_mem_mw);
  register_command("md", do_mem_md);
  register_command("cp", do_mem_cp);
  register_command("cmp", do_mem_cmp);
}

module_init(command_mem_init);
