#include "v3_conv.h"

Vector3 V3ToRV3(const V3 &v) { return Vector3{v[0], v[1], v[2]}; }

V3 RV3ToV3(const Vector3 &v) { return V3{v.x, v.y, v.z}; }

Color VC4ToC(const VC4 &v) { return Color{v[0], v[1], v[2], v[3]}; }

VC4 CToVC4(const Color &c) { return VC4{c.r, c.g, c.b, c.a}; }
