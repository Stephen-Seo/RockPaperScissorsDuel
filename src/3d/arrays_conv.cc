#include "arrays_conv.h"

Vector3 A3FToRV3(const A3F &v) { return Vector3{v[0], v[1], v[2]}; }

A3F RV3ToA3F(const Vector3 &v) { return A3F{v.x, v.y, v.z}; }

Color A4CToC(const A4C &v) { return Color{v[0], v[1], v[2], v[3]}; }

A4C CToA4C(const Color &c) { return A4C{c.r, c.g, c.b, c.a}; }

Vector2 A2FToRV2(const A2F &v) { return Vector2{v.at(0), v.at(1)}; }

A2F RV2ToA2F(const Vector2 &v) { return A2F{v.x, v.y}; }

Rectangle A4FToRect(const A4F &v) {
  return Rectangle{v.at(0), v.at(1), v.at(2), v.at(3)};
}

A4F RectToA4F(const Rectangle &r) { return A4F{r.x, r.y, r.width, r.height}; }
