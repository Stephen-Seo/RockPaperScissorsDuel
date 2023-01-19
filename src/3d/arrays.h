#ifndef ROCK_PAPER_SCISSORS_3D_ARRAY3F_H_
#define ROCK_PAPER_SCISSORS_3D_ARRAY3F_H_

#include <array>

using A2F = std::array<float, 2>;
using A3F = std::array<float, 3>;

A3F operator+(const A3F &a, const A3F &b);
A3F operator-(const A3F &a, const A3F &b);

A3F operator*(const A3F &v, float s);
A3F operator/(const A3F &v, float s);

using A4F = std::array<float, 4>;

using A3C = std::array<unsigned char, 3>;
using A4C = std::array<unsigned char, 4>;
using A2U = std::array<unsigned int, 2>;
using A4U = std::array<unsigned int, 4>;

namespace A3F_F {
extern float dotp(const A3F &a, const A3F &b);
extern A3F crossp(const A3F &a, const A3F &b);
}  // namespace A3F_F

#endif
