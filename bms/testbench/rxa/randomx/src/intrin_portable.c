#include <intrin_portable.h>

const char *platformError = "Platform doesn't support hardware AES";

#include <stdio.h>
#include <stdlib.h>

rx_vec_i128 rx_aesenc_vec_i128(rx_vec_i128 v, rx_vec_i128 rkey) {
  printf("%s\n", platformError);
  return v;
}

rx_vec_i128 rx_aesdec_vec_i128(rx_vec_i128 v, rx_vec_i128 rkey) {
  printf("%s\n", platformError);
  return v;
}
