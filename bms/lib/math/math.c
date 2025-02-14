#include <math.h>
/*
 * COPYRIGHT:        See COPYING in the top level directory
 * PROJECT:          ReactOS CRT
 * FILE:             lib/crt/math/cos.c
 * PURPOSE:          Generic C Implementation of cos
 * PROGRAMMER:       Timo Kreuzer (timo.kreuzer@reactos.org)
 */

#define PRECISION 9

static double cos_off_tbl[]  = {0.0, -M_PI / 2., 0, -M_PI / 2.};
static double cos_sign_tbl[] = {1, -1, -1, 1};

static double sin_off_tbl[]  = {0.0, -M_PI / 2., 0, -M_PI / 2.};
static double sin_sign_tbl[] = {1, -1, -1, 1};

static const double bp[] =
    {
        1.0,
        1.5,
}, /*                               */
    dp_h[] =
        {
            0.0,
            5.84962487220764160156e-01,
}, /* 0x3FE2B803, 0x40000000 */
    dp_l[] =
        {
            0.0,
            1.35003920212974897128e-08,
},                                       /* 0x3E4CFDEB, 0x43CFD006 */
    zero   = 0.0,                        /*                               */
    one    = 1.0,                        /*                               */
    two    = 2.0,                        /*                               */
    two53  = 9007199254740992.0,         /* 0x43400000, 0x00000000 */
    two54  = 1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
    twom54 = 5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
    huge   = 1.0e+300,                   /*                               */
    tiny   = 1.0e-300,                   /*                               */
    /* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
    L1    = 5.99999999999994648725e-01,  /* 0x3FE33333, 0x33333303 */
    L2    = 4.28571428578550184252e-01,  /* 0x3FDB6DB6, 0xDB6FABFF */
    L3    = 3.33333329818377432918e-01,  /* 0x3FD55555, 0x518F264D */
    L4    = 2.72728123808534006489e-01,  /* 0x3FD17460, 0xA91D4101 */
    L5    = 2.30660745775561754067e-01,  /* 0x3FCD864A, 0x93C9DB65 */
    L6    = 2.06975017800338417784e-01,  /* 0x3FCA7E28, 0x4A454EEF */
    P1    = 1.66666666666666019037e-01,  /* 0x3FC55555, 0x5555553E */
    P2    = -2.77777777770155933842e-03, /* 0xBF66C16C, 0x16BEBD93 */
    P3    = 6.61375632143793436117e-05,  /* 0x3F11566A, 0xAF25DE2C */
    P4    = -1.65339022054652515390e-06, /* 0xBEBBBD41, 0xC5D26BF1 */
    P5    = 4.13813679705723846039e-08,  /* 0x3E663769, 0x72BEA4D0 */
    lg2   = 6.93147180559945286227e-01,  /* 0x3FE62E42, 0xFEFA39EF */
    lg2_h = 6.93147182464599609375e-01,  /* 0x3FE62E43, 0x00000000 */
    lg2_l = -1.90465429995776804525e-09, /* 0xBE205C61, 0x0CA86C39 */
    ovt   = 8.0085662595372944372e-0017, /* -(1024-log2(ovfl+.5ulp)) */
    cp    = 9.61796693925975554329e-01,  /* 0x3FEEC709, 0xDC3A03FD =2/(3ln2) */
    cp_h  = 9.61796700954437255859e-01,  /* 0x3FEEC709, 0xE0000000 =(float)cp */
    cp_l =
        -7.02846165095275826516e-09, /* 0xBE3E2FE0, 0x145B01F5 =tail of cp_h*/
    ivln2   = 1.44269504088896338700e+00, /* 0x3FF71547, 0x652B82FE =1/ln2 */
    ivln2_h = 1.44269502162933349609e+00, /* 0x3FF71547, 0x60000000 =24b 1/ln2*/
    ivln2_l =
        1.92596299112661746887e-08; /* 0x3E54AE0B, 0xF85DDF44 =1/ln2 tail*/

static const double TWO52[2] = {
    4.50359962737049600000e+15,  /* 0x43300000, 0x00000000 */
    -4.50359962737049600000e+15, /* 0xC3300000, 0x00000000 */
};

static const double ln2_hi = 6.93147180369123816490e-01, /* 3fe62e42 fee00000 */
    ln2_lo                 = 1.90821492927058770002e-10, /* 3dea39ef 35793c76 */
    Lg1                    = 6.666666666666735130e-01,   /* 3FE55555 55555593 */
    Lg2                    = 3.999999999940941908e-01,   /* 3FD99999 9997FA04 */
    Lg3                    = 2.857142874366239149e-01,   /* 3FD24924 94229359 */
    Lg4                    = 2.222219843214978396e-01,   /* 3FCC71C5 1D8E78AF */
    Lg5                    = 1.818357216161805012e-01,   /* 3FC74664 96CB03DE */
    Lg6                    = 1.531383769920937332e-01,   /* 3FC39A09 D078C69F */
    Lg7                    = 1.479819860511658591e-01,   /* 3FC2F112 DF3E5244 */
    ivln10    = 4.34294481903251816668e-01, /* 0x3FDBCB7B, 0x1526E50E */
    log10_2hi = 3.01029995663611771306e-01, /* 0x3FD34413, 0x509F6000 */
    log10_2lo = 3.69423907715893078616e-13; /* 0x3D59FEF3, 0x11F12B36 */

static const double halF[2] =
    {
        0.5,
        -0.5,
}, /*                               */
    twom1000    = 9.33263618503218878990e-302, /* 2**-1000=0x01700000,0*/
    o_threshold = 7.09782712893383973096e+02,  /* 0x40862E42, 0xFEFA39EF */
    u_threshold = -7.45133219101941108420e+02, /* 0xc0874910, 0xD52D3051 */
    ln2HI[2] =
        {
            6.93147180369123816490e-01, /* 0x3fe62e42, 0xfee00000 */
            -6.93147180369123816490e-01,
}, /* 0xbfe62e42, 0xfee00000 */
    ln2LO[2] =
        {
            1.90821492927058770002e-10, /* 0x3dea39ef, 0x35793c76 */
            -1.90821492927058770002e-10,
},                                       /* 0xbdea39ef, 0x35793c76 */
    invln2 = 1.44269504088896338700e+00; /* 0x3ff71547, 0x652b82fe */

double sin(double x) {
  int quadrant;
  double x2, result;

  /* Calculate the quadrant */
  quadrant = x * (2. / M_PI);

  /* Get offset inside quadrant */
  x = x - quadrant * (M_PI / 2.);

  /* Normalize quadrant to [0..3] */
  quadrant = (quadrant - 1) & 0x3;

  /* Fixup value for the generic function */
  x += sin_off_tbl[quadrant];

  /* Calculate the negative of the square of x */
  x2 = -(x * x);

  /* This is an unrolled taylor series using <PRECISION> iterations
   * Example with 4 iterations:
   * result = 1 - x^2/2! + x^4/4! - x^6/6! + x^8/8!
   * To save multiplications and to keep the precision high, it's performed
   * like this:
   * result = 1 - x^2 * (1/2! - x^2 * (1/4! - x^2 * (1/6! - x^2 * (1/8!))))
   */

  /* Start with 0, compiler will optimize this away */
  result = 0;

#if (PRECISION >= 10)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 *
                  15 * 16 * 17 * 18 * 19 * 20);
  result *= x2;
#endif
#if (PRECISION >= 9)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 *
                  15 * 16 * 17 * 18);
  result *= x2;
#endif
#if (PRECISION >= 8)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 *
                  15 * 16);
  result *= x2;
#endif
#if (PRECISION >= 7)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14);
  result *= x2;
#endif
#if (PRECISION >= 6)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);
  result *= x2;
#endif
#if (PRECISION >= 5)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
  result *= x2;
#endif
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8);
  result *= x2;

  result += 1. / (1. * 2 * 3 * 4 * 5 * 6);
  result *= x2;

  result += 1. / (1. * 2 * 3 * 4);
  result *= x2;

  result += 1. / (1. * 2);
  result *= x2;

  result += 1;

  /* Apply correct sign */
  result *= sin_sign_tbl[quadrant];

  return result;
}

double cos(double x) {
  int quadrant;
  double x2, result;

  /* Calculate the quadrant */
  quadrant = x * (2. / M_PI);

  /* Get offset inside quadrant */
  x = x - quadrant * (M_PI / 2.);

  /* Normalize quadrant to [0..3] */
  quadrant = quadrant & 0x3;

  /* Fixup value for the generic function */
  x += cos_off_tbl[quadrant];

  /* Calculate the negative of the square of x */
  x2 = -(x * x);

  /* This is an unrolled taylor series using <PRECISION> iterations
   * Example with 4 iterations:
   * result = 1 - x^2/2! + x^4/4! - x^6/6! + x^8/8!
   * To save multiplications and to keep the precision high, it's performed
   * like this:
   * result = 1 - x^2 * (1/2! - x^2 * (1/4! - x^2 * (1/6! - x^2 * (1/8!))))
   */

  /* Start with 0, compiler will optimize this away */
  result = 0;

#if (PRECISION >= 10)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 *
                  15 * 16 * 17 * 18 * 19 * 20);
  result *= x2;
#endif
#if (PRECISION >= 9)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 *
                  15 * 16 * 17 * 18);
  result *= x2;
#endif
#if (PRECISION >= 8)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 *
                  15 * 16);
  result *= x2;
#endif
#if (PRECISION >= 7)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14);
  result *= x2;
#endif
#if (PRECISION >= 6)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);
  result *= x2;
#endif
#if (PRECISION >= 5)
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
  result *= x2;
#endif
  result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8);
  result *= x2;

  result += 1. / (1. * 2 * 3 * 4 * 5 * 6);
  result *= x2;

  result += 1. / (1. * 2 * 3 * 4);
  result *= x2;

  result += 1. / (1. * 2);
  result *= x2;

  result += 1;

  /* Apply correct sign */
  result *= cos_sign_tbl[quadrant];

  return result;
}

double nan(const char *unused) {
  double x;

  INSERT_WORDS(x, 0x7ff80000, 0);
  return x;
}

int __fpclassifyf(float x) {
  uint32_t w;

  GET_FLOAT_WORD(w, x);

  if (w == 0x00000000 || w == 0x80000000)
    return FP_ZERO;
  else if ((w >= 0x00800000 && w <= 0x7f7fffff) ||
           (w >= 0x80800000 && w <= 0xff7fffff))
    return FP_NORMAL;
  else if ((w >= 0x00000001 && w <= 0x007fffff) ||
           (w >= 0x80000001 && w <= 0x807fffff))
    return FP_SUBNORMAL;
  else if (w == 0x7f800000 || w == 0xff800000)
    return FP_INFINITE;
  else
    return FP_NAN;
}

int __fpclassifyd(double x) {
  uint32_t msw, lsw;

  EXTRACT_WORDS(msw, lsw, x);

  if ((msw == 0x00000000 && lsw == 0x00000000) ||
      (msw == 0x80000000 && lsw == 0x00000000))
    return FP_ZERO;
  else if ((msw >= 0x00100000 && msw <= 0x7fefffff) ||
           (msw >= 0x80100000 && msw <= 0xffefffff))
    return FP_NORMAL;
  else if ((msw >= 0x00000000 && msw <= 0x000fffff) ||
           (msw >= 0x80000000 && msw <= 0x800fffff))
    /* zero is already handled above */
    return FP_SUBNORMAL;
  else if ((msw == 0x7ff00000 && lsw == 0x00000000) ||
           (msw == 0xfff00000 && lsw == 0x00000000))
    return FP_INFINITE;
  else
    return FP_NAN;
}

double fmin(double x, double y) {
  if (__fpclassifyd(x) == FP_NAN)
    return y;
  if (__fpclassifyd(y) == FP_NAN)
    return x;

  return x < y ? x : y;
}

double fmax(double x, double y) {
  if (__fpclassifyd(x) == FP_NAN)
    return y;
  if (__fpclassifyd(y) == FP_NAN)
    return x;

  return x > y ? x : y;
}

int abs(int i) { return (i < 0) ? -i : i; }

double fabs(double x) {
  uint32_t high;
  GET_HIGH_WORD(high, x);
  SET_HIGH_WORD(x, high & 0x7fffffff);
  return x;
}

double copysign(double x, double y) {
  uint32_t hx, hy;
  GET_HIGH_WORD(hx, x);
  GET_HIGH_WORD(hy, y);
  SET_HIGH_WORD(x, (hx & 0x7fffffff) | (hy & 0x80000000));
  return x;
}

int finite(double x) {
  int32_t hx;
  GET_HIGH_WORD(hx, x);
  return (int)((uint32_t)((hx & 0x7fffffff) - 0x7ff00000) >> 31);
}

int matherr(struct exception *x) {
  int n = 0;
  if (x->arg1 != x->arg1)
    return 0;
  return n;
}

double ceil(double x) {
  int32_t i0, i1, j0;
  uint32_t i, j;

  EXTRACT_WORDS(i0, i1, x);
  j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
  if (j0 < 20) {
    if (j0 < 0) /* raise inexact if x != 0 */
    {
      if (huge + x > 0.0) /* return 0*sign(x) if |x|<1 */
      {
        if (i0 < 0) {
          i0 = 0x80000000;
          i1 = 0;
        } else if ((i0 | i1) != 0) {
          i0 = 0x3ff00000;
          i1 = 0;
        }
      }
    } else {
      i = (0x000fffff) >> j0;
      if (((i0 & i) | i1) == 0)
        return x;         /* x is integral */
      if (huge + x > 0.0) /* raise inexact flag */
      {
        if (i0 > 0)
          i0 += (0x00100000) >> j0;
        i0 &= (~i);
        i1 = 0;
      }
    }
  } else if (j0 > 51) {
    if (j0 == 0x400)
      return x + x; /* inf or NaN */
    else
      return x; /* x is integral */
  } else {
    i = ((uint32_t)(0xffffffff)) >> (j0 - 20);
    if ((i1 & i) == 0)
      return x;         /* x is integral */
    if (huge + x > 0.0) /* raise inexact flag */
    {
      if (i0 > 0) {
        if (j0 == 20)
          i0 += 1;
        else {
          j = i1 + (1 << (52 - j0));
          if (j < i1)
            i0 += 1; /* got a carry */
          i1 = j;
        }
      }
      i1 &= (~i);
    }
  }
  INSERT_WORDS(x, i0, i1);
  return x;
}

double floor(double x) {
  int32_t i0, i1, j0;
  uint32_t i, j;

  EXTRACT_WORDS(i0, i1, x);
  j0 = ((i0 >> 20) & 0x7ff) - 0x3ff;
  if (j0 < 20) {
    if (j0 < 0) /* raise inexact if x != 0 */
    {
      if (huge + x > 0.0) /* return 0*sign(x) if |x|<1 */
      {
        if (i0 >= 0) {
          i0 = i1 = 0;
        } else if (((i0 & 0x7fffffff) | i1) != 0) {
          i0 = 0xbff00000;
          i1 = 0;
        }
      }
    } else {
      i = (0x000fffff) >> j0;
      if (((i0 & i) | i1) == 0)
        return x;         /* x is integral */
      if (huge + x > 0.0) /* raise inexact flag */
      {
        if (i0 < 0)
          i0 += (0x00100000) >> j0;
        i0 &= (~i);
        i1 = 0;
      }
    }
  } else if (j0 > 51) {
    if (j0 == 0x400)
      return x + x; /* inf or NaN */
    else
      return x; /* x is integral */
  } else {
    i = ((uint32_t)(0xffffffff)) >> (j0 - 20);
    if ((i1 & i) == 0)
      return x;         /* x is integral */
    if (huge + x > 0.0) /* raise inexact flag */
    {
      if (i0 < 0) {
        if (j0 == 20)
          i0 += 1;
        else {
          j = i1 + (1 << (52 - j0));
          if (j < i1)
            i0 += 1; /* got a carry */
          i1 = j;
        }
      }
      i1 &= (~i);
    }
  }
  INSERT_WORDS(x, i0, i1);
  return x;
}

double scalbn(double x, int n) {
  int32_t k, hx, lx;

  EXTRACT_WORDS(hx, lx, x);
  k = (hx & 0x7ff00000) >> 20;

  /* extract exponent */
  if (k == 0) /* 0 or subnormal x */
  {
    if ((lx | (hx & 0x7fffffff)) == 0)
      return x; /* +-0 */
    x *= two54;
    GET_HIGH_WORD(hx, x);
    k = ((hx & 0x7ff00000) >> 20) - 54;
    if (n < -50000)
      return tiny * x; /*underflow*/
  }

  if (k == 0x7ff)
    return x + x; /* NaN or Inf */
  k = k + n;

  if (k > 0x7fe)
    return huge * copysign(huge, x); /* overflow  */

  if (k > 0) /* normal result */
  {
    SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
    return x;
  }

  if (k <= -54) {
    if (n > 50000)                     /* in case integer overflow in n+k */
      return huge * copysign(huge, x); /*overflow*/
    else
      return tiny * copysign(tiny, x); /*underflow*/
  }

  k += 54; /* subnormal result */
  SET_HIGH_WORD(x, (hx & 0x800fffff) | (k << 20));
  return x * twom54;
}

double rint(double x) {
  int32_t i0, j0, sx;
  uint32_t i, i1;
  double t;
  volatile double w;

  EXTRACT_WORDS(i0, i1, x);
  sx = (i0 >> 31) & 1;               /* sign */
  j0 = ((i0 >> 20) & 0x7ff) - 0x3ff; /* exponent */
  if (j0 < 20) {
    /* no integral bits in LS part */
    if (j0 < 0) {
      /* x is fractional or 0 */
      if (((i0 & 0x7fffffff) | i1) == 0)
        return x; /* x == 0 */
      i1 |= (i0 & 0x0fffff);
      i0 &= 0xfffe0000;
      i0 |= ((i1 | -i1) >> 12) & 0x80000;
      SET_HIGH_WORD(x, i0);
      w = TWO52[sx] + x;
      t = w - TWO52[sx];
      GET_HIGH_WORD(i0, t);
      SET_HIGH_WORD(t, (i0 & 0x7fffffff) | (sx << 31));
      return t;
    } else {
      /* x has integer and maybe fraction */
      i = (0x000fffff) >> j0;
      if (((i0 & i) | i1) == 0)
        return x; /* x is integral */
      i >>= 1;
      if (((i0 & i) | i1) != 0) {
        /* 2nd or any later bit after radix is set */
        if (j0 == 19)
          i1 = 0x80000000;
        else
          i1 = 0;
        i0 = (i0 & (~i)) | ((0x40000) >> j0);
      }
    }
  } else if (j0 > 51) {
    if (j0 == 0x400)
      return x + x; /* inf or NaN */
    else
      return x; /* x is integral */
  } else {
    i = ((uint32_t)(0xffffffff)) >> (j0 - 20);
    if ((i1 & i) == 0)
      return x; /* x is integral */
    i >>= 1;
    if ((i1 & i) != 0)
      i1 = (i1 & (~i)) | ((0x40000000) >> (j0 - 20));
  }
  INSERT_WORDS(x, i0, i1);
  w = TWO52[sx] + x;
  return w - TWO52[sx];
}

double __ieee754_sqrt(double x) {
  double z;
  int32_t sign = (int)0x80000000;
  uint32_t r, t1, s1, ix1, q1;
  int32_t ix0, s0, q, m, t, i;

  EXTRACT_WORDS(ix0, ix1, x);

  /* take care of Inf and NaN */
  if ((ix0 & 0x7ff00000) == 0x7ff00000) {
    return x * x + x; /* sqrt(NaN)=NaN, sqrt(+inf)=+inf
     sqrt(-inf)=sNaN */
  }

  /* take care of zero */
  if (ix0 <= 0) {
    if (((ix0 & (~sign)) | ix1) == 0)
      return x; /* sqrt(+-0) = +-0 */
    else if (ix0 < 0)
      return (x - x) / (x - x); /* sqrt(-ve) = sNaN */
  }

  /* normalize x */
  m = (ix0 >> 20);
  if (m == 0) /* subnormal x */
  {
    while (ix0 == 0) {
      m -= 21;
      ix0 |= (ix1 >> 11);
      ix1 <<= 21;
    }
    for (i = 0; (ix0 & 0x00100000) == 0; i++)
      ix0 <<= 1;
    m -= i - 1;
    ix0 |= (ix1 >> (32 - i));
    ix1 <<= i;
  }

  m -= 1023; /* unbias exponent */
  ix0 = (ix0 & 0x000fffff) | 0x00100000;
  if (m & 1) /* odd m, double x to make it even */
  {
    ix0 += ix0 + ((ix1 & sign) >> 31);
    ix1 += ix1;
  }
  m >>= 1; /* m = [m/2] */

  /* generate sqrt(x) bit by bit */
  ix0 += ix0 + ((ix1 & sign) >> 31);
  ix1 += ix1;
  q = q1 = s0 = s1 = 0;          /* [q,q1] = sqrt(x) */
  r                = 0x00200000; /* r = moving bit from right to left */

  while (r != 0) {
    t = s0 + r;
    if (t <= ix0) {
      s0 = t + r;
      ix0 -= t;
      q += r;
    }
    ix0 += ix0 + ((ix1 & sign) >> 31);
    ix1 += ix1;
    r >>= 1;
  }

  r = sign;
  while (r != 0) {
    t1 = s1 + r;
    t  = s0;
    if ((t < ix0) || ((t == ix0) && (t1 <= ix1))) {
      s1 = t1 + r;
      if (((t1 & sign) == sign) && (s1 & sign) == 0)
        s0 += 1;
      ix0 -= t;
      if (ix1 < t1)
        ix0 -= 1;
      ix1 -= t1;
      q1 += r;
    }
    ix0 += ix0 + ((ix1 & sign) >> 31);
    ix1 += ix1;
    r >>= 1;
  }

  /* use floating add to find out rounding direction */
  if ((ix0 | ix1) != 0) {
    z = one - tiny; /* trigger inexact flag */
    if (z >= one) {
      z = one + tiny;
      if (q1 == (uint32_t)0xffffffff) {
        q1 = 0;
        q += 1;
      } else if (z > one) {
        if (q1 == (uint32_t)0xfffffffe)
          q += 1;
        q1 += 2;
      } else
        q1 += (q1 & 1);
    }
  }

  ix0 = (q >> 1) + 0x3fe00000;
  ix1 = q1 >> 1;
  if ((q & 1) == 1)
    ix1 |= sign;
  ix0 += (m << 20);
  INSERT_WORDS(z, ix0, ix1);
  return z;
}

double __ieee754_pow(double x, double y) {
  double z, ax, z_h, z_l, p_h, p_l;
  double y1, t1, t2, r, s, t, u, v, w;
  int32_t i, j, k, yisint, n;
  int32_t hx, hy, ix, iy;
  uint32_t lx, ly;

  EXTRACT_WORDS(hx, lx, x);
  EXTRACT_WORDS(hy, ly, y);
  ix = hx & 0x7fffffff;
  iy = hy & 0x7fffffff;

  /* y==zero: x**0 = 1 */
  if ((iy | ly) == 0)
    return one;

  /* x|y==NaN return NaN unless x==1 then return 1 */
  if (ix > 0x7ff00000 || ((ix == 0x7ff00000) && (lx != 0)) || iy > 0x7ff00000 ||
      ((iy == 0x7ff00000) && (ly != 0))) {
    if (((ix - 0x3ff00000) | lx) == 0)
      return one;
    else
      return nan("");
  }

  /* determine if y is an odd int when x < 0
   * yisint = 0   ... y is not an integer
   * yisint = 1   ... y is an odd int
   * yisint = 2   ... y is an even int
   */
  yisint = 0;
  if (hx < 0) {
    if (iy >= 0x43400000)
      yisint = 2; /* even integer y */
    else if (iy >= 0x3ff00000) {
      k = (iy >> 20) - 0x3ff; /* exponent */
      if (k > 20) {
        j = ly >> (52 - k);
        if ((j << (52 - k)) == ly)
          yisint = 2 - (j & 1);
      } else if (ly == 0) {
        j = iy >> (20 - k);
        if ((j << (20 - k)) == iy)
          yisint = 2 - (j & 1);
      }
    }
  }

  /* special value of y */
  if (ly == 0) {
    if (iy == 0x7ff00000) /* y is +-inf */
    {
      if (((ix - 0x3ff00000) | lx) == 0)
        return one;              /* +-1**+-inf = 1 */
      else if (ix >= 0x3ff00000) /* (|x|>1)**+-inf = inf,0 */
        return (hy >= 0) ? y : zero;
      else
        /* (|x|<1)**-,+inf = inf,0 */
        return (hy < 0) ? -y : zero;
    }
    if (iy == 0x3ff00000) /* y is  +-1 */
    {
      if (hy < 0)
        return one / x;
      else
        return x;
    }
    if (hy == 0x40000000)
      return x * x;       /* y is  2 */
    if (hy == 0x3fe00000) /* y is  0.5 */
    {
      if (hx >= 0) /* x >= +0 */
        return __ieee754_sqrt(x);
    }
  }

  ax = fabs(x);
  /* special value of x */
  if (lx == 0) {
    if (ix == 0x7ff00000 || ix == 0 || ix == 0x3ff00000) {
      z = ax; /*x is +-0,+-inf,+-1*/
      if (hy < 0)
        z = one / z; /* z = (1/|x|) */
      if (hx < 0) {
        if (((ix - 0x3ff00000) | yisint) == 0) {
          z = (z - z) / (z - z); /* (-1)**non-int is NaN */
        } else if (yisint == 1)
          z = -z; /* (x<0)**odd = -(|x|**odd) */
      }
      return z;
    }
  }

  /* (x<0)**(non-int) is NaN */
  /* REDHAT LOCAL: This used to be
   if((((hx>>31)+1)|yisint)==0) return (x-x)/(x-x);
   but ANSI C says a right shift of a signed negative quantity is
   implementation defined.  */
  if (((((uint32_t)hx >> 31) - 1) | yisint) == 0)
    return (x - x) / (x - x);

  /* |y| is huge */
  if (iy > 0x41e00000) /* if |y| > 2**31 */
  {
    if (iy > 0x43f00000) /* if |y| > 2**64, must o/uflow */
    {
      if (ix <= 0x3fefffff)
        return (hy < 0) ? huge * huge : tiny * tiny;
      if (ix >= 0x3ff00000)
        return (hy > 0) ? huge * huge : tiny * tiny;
    }

    /* over/underflow if x is not close to one */
    if (ix < 0x3fefffff)
      return (hy < 0) ? huge * huge : tiny * tiny;
    if (ix > 0x3ff00000)
      return (hy > 0) ? huge * huge : tiny * tiny;

    /* now |1-x| is tiny <= 2**-20, suffice to compute
     log(x) by x-x^2/2+x^3/3-x^4/4 */
    t  = ax - 1; /* t has 20 trailing zeros */
    w  = (t * t) * (0.5 - t * (0.3333333333333333333333 - t * 0.25));
    u  = ivln2_h * t; /* ivln2_h has 21 sig. bits */
    v  = t * ivln2_l - w * ivln2;
    t1 = u + v;
    SET_LOW_WORD(t1, 0);
    t2 = v - (t1 - u);
  } else {
    double s2, s_h, s_l, t_h, t_l;

    n = 0;
    /* take care subnormal number */
    if (ix < 0x00100000) {
      ax *= two53;
      n -= 53;
      GET_HIGH_WORD(ix, ax);
    }
    n += ((ix) >> 20) - 0x3ff;
    j = ix & 0x000fffff;

    /* determine interval */
    ix = j | 0x3ff00000; /* normalize ix */
    if (j <= 0x3988E)
      k = 0; /* |x|<sqrt(3/2) */
    else if (j < 0xBB67A)
      k = 1; /* |x|<sqrt(3)   */
    else {
      k = 0;
      n += 1;
      ix -= 0x00100000;
    }
    SET_HIGH_WORD(ax, ix);

    /* compute s = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
    u   = ax - bp[k]; /* bp[0]=1.0, bp[1]=1.5 */
    v   = one / (ax + bp[k]);
    s   = u * v;
    s_h = s;
    SET_LOW_WORD(s_h, 0);

    /* t_h=ax+bp[k] High */
    t_h = zero;
    SET_HIGH_WORD(t_h, ((ix >> 1) | 0x20000000) + 0x00080000 + (k << 18));
    t_l = ax - (t_h - bp[k]);
    s_l = v * ((u - s_h * t_h) - s_h * t_l);

    /* compute log(ax) */
    s2 = s * s;
    r  = s2 * s2 *
        (L1 + s2 * (L2 + s2 * (L3 + s2 * (L4 + s2 * (L5 + s2 * L6)))));
    r += s_l * (s_h + s);
    s2  = s_h * s_h;
    t_h = 3.0 + s2 + r;
    SET_LOW_WORD(t_h, 0);
    t_l = r - ((t_h - 3.0) - s2);

    /* u+v = s*(1+...) */
    u = s_h * t_h;
    v = s_l * t_h + t_l * s;

    /* 2/(3log2)*(s+...) */
    p_h = u + v;
    SET_LOW_WORD(p_h, 0);
    p_l = v - (p_h - u);
    z_h = cp_h * p_h; /* cp_h+cp_l = 2/(3*log2) */
    z_l = cp_l * p_h + p_l * cp + dp_l[k];

    /* log2(ax) = (s+..)*2/(3*log2) = n + dp_h + z_h + z_l */
    t  = (double)n;
    t1 = (((z_h + z_l) + dp_h[k]) + t);
    SET_LOW_WORD(t1, 0);
    t2 = z_l - (((t1 - t) - dp_h[k]) - z_h);
  }

  s = one; /* s (sign of result -ve**odd) = -1 else = 1 */
  if (((((uint32_t)hx >> 31) - 1) | (yisint - 1)) == 0)
    s = -one; /* (-ve)**(odd int) */

  /* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
  y1 = y;
  SET_LOW_WORD(y1, 0);
  p_l = (y - y1) * t1 + y * t2;
  p_h = y1 * t1;
  z   = p_l + p_h;
  EXTRACT_WORDS(j, i, z);
  if (j >= 0x40900000) /* z >= 1024 */
  {
    if (((j - 0x40900000) | i) != 0) /* if z > 1024 */
      return s * huge * huge;        /* overflow */
    else {
      if (p_l + ovt > z - p_h)
        return s * huge * huge; /* overflow */
    }
  } else if ((j & 0x7fffffff) >= 0x4090cc00) /* z <= -1075 */
  {
    if (((j - 0xc090cc00) | i) != 0) /* z < -1075 */
      return s * tiny * tiny;        /* underflow */
    else {
      if (p_l <= z - p_h)
        return s * tiny * tiny; /* underflow */
    }
  }
  /*
   * compute 2**(p_h+p_l)
   */
  i = j & 0x7fffffff;
  k = (i >> 20) - 0x3ff;
  n = 0;
  if (i > 0x3fe00000) /* if |z| > 0.5, set n = [z+0.5] */
  {
    n = j + (0x00100000 >> (k + 1));
    k = ((n & 0x7fffffff) >> 20) - 0x3ff; /* new k for n */
    t = zero;
    SET_HIGH_WORD(t, n & ~(0x000fffff >> k));
    n = ((n & 0x000fffff) | 0x00100000) >> (20 - k);
    if (j < 0)
      n = -n;
    p_h -= t;
  }
  t = p_l + p_h;
  SET_LOW_WORD(t, 0);
  u  = t * lg2_h;
  v  = (p_l - (t - p_h)) * lg2 + t * lg2_l;
  z  = u + v;
  w  = v - (z - u);
  t  = z * z;
  t1 = z - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
  r  = (z * t1) / (t1 - two) - (w + z * w);
  z  = one - (r - z);
  GET_HIGH_WORD(j, z);
  j += (n << 20);
  if ((j >> 20) <= 0)
    z = scalbn(z, (int)n); /* subnormal output */
  else
    SET_HIGH_WORD(z, j);
  return s * z;
}

double pow(double x, double y) {
  double z;
  struct exception exc;

  z = __ieee754_pow(x, y);

  if (isnan(y))
    return z;

  if (isnan(x)) {
    if (y == 0.0) {
      /* pow(NaN,0.0) */
      /* error only if _LIB_VERSION == _SVID_ & _XOPEN_ */
      exc.type   = DOMAIN;
      exc.name   = "pow";
      exc.err    = 0;
      exc.arg1   = x;
      exc.arg2   = y;
      exc.retval = 1.0;
      return exc.retval;
    } else
      return z;
  }
  if (x == 0.0) {
    if (y == 0.0) {
      /* pow(0.0,0.0) */
      /* error only if _LIB_VERSION == _SVID_ */
      exc.type   = DOMAIN;
      exc.name   = "pow";
      exc.err    = 0;
      exc.arg1   = x;
      exc.arg2   = y;
      exc.retval = 0.0;
      return exc.retval;
    }
    if (finite(y) && y < 0.0) {
      /* 0**neg */
      exc.type   = DOMAIN;
      exc.name   = "pow";
      exc.err    = 0;
      exc.arg1   = x;
      exc.arg2   = y;
      exc.retval = -HUGE_VAL;
      return exc.retval;
    }
    return z;
  }
  if (!finite(z)) {
    if (finite(x) && finite(y)) {
      if (isnan(z)) {
        /* neg**non-integral */
        exc.type   = DOMAIN;
        exc.name   = "pow";
        exc.err    = 0;
        exc.arg1   = x;
        exc.arg2   = y;
        exc.retval = 0.0; /* X/Open allow NaN */
        return exc.retval;
      } else {
        /* pow(x,y) overflow */
        exc.type   = OVERFLOW;
        exc.name   = "pow";
        exc.err    = 0;
        exc.arg1   = x;
        exc.arg2   = y;
        exc.retval = HUGE_VAL;
        y *= 0.5;
        if (x < 0.0 && rint(y) != y)
          exc.retval = -HUGE_VAL;
        return exc.retval;
      }
    }
  }
  if (z == 0.0 && finite(x) && finite(y)) {
    /* pow(x,y) underflow */
    exc.type   = UNDERFLOW;
    exc.name   = "pow";
    exc.err    = 0;
    exc.arg1   = x;
    exc.arg2   = y;
    exc.retval = 0.0;
    return exc.retval;
  }
  return z;
}

double sqrt(double x) {
  struct exception exc;
  double z;

  z = __ieee754_sqrt(x);

  if (isnan(x))
    return z;
  if (x < 0.0) {
    exc.type = DOMAIN;
    exc.name = "sqrt";
    exc.err  = 0;
    exc.arg1 = exc.arg2 = x;
    exc.retval          = 0.0;
    return exc.retval;
  } else
    return z;
}

double __ieee754_log(double x) {
  double hfsq, f, s, z, R, w, t1, t2, dk;
  int32_t k, hx, i, j;
  uint32_t lx;

  EXTRACT_WORDS(hx, lx, x);

  k = 0;
  if (hx < 0x00100000) { /* x < 2**-1022  */
    if (((hx & 0x7fffffff) | lx) == 0)
      return -two54 / zero; /* log(+-0)=-inf */
    if (hx < 0)
      return (x - x) / zero; /* log(-#) = NaN */
    k -= 54;
    x *= two54; /* subnormal number, scale up x */
    GET_HIGH_WORD(hx, x);
  }
  if (hx >= 0x7ff00000)
    return x + x;
  k += (hx >> 20) - 1023;
  hx &= 0x000fffff;
  i = (hx + 0x95f64) & 0x100000;
  SET_HIGH_WORD(x, hx | (i ^ 0x3ff00000)); /* normalize x or x/2 */
  k += (i >> 20);
  f = x - 1.0;
  if ((0x000fffff & (2 + hx)) < 3) { /* |f| < 2**-20 */
    if (f == zero) {
      if (k == 0)
        return zero;
      else {
        dk = (double)k;
        return dk * ln2_hi + dk * ln2_lo;
      }
    }
    R = f * f * (0.5 - 0.33333333333333333 * f);
    if (k == 0)
      return f - R;
    else {
      dk = (double)k;
      return dk * ln2_hi - ((R - dk * ln2_lo) - f);
    }
  }
  s  = f / (2.0 + f);
  dk = (double)k;
  z  = s * s;
  i  = hx - 0x6147a;
  w  = z * z;
  j  = 0x6b851 - hx;
  t1 = w * (Lg2 + w * (Lg4 + w * Lg6));
  t2 = z * (Lg1 + w * (Lg3 + w * (Lg5 + w * Lg7)));
  i |= j;
  R = t2 + t1;
  if (i > 0) {
    hfsq = 0.5 * f * f;
    if (k == 0)
      return f - (hfsq - s * (hfsq + R));
    else
      return dk * ln2_hi - ((hfsq - (s * (hfsq + R) + dk * ln2_lo)) - f);
  } else {
    if (k == 0)
      return f - s * (f - R);
    else
      return dk * ln2_hi - ((s * (f - R) - dk * ln2_lo) - f);
  }
}

double log(double x) /* wrapper log */
{
  double z;
  struct exception exc;

  z = __ieee754_log(x);
  if (isnan(x) || x > 0.0)
    return z;
  exc.name   = "log";
  exc.err    = 0;
  exc.arg1   = x;
  exc.arg2   = x;
  exc.retval = -HUGE_VAL;
  if (x == 0.0) {
    /* log(0) */
    exc.type = SING;
  } else {
    /* log(x<0) */
    exc.type   = DOMAIN;
    exc.retval = nan("");
  }
  return exc.retval;
}

double __ieee754_log10(double x) {
  double y, z;
  int32_t i, k, hx;
  uint32_t lx;

  EXTRACT_WORDS(hx, lx, x);

  k = 0;
  if (hx < 0x00100000) { /* x < 2**-1022  */
    if (((hx & 0x7fffffff) | lx) == 0)
      return -two54 / zero; /* log(+-0)=-inf */
    if (hx < 0)
      return (x - x) / zero; /* log(-#) = NaN */
    k -= 54;
    x *= two54; /* subnormal number, scale up x */
    GET_HIGH_WORD(hx, x);
  }
  if (hx >= 0x7ff00000)
    return x + x;
  k += (hx >> 20) - 1023;
  i  = ((uint32_t)k & 0x80000000) >> 31;
  hx = (hx & 0x000fffff) | ((0x3ff - i) << 20);
  y  = (double)(k + i);
  SET_HIGH_WORD(x, hx);
  z = y * log10_2lo + ivln10 * __ieee754_log(x);
  return z + y * log10_2hi;
}

double log10(double x) /* wrapper log10 */
{
  double z;
  struct exception exc;
  z = __ieee754_log10(x);
  if (isnan(x))
    return z;
  if (x <= 0.0) {
    exc.name   = "log10";
    exc.err    = 0;
    exc.arg1   = x;
    exc.arg2   = x;
    exc.retval = -HUGE_VAL;
    if (x == 0.0) {
      /* log10(0) */
      exc.type = SING;
    } else {
      /* log10(x<0) */
      exc.type   = DOMAIN;
      exc.retval = nan("");
    }
    return exc.retval;
  } else
    return z;
}

double __ieee754_exp(double x) /* default IEEE double exp */
{
  double y, hi, lo, c, t;
  int32_t k = 0, xsb;
  uint32_t hx;

  GET_HIGH_WORD(hx, x);
  xsb = (hx >> 31) & 1; /* sign bit of x */
  hx &= 0x7fffffff;     /* high word of |x| */

  /* filter out non-finite argument */
  if (hx >= 0x40862E42) { /* if |x|>=709.78... */
    if (hx >= 0x7ff00000) {
      uint32_t lx;
      GET_LOW_WORD(lx, x);
      if (((hx & 0xfffff) | lx) != 0)
        return x + x; /* NaN */
      else
        return (xsb == 0) ? x : 0.0; /* exp(+-inf)={inf,0} */
    }
    if (x > o_threshold)
      return huge * huge; /* overflow */
    if (x < u_threshold)
      return twom1000 * twom1000; /* underflow */
  }

  /* argument reduction */
  if (hx > 0x3fd62e42) {   /* if  |x| > 0.5 ln2 */
    if (hx < 0x3FF0A2B2) { /* and |x| < 1.5 ln2 */
      hi = x - ln2HI[xsb];
      lo = ln2LO[xsb];
      k  = 1 - xsb - xsb;
    } else {
      k  = invln2 * x + halF[xsb];
      t  = k;
      hi = x - t * ln2HI[0]; /* t*ln2HI is exact here */
      lo = t * ln2LO[0];
    }
    x = hi - lo;
  } else if (hx < 0x3e300000) { /* when |x|<2**-28 */
    if (huge + x > one)
      return one + x; /* trigger inexact */
  }

  /* x is now in primary range */
  t = x * x;
  c = x - t * (P1 + t * (P2 + t * (P3 + t * (P4 + t * P5))));
  if (k == 0)
    return one - ((x * c) / (c - 2.0) - x);
  else
    y = one - ((lo - (x * c) / (2.0 - c)) - hi);
  if (k >= -1021) {
    uint32_t hy;
    GET_HIGH_WORD(hy, y);
    SET_HIGH_WORD(y, hy + (k << 20)); /* add k to y's exponent */
    return y;
  } else {
    uint32_t hy;
    GET_HIGH_WORD(hy, y);
    SET_HIGH_WORD(y, hy + ((k + 1000) << 20)); /* add k to y's exponent */
    return y * twom1000;
  }
}

double exp(double x) /* wrapper exp */
{
  double z;
  struct exception exc;
  z = __ieee754_exp(x);

  if (finite(x)) {
    if (x > o_threshold) {
      /* exp(finite) overflow */
      exc.type = OVERFLOW;
      exc.name = "exp";
      exc.err  = 0;
      exc.arg1 = exc.arg2 = x;
      exc.retval          = HUGE_VAL;
      return exc.retval;
    } else if (x < u_threshold) {
      /* exp(finite) underflow */
      exc.type = UNDERFLOW;
      exc.name = "exp";
      exc.err  = 0;
      exc.arg1 = exc.arg2 = x;
      exc.retval          = 0.0;
      return exc.retval;
    }
  }
  return z;
}

static void exch(char *base, size_t size, size_t a, size_t b) {
  char *x = base + a * size;
  char *y = base + b * size;
  while (size) {
    char z = *x;
    *x     = *y;
    *y     = z;
    --size;
    ++x;
    ++y;
  }
}

/* Quicksort with 3-way partitioning, ala Sedgewick */
/* Blame him for the scary variable names */
/* http://www.cs.princeton.edu/~rs/talks/QuicksortIsOptimal.pdf */
static void quicksort(char *base, size_t size, ssize_t l, ssize_t r,
                      int (*compar)(const void *, const void *)) {
  ssize_t i = l - 1, j = r, p = l - 1, q = r, k;
  char *v = base + r * size;
  if (r <= l)
    return;

  for (;;) {
    while (++i != r && compar(base + i * size, v) < 0)
      ;

    while (compar(v, base + (--j) * size) < 0)
      if (j == l)
        break;

    if (i >= j)
      break;
    exch(base, size, i, j);
    if (compar(base + i * size, v) == 0)
      exch(base, size, ++p, i);
    if (compar(v, base + j * size) == 0)
      exch(base, size, j, --q);
  }
  exch(base, size, i, r);
  j = i - 1;
  ++i;
  for (k = l; k < p; k++, j--)
    exch(base, size, k, j);
  for (k = r - 1; k > q; k--, i++)
    exch(base, size, i, k);
  quicksort(base, size, l, j, compar);
  quicksort(base, size, i, r, compar);
}

void qsort(void *base, size_t nmemb, size_t size,
           int (*compar)(const void *, const void *)) {
  /* check for integer overflows */
  if (nmemb >= (((size_t)-1) >> 1) || size >= (((size_t)-1) >> 1))
    return;
  if (nmemb > 1)
    quicksort(base, size, 0, nmemb - 1, compar);
}
