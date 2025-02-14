#include <linux/types.h>
#include <stdio.h>
#include <uint256.h>

void initu128(uint64_t *buffer, uint128_t *target) {
  UPPER_P(target) = buffer ? buffer[1] : 0;
  LOWER_P(target) = buffer ? buffer[0] : 0;
}

void initu256(uint64_t *buffer, uint256_t *target) {
  initu128(buffer, &UPPER_P(target));
  initu128(buffer ? buffer + 16 : NULL, &LOWER_P(target));
}

static uint64_t readUint64BE(uint8_t *buffer) {
  return (((uint64_t)buffer[0]) << 56) | (((uint64_t)buffer[1]) << 48) |
         (((uint64_t)buffer[2]) << 40) | (((uint64_t)buffer[3]) << 32) |
         (((uint64_t)buffer[4]) << 24) | (((uint64_t)buffer[5]) << 16) |
         (((uint64_t)buffer[6]) << 8) | (((uint64_t)buffer[7]));
}

void readu128BE(uint8_t *buffer, uint128_t *target) {
  UPPER_P(target) = readUint64BE(buffer);
  LOWER_P(target) = readUint64BE(buffer + 8);
}

void readu256BE(uint8_t *buffer, uint256_t *target) {
  readu128BE(buffer, &UPPER_P(target));
  readu128BE(buffer + 16, &LOWER_P(target));
}

static uint64_t readUint64LE(uint8_t *buffer) {
  return (((uint64_t)buffer[7]) << 56) | (((uint64_t)buffer[6]) << 48) |
         (((uint64_t)buffer[5]) << 40) | (((uint64_t)buffer[4]) << 32) |
         (((uint64_t)buffer[3]) << 24) | (((uint64_t)buffer[2]) << 16) |
         (((uint64_t)buffer[1]) << 8) | (((uint64_t)buffer[0]));
}

void readu128LE(uint8_t *buffer, uint128_t *target) {
  LOWER_P(target) = readUint64LE(buffer);
  UPPER_P(target) = readUint64LE(buffer + 8);
}

void readu256LE(uint8_t *buffer, uint256_t *target) {
  readu128LE(buffer, &LOWER_P(target));
  readu128LE(buffer + 16, &UPPER_P(target));
}

void xor128(uint128_t *number1, uint128_t *number2, uint128_t *target) {
  UPPER_P(target) = UPPER_P(number1) ^ UPPER_P(number2);
  LOWER_P(target) = LOWER_P(number1) ^ LOWER_P(number2);
}

void xor256(uint256_t *number1, uint256_t *number2, uint256_t *target) {
  xor128(&UPPER_P(number1), &UPPER_P(number2), &UPPER_P(target));
  xor128(&LOWER_P(number1), &LOWER_P(number2), &LOWER_P(target));
}

void printu128(uint128_t *target) {
  printf("%016lx%016lx\n", UPPER_P(target), LOWER_P(target));
}

void printu256(uint256_t *target) {
  printf("%016lx%016lx%016lx%016lx\n", UPPER_P(&UPPER_P(target)),
         LOWER_P(&UPPER_P(target)), UPPER_P(&LOWER_P(target)),
         LOWER_P(&LOWER_P(target)));
}
