#ifndef ROCK_PAPER_SCISSORS_DUEL_HELPERS_H_
#define ROCK_PAPER_SCISSORS_DUEL_HELPERS_H_

// forard declarations
struct Vector3;

namespace Helpers {

extern bool isValidChoice(char choice);
extern int getFitableSize(const char *text, const int default_size,
                          const int width);

extern void lerp_v3(const Vector3 *start, const Vector3 *end, Vector3 *out,
                    float value);

}  // namespace Helpers

#endif
