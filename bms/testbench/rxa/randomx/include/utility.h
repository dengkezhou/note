/*
Copyright (c) 2018-2019, tevador <tevador@gmail.com>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the copyright holder nor the
          names of its contributors may be used to endorse or promote products
          derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <exports.h>

static inline void outputHex(const char *data, int length) {
  char hexmap[] = "0123456789abcdef";
  for (int i = 0; i < length; ++i) {
    printf("%c", hexmap[(data[i] & 0xF0) >> 4]);
    printf("%c", hexmap[data[i] & 0x0F]);
  }
}

static inline char parseNibble(char hex) {
  hex &= ~0x20;
  if (hex & 0x40) {
    hex -= 'A' - 10;
  } else {
    hex &= 0xf;
  }
  return hex;
}

static inline void hex2bin(const char *in, int length, char *out) {
  for (int i = 0; i < length; i += 2) {
    char nibble1 = parseNibble(*in++);
    char nibble2 = parseNibble(*in++);
    *out++       = nibble1 << 4 | nibble2;
  }
}

static inline bool stringsEqual(char const *a, char const *b) {
  return *a == *b && (*a == '\0' || stringsEqual(a + 1, b + 1));
}

static inline void dump(const char *buffer, uint64_t count, const char *name) {
#if 0
	std::ofstream fout(name, std::ios::out | std::ios::binary);
	fout.write(buffer, count);
	fout.close();
#endif
}

static inline void readOption(const char *option, int argc, char **argv,
                              bool *out) {
  for (int i = 0; i < argc; ++i) {
    if (strcmp(argv[i], option) == 0) {
      *out = true;
      return;
    }
  }
  *out = false;
}

static inline int atoi(char *s) {
  int i;
  int n = 0;
  for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i) {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

static inline void readIntOption(const char *option, int argc, char **argv,
                                 int *out, int defaultValue) {
  for (int i = 0; i < argc - 1; ++i) {
    if (strcmp(argv[i], option) == 0 && (*out = atoi(argv[i + 1])) > 0) {
      return;
    }
  }
  *out = defaultValue;
}

static inline void readUInt64Option(const char *option, int argc, char **argv,
                                    uint64_t *out, uint64_t defaultValue) {
  for (int i = 0; i < argc - 1; ++i) {
    if (strcmp(argv[i], option) == 0 &&
        (*out = simple_strtoul(argv[i + 1], NULL, 0)) > 0) {
      return;
    }
  }
  *out = defaultValue;
}
#if 0
static inline void readFloatOption(const char *option, int argc, char **argv,
                                   double *out, double defaultValue) {
  for (int i = 0; i < argc - 1; ++i) {
    if (strcmp(argv[i], option) == 0 && (*out = atof(argv[i + 1])) > 0) {
      return;
    }
  }
  *out = defaultValue;
}
#endif
static inline void readInt(int argc, char **argv, int *out, int defaultValue) {
  for (int i = 0; i < argc; ++i) {
    if (*argv[i] != '-' && (*out = atoi(argv[i])) > 0) {
      return;
    }
  }
  *out = defaultValue;
}

#endif
