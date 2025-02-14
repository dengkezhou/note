#ifndef __MATH_H__
#define __MATH_H__

// #include "common.h"
#include <linux/types.h>

#define DOMAIN    1
#define SING      2
#define OVERFLOW  3
#define UNDERFLOW 4
#define TLOSS     5
#define PLOSS     6

#define EDOM   33 /* Math arg out of domain of func */
#define ERANGE 34 /* Math result not representable */

#define FP_NAN       0
#define FP_INFINITE  1
#define FP_ZERO      2
#define FP_SUBNORMAL 3
#define FP_NORMAL    4

#define HUGE_VAL (1.7E+308)
#define HUGE     ((float)3.40282346638528860e+38)
#define M_PI     3.141592653589793238462643

#define log10f(val) log10((double)(val))

#define log2(val) log((double)(val))

#define fpclassify(__x)                                                        \
  ((sizeof(__x) == sizeof(float)) ? __fpclassifyf(__x) : __fpclassifyd(__x))

#ifndef isnan
#define isnan(y) (fpclassify(y) == FP_NAN)
#endif

#ifdef __IEEE_BIG_ENDIAN

typedef union {
  double value;
  struct {
    uint32_t msw;
    uint32_t lsw;
  } parts;
} ieee_double_shape_type;

#endif

//#ifdef __IEEE_LITTLE_ENDIAN

typedef union {
  double value;
  struct {
    uint32_t lsw;
    uint32_t msw;
  } parts;
} ieee_double_shape_type;

//#endif

struct exception {
  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};

#define EXTRACT_WORDS(ix0, ix1, d)                                             \
  do {                                                                         \
    ieee_double_shape_type ew_u;                                               \
    ew_u.value = (d);                                                          \
    (ix0)      = ew_u.parts.msw;                                               \
    (ix1)      = ew_u.parts.lsw;                                               \
  } while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i, d)                                                    \
  do {                                                                         \
    ieee_double_shape_type gh_u;                                               \
    gh_u.value = (d);                                                          \
    (i)        = gh_u.parts.msw;                                               \
  } while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i, d)                                                     \
  do {                                                                         \
    ieee_double_shape_type gl_u;                                               \
    gl_u.value = (d);                                                          \
    (i)        = gl_u.parts.lsw;                                               \
  } while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d, ix0, ix1)                                              \
  do {                                                                         \
    ieee_double_shape_type iw_u;                                               \
    iw_u.parts.msw = (ix0);                                                    \
    iw_u.parts.lsw = (ix1);                                                    \
    (d)            = iw_u.value;                                               \
  } while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d, v)                                                    \
  do {                                                                         \
    ieee_double_shape_type sh_u;                                               \
    sh_u.value     = (d);                                                      \
    sh_u.parts.msw = (v);                                                      \
    (d)            = sh_u.value;                                               \
  } while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d, v)                                                     \
  do {                                                                         \
    ieee_double_shape_type sl_u;                                               \
    sl_u.value     = (d);                                                      \
    sl_u.parts.lsw = (v);                                                      \
    (d)            = sl_u.value;                                               \
  } while (0)

/* A union which permits us to convert between a float and a 32 bit
   int.  */

typedef union {
  float value;
  uint32_t word;
} ieee_float_shape_type;

/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i, d)                                                   \
  do {                                                                         \
    ieee_float_shape_type gf_u;                                                \
    gf_u.value = (d);                                                          \
    (i)        = gf_u.word;                                                    \
  } while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d, i)                                                   \
  do {                                                                         \
    ieee_float_shape_type sf_u;                                                \
    sf_u.word = (i);                                                           \
    (d)       = sf_u.value;                                                    \
  } while (0)

double sin(double x);
double cos(double x);
double fmin(double x, double y);
double fmax(double x, double y);
int abs(int i);
double fabs(double x);
double ceil(double x);
double floor(double x);
double scalbn(double x, int n);
double rint(double x);
double pow(double x, double y);
double sqrt(double x);
double log(double x);
double log10(double x);
double exp(double x);
void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *));

#endif //__MATH_H__
