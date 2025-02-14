/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <log.h>

/*
 * This is a basic implementation. This could be improved.
 */
void __assert(const char *function, const char *file, unsigned int line,
              const char *assertion) {
  LOG_HANDLER("ASSERT: %s <%d> : %s\n\r", function, line, assertion);
  while (1)
    ;
}

/* Likewise, but prints the error text for ERRNUM.  */
void __assert_perror_fail(int __errnum, __const char *__file,
                          unsigned int __line, __const char *__function) {
  LOG_HANDLER("assert perror fail  :%d:%s:%d:%s\n", __errnum, __file, __line,
              __function);
  return;
}

/* The following is not at all used here but needed for standard
   compliance.  */
void __assert2(const char *__assertion, const char *__file, int __line) {
  LOG_HANDLER("assert :%s:%s:%d\n", __assertion, __file, __line);
  return;
}

void test_assert(void) {
  while (1)
    ;
}

/**
 * @brief __assert_fail
 *
 * @param __assertion
 * @param __file
 * @param __line
 * @param __function
 */
void __assert_fail(__const char *__assertion, __const char *__file,
                   unsigned int __line, __const char *__function) {
  printf("assert fail :%s:%s:%d:%s\n", __assertion, __file, __line, __function);
}
