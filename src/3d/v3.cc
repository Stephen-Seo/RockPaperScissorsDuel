#include "v3.h"

V3 operator+(const V3 &a, const V3 &b) {
  return V3{a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

V3 operator-(const V3 &a, const V3 &b) {
  return V3{a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

V3 operator*(const V3 &v, float s) { return V3{v[0] * s, v[1] * s, v[2] * s}; }

V3 operator/(const V3 &v, float s) { return V3{v[0] / s, v[1] / s, v[2] / s}; }

float V3F::dotp(const V3 &a, const V3 &b) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

V3 V3F::crossp(const V3 &a, const V3 &b) {
  return V3{a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
}
