#ifndef ROCK_PAPER_SCISSORS_3D_V3_H_
#define ROCK_PAPER_SCISSORS_3D_V3_H_

#include <array>

using V3 = std::array<float, 3>;

V3 operator+(const V3 &a, const V3 &b);
V3 operator-(const V3 &a, const V3 &b);

V3 operator*(const V3 &v, float s);
V3 operator/(const V3 &v, float s);

using VC3 = std::array<unsigned char, 3>;
using VC4 = std::array<unsigned char, 4>;

namespace V3F {
extern float dotp(const V3 &a, const V3 &b);
extern V3 crossp(const V3 &a, const V3 &b);
}  // namespace V3F

#endif
