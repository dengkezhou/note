#ifndef __UINT256_H__
#define __UINT256_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct uint128_t {
  uint64_t elements[2];
} uint128_t;
typedef struct uint256_t {
  uint128_t elements[2];
} uint256_t;

#define UPPER_P(x) (x)->elements[0]
#define LOWER_P(x) (x)->elements[1]
#define UPPER(x)   (x).elements[0]
#define LOWER(x)   (x).elements[1]

void initu128(uint64_t *buffer, uint128_t *target);
void initu256(uint64_t *buffer, uint256_t *target);
void readu128BE(uint8_t *buffer, uint128_t *target);
void readu256BE(uint8_t *buffer, uint256_t *target);
void readu128LE(uint8_t *buffer, uint128_t *target);
void readu256LE(uint8_t *buffer, uint256_t *target);
void xor128(uint128_t *number1, uint128_t *number2, uint128_t *target);
void xor256(uint256_t *number1, uint256_t *number2, uint256_t *target);
void printu128(uint128_t *target);
void printu256(uint256_t *target);

#endif
