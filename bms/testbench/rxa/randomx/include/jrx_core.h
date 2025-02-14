#ifndef __JRX_CORE_H__
#define __JRX_CORE_H__

#include <cvector.h>
#include <program.h>
#include <stdbool.h>
#include <stdint.h>
#include <superscalar_program.h>
#include <virtual_machine.h>
#include <malloc.h>

typedef struct jrx {
  char *name;
  void *(*init_jrx)(int id);
  void (*exit_jrx)(void *);
  void (*generateProgram)(void *, Program_t *, ProgramConfiguration_t *);
  void (*generateProgramLight)(void *, Program_t *, ProgramConfiguration_t *,
                               uint32_t);
  void (*generateSuperscalarHash)(void *, SuperscalarProgram_t *programs,
                                  cvector);
  void (*generateDatasetInitCode)(void *);
  ProgramFunc *(*getProgramFunc)(void *);
  DatasetInitFunc *(*getDatasetInitFunc)(void *);
  uint8_t *(*getCode)(void *);
  size_t (*getCodeSize)(void *);
	int (*cipherUpdate)(void *, int crypto_mode, const uint8_t *in, int inlen, uint8_t *out, int outlen, void *priv);
  void (*enableWriting)(void *);
  void (*enableExecution)(void *);
  void (*enableAll)(void *);
} jrx_t;

typedef struct jrx_registration {
  char *name;
  jrx_t *dev;

  struct jrx_registration *next; // DO NOT USE
  struct jrx_registration *prev; // DO NOT USE
} jrx_registration_t;

void register_jrx(jrx_t *dev);
jrx_t *get_jrx_by_name(char *name);

typedef struct jrx_machine {
  jrx_t *jrx;
  void *jrxDev;
} jrx_machine_t;

#define JRX_REGISTER(dev)                                                      \
  void register_jrx_##dev(void) {                                              \
    if (get_jrx_by_name(dev.name))                                             \
      return;                                                                  \
    register_jrx(&dev);                                                        \
  }

#define REGISTER_DEV(dev)                                                      \
  {                                                                            \
    extern void register_jrx_##dev(void);                                      \
    register_jrx_##dev();                                                      \
  }

void jrx_register_all(void);
extern bool rxaMode;
jrx_machine_t *jrx_get_machine(int id);
void jrx_release_machine(jrx_machine_t *mc);

#endif
