#include "a3f_conv.h"

Vector3 A3FToRV3(const A3F &v) { return Vector3{v[0], v[1], v[2]}; }

A3F RV3ToA3F(const Vector3 &v) { return A3F{v.x, v.y, v.z}; }

Color A4CToC(const A4C &v) { return Color{v[0], v[1], v[2], v[3]}; }

A4C CToA4C(const Color &c) { return A4C{c.r, c.g, c.b, c.a}; }
