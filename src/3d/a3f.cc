#include "a3f.h"

A3F operator+(const A3F &a, const A3F &b) {
  return A3F{a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

A3F operator-(const A3F &a, const A3F &b) {
  return A3F{a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

A3F operator*(const A3F &v, float s) {
  return A3F{v[0] * s, v[1] * s, v[2] * s};
}

A3F operator/(const A3F &v, float s) {
  return A3F{v[0] / s, v[1] / s, v[2] / s};
}

float A3F_F::dotp(const A3F &a, const A3F &b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

A3F A3F_F::crossp(const A3F &a, const A3F &b) {
  return A3F{a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
             a[0] * b[1] - a[1] * b[0]};
}
