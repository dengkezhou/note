#include <program.h>

Program_t *initProgram(void) {
  Program_t *pg = NULL;

  pg = aligned_allocMemory(sizeof(Program_t), 64);
  if (!pg) {
    printf("Program alloc mem Error\n");
    return NULL;
  }
  return pg;
}

void exitProgram(Program_t *pg) {
  aligned_freeMemory(pg, sizeof(Program_t));
}

Instruction_t *getPGInstruction(Program_t *pg, int pc) {
  return &(pg->programBuffer[pc]);
}

void printProgram(Program_t *pg) {
  for (int i = 0; i < RANDOMX_PROGRAM_SIZE; ++i) {
    printInstruction(getPGInstruction(pg, i));
  }
}

uint64_t getEntropy(Program_t *pg, int i) {
  return load64(&(pg->entropyBuffer[i]));
}

uint32_t getProgramSize() { return RANDOMX_PROGRAM_SIZE; }

