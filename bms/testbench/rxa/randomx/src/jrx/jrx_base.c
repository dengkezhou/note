#include <allocator.h>
#include <jrx_base.h>
#include <jrx_dev.h>
#include <stdlib.h>
#include <string.h>

extern int jrxNum;
jrx_base_t *initJrxBase(int sz, uint8_t *c, int *slots, uint8_t *d) {
  jrx_base_t *base = NULL;
  base             = allocMemory(AlignedAllocator, sizeof(jrx_base_t), 4);
  if (!base) {
    printf("initJrxBase malloc Error\n");
    return NULL;
  }

  base->code  = (uint8_t *)c;
  base->size  = sz;
  base->M     = slots;
  base->xslot = slots + 512;
  base->vslot = base->xslot + 32;
  base->rslot = allocMemory(AlignedAllocator, 64 * sizeof(rxaX_t), 4);
  if (!base->rslot) {
    printf("init rslot malloc Error\n");
    return NULL;
  }
  base->dlog  = d;
  base->_lock = 0;
  base->id    = ++jrxNum;
  for (int i = 0; i < 32; i++)
    base->M[i] = i;

  return base;
}

void exitJrxBase(jrx_base_t *dev) {
  freeMemory(AlignedAllocator, dev->rslot, 64 * sizeof(rxaX_t));
  freeMemory(AlignedAllocator, dev, sizeof(jrx_base_t));
}

void reset(jrx_base_t *base) {
  memset(base->code, 0, base->size);
  base->pos            = 0;
  base->lastP          = 0;
  base->lastdevregpool = GEN_REG_XPOOL;
  base->lastgenregpool = RESV_TMP;
  for (int i = 0; i < 64; i++) {
    if (i < 32) {
      *(base->xslot + i) = 0;
      *(base->vslot + i) = 0;
    }
    (base->rslot + i)->xslot = -1;
  }

  //    memset(code, 0, size);
  // if (dlog) memset(dlog, 0, size * 2);
}

void rxaReset(jrx_base_t *base) {
  base->pos            = 0;
  base->lastP          = 0;
  base->lastdevregpool = GEN_REG_XPOOL;
  base->lastgenregpool = RESV_TMP;
  for (int i = 0; i < 64; i++) {
    if (i < 32) {
      *(base->xslot + i) = 0;
      *(base->vslot + i) = 0;
    }
    (base->rslot + i)->xslot = -1;
  }
}

int jrxStage = PROGRAM;
void Jrx_set_stage(int stage) { jrxStage = stage; }

int Jrx_get_stage(void) { return jrxStage; }

void iseek(jrx_base_t *base, int offs) { base->pos = offs; }

int locked(jrx_base_t *base) { return base->_lock; }

void lock(jrx_base_t *base) { base->_lock = 1; }

inline int codeSize(jrx_base_t *base) { return base->pos; }

int _allocX(jrx_base_t *base, int resv) {
  int i;
  int stage    = Jrx_get_stage();
  int pool     = ((stage == PROGRAM) ? xpool : dspool);
  int resv_tmp = ((stage == PROGRAM) ? RESV_TMP : min(4, RESV_TMP));
  int startP = resv ? resv_tmp : 0, endP = resv ? 32 : resv_tmp;

  for (i = startP; i < endP && base->M[pool + i]; i++) {
    if (!base->xslot[i]) {
      if (!resv) {
        // backP = i;
        if (i > base->lastP) {
          base->lastP = i;
          if (base->lastP == (resv_tmp - 1))
            base->lastP = -1;
          goto release;
        }
      } else
        goto release;
    }
  }

  if (!resv) {
    printf("cannot alloc tmp X reg\n");
    for (;;)
      ;
  }
  return 0;

release:
  base->xslot[i] = 1;
  return i + pool;
}

int allocX(jrx_base_t *base) { return _allocX(base, 0); }
int resvX(jrx_base_t *base) { return _allocX(base, 1); }
void freeX(jrx_base_t *base, int x) {
  int stage             = Jrx_get_stage();
  int pool              = ((stage == PROGRAM) ? xpool : dspool);
  base->xslot[x - pool] = 0;
}

int _allocV(jrx_base_t *base, int resv) {
  int i, free_n = 0;
  int stage    = Jrx_get_stage();
  int resv_tmp = ((stage == PROGRAM) ? RESV_TMP : min(4, RESV_TMP));
  for (i = 0; i < 32 && base->M[vpool + i]; i++) {
    if (!base->vslot[i]) {
      if (!resv || ++free_n > resv_tmp)
        goto release;
    }
  }

  if (!resv) {
    printf("cannot alloc tmp V reg\n");
    for (;;)
      ;
  }
  return 0;

release:
  base->vslot[i] = 1;
  return i + vpool;
}
int allocV(jrx_base_t *base) { return _allocV(base, 0); }
void freeV(jrx_base_t *base, int x) { base->vslot[x - vpool] = 0; }

void link_(jrx_base_t *base, jrx_base_t *isa) {
  int offs = isa->code - base->code - base->pos;
  base->ops->b(base, offs);
  ENC(base, 0, 0, 0, 0);
}

void printIns(uint64_t ins) {
  int cy = ins & 0xff;
  int ut = cy >> 6;

  cy &= 0x3f;
  ins >>= 8;

  // int st = ins & 0xff;
  ins >>= 8;

  int src = (ins >> 24) == 0xfe ? 3 : 2;

  printf(" (%2d, %s): ", cy,
         !ut ? (cy == 3 ? " M " : cy > 10 ? "DIV" : "A L")
             : ut == 3 ? "LS " : ut == 2 ? " VP" : "xxx");

  if ((ins & 0xffffffffull) == 0xffffffffull) {
    printf(" ** ** => ** **");
    ins >>= 32;
    goto out;
  }

  for (int i = 0; i < 4; i++, ins >>= 8) {
    int o = ins & 0xff;

    if (i == src)
      printf(" =>");

    if (o == 0xff) {
      printf("   ");
      continue;
    }

    printf(" %02x", o);
  }

out:
  // int max = ins;
  printf(" :: %ld\n", ins);
}

void reorder(uint8_t *c2, int end) {
  uint64_t *pc = (uint64_t *)c2;
  int i = 0, _cy = 0;
  for (; *pc && ((uint8_t *)pc) - c2 < end;) {
    int k = 0, lock = 0, cy = 0;
    for (int j = 0; j < 20; j++) {
      uint64_t *p = pc + j;
      if (!*p)
        break;
      int step = *p >> 48;
      if (step <= i) {
        if (!lock)
          k++;
        if (step == i) {
          printf("%4d: ", (int)(p - (uint64_t *)c2));
          printIns(*p);
          if ((*p & 0x3f) > cy)
            cy = *p & 0x3f;
        }
      } else
        lock = 1;
    }

    if (lock) {
      i++;
      if (cy)
        printf("... %d\n", cy);
      _cy += cy;
    }
    pc += k;
  }

  printf("all clk %d\n", _cy);
}

void analyze(uint8_t *c2, int end, int reset) {
  static int D[256] = {0}, nr = 0;
  uint64_t *pc = (uint64_t *)c2;

  if (reset) {
    memset(D, 0, sizeof(D));
    nr = 0;
  }

  while (*pc && ((uint8_t *)pc) - c2 < end) {
    // printf("%016llx\n", *pc);
    uint64_t ins = *pc;
    // int cy       = ins & 0xff;
    ins >>= 8;

    // int st = ins & 0xff;
    ins >>= 8;

    int src = (ins >> 24) == 0xfe ? 3 : 2;
    int max = 0;

    if (ins == 0xffffffffffffull) {
      for (int i = 0; i < 256; i++)
        if (D[i] > max)
          max = D[i];
      for (int i = 0; i < 256; i++)
        D[i] = max;

      goto out;
    }

    for (int i = 0; i < 4; i++, ins >>= 8) {
      int o = ins & 0xff;

      if (o == 0xff)
        continue;

      // src
      if (D[o] > max)
        max = D[o];

      if (i >= src) {
        // dst
        D[o] = max + 1;
      }
    }

  out:
    *pc &= 0xffffffffffffull;
    *pc |= (uint64_t)max << 48;
    printf("%4d: ", nr);
    printIns(*pc);

    pc++;
    nr++;
  }
}
