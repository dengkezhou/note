#ifndef __CVECTOR_H__
#define __CVECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_LEN     256
#define CVEFAILED   -1
#define CVESUCCESS  0
#define CVEPUSHBACK 1
#define CVEPOPBACK  2
#define CVEINSERT   3
#define CVERM       4
#define EXPANED_VAL 1
#define REDUSED_VAL 2

struct _cvector {
  void *cv_pdata;
  size_t cv_len, cv_tot_len, cv_size;
};

typedef void *citerator;
typedef struct _cvector *cvector;

cvector cvector_create(const size_t size);
void cvector_destroy(const cvector cv);
size_t cvector_length(const cvector cv);
int cvector_pushback(const cvector cv, void *memb);
int cvector_popback(const cvector cv, void *memb);
size_t cvector_iter_at(const cvector cv, citerator iter);
int cvector_iter_val(const cvector cv, citerator iter, void *memb);
citerator cvector_begin(const cvector cv);
citerator cvector_end(const cvector cv);
citerator cvector_next(const cvector cv, citerator iter);
int cvector_val_at(const cvector cv, size_t index, void *memb);
char *cvector_get_val(const cvector cv, size_t index);
int cvector_insert(const cvector cv, citerator iter, void *memb);
int cvector_insert_at(const cvector cv, size_t index, void *memb);
int cvector_rm(const cvector cv, citerator iter);
int cvector_rm_at(const cvector cv, size_t index);
void cvector_clear(const cvector cv);

void cv_info(const cvector cv);
void cv_print(const cvector cv);

#endif
