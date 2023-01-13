#ifndef ROCK_PAPER_SCISSORS_3D_A3F_CONV_H_
#define ROCK_PAPER_SCISSORS_3D_A3F_CONV_H_

#include "a3f.h"

// third party includes
#include <raylib.h>

extern Vector3 A3FToRV3(const A3F &v);
extern A3F RV3ToA3F(const Vector3 &v);

extern Color A4CToC(const A4C &v);
extern A4C CToA4C(const Color &c);

#endif
