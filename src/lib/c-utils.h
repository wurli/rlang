#ifndef RLANG_C_UTILS_H
#define RLANG_C_UTILS_H

#include "cnd.h"


// Adapted from CERT C coding standards
static inline
intmax_t r__intmax_add(intmax_t x, intmax_t y) {
  if ((y > 0 && x > (INTMAX_MAX - y)) ||
      (y < 0 && x < (INTMAX_MIN - y))) {
    r_stop_internal("intmax_add", "Values too large to be added.");
  }

  return x + y;
}
static inline
intmax_t r__intmax_subtract(intmax_t x, intmax_t y) {
  if ((y > 0 && x < (INTMAX_MIN + y)) ||
      (y < 0 && x < (INTMAX_MAX + y))) {
    r_stop_internal("intmax_subtract", "Subtraction resulted in overflow or underflow.");
  }

  return x - y;
}

static inline
r_ssize r_ssize_add(r_ssize x, r_ssize y) {
  intmax_t out = r__intmax_add(x, y);

  if (out > R_SSIZE_MAX) {
    r_stop_internal("r_ssize_safe_add", "Result too large for an `r_ssize`.");
  }

  return (r_ssize) out;
}

static inline
r_ssize r_ssize_mult(r_ssize x, r_ssize y) {
  if (x > 0) {
    if (y > 0) {
      if (x > (R_SSIZE_MAX / y)) {
        goto error;
      }
    } else {
      if (y < (R_SSIZE_MIN / x)) {
        goto error;
      }
    }
  } else {
    if (y > 0) {
      if (x < (R_SSIZE_MIN / y)) {
        goto error;
      }
    } else {
      if ( (x != 0) && (y < (R_SSIZE_MAX / x))) {
        goto error;
      }
    }
  }

  return x * y;

 error:
  r_stop_internal("r_ssize_mult", "Result too large for an `r_ssize`.");
}

#endif
