#include <jrx_core.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <isa.h>

jrx_registration_t jrxlist = {.dev = NULL, .next = &jrxlist, .prev = &jrxlist};

void *initIsa(int mode, int size, uint8_t *c, int *slots, uint8_t *d) {
  if (mode == ISA_A64)
    return initIsaA64(size, c, slots, d);
  else if (mode == ISA_RV64G)
    return initIsaRV64g(size, c, slots, d);
  else if (mode == ISA_RXA)
    return initIsaRxa(size, c, slots, d);

	return NULL;
}

void exitIsa(int mode, void *data) {
  if (mode == ISA_A64)
    exitIsaA64(data);
  else if (mode == ISA_RV64G)
    exitIsaRV64g(data);
  else if (mode == ISA_RXA)
    exitIsaRxa(data);
}

void jrx_register_all(void) {
  REGISTER_DEV(rxaDev);
#if defined(__aarch64__) || defined(__riscv)
  REGISTER_DEV(baseDev);
#else
  REGISTER_DEV(x86Dev);
#endif
}

extern bool rxaMode;
jrx_machine_t *jrx_get_machine(int id) {
  jrx_machine_t *mc;

  mc = malloc(sizeof(jrx_machine_t));
  if (!mc)
    return NULL;

  if (rxaMode) {
    mc->jrx = get_jrx_by_name("rxaDev");
  } else {
#if defined(__aarch64__) || defined(__riscv)
    mc->jrx = get_jrx_by_name("baseDev");
#else
    mc->jrx = get_jrx_by_name("x86Dev");
#endif
  }
  if (!mc->jrx) {
    printf("Get jrx device Error\n");
    return NULL;
  }

  mc->jrxDev = mc->jrx->init_jrx(id);
  return mc;
}

void jrx_release_machine(jrx_machine_t *mc) {
  if (!mc)
    return;

  mc->jrx->exit_jrx(mc->jrxDev);
  free(mc);
}

static inline void list_add_tail(jrx_registration_t *head,
                                 jrx_registration_t *add) {
  jrx_registration_t *tail = head->prev;
  tail->next               = add;
  add->next                = head;
  add->prev                = tail;
  head->prev               = add;
}

void register_jrx(jrx_t *dev) {
  jrx_registration_t *ndr;

  ndr       = malloc(sizeof(*ndr));
  ndr->dev  = dev;
  ndr->name = dev->name;
  list_add_tail(&jrxlist, ndr);
}

jrx_t *get_jrx_by_name(char *name) {
  jrx_registration_t *ndr;
  for (ndr = jrxlist.next; ndr != &jrxlist; ndr = ndr->next) {
    if (!strcmp(ndr->name, name))
      return ndr->dev;
  }
  return NULL;
}
