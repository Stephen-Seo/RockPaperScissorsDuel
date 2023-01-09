#ifndef ROCK_PAPER_SCISSORS_DUEL_HELPERS_H_
#define ROCK_PAPER_SCISSORS_DUEL_HELPERS_H_

namespace Helpers {

extern bool isValidChoice(char choice);
extern int getFitableSize(const char *text, const int default_size,
                          const int width);

}  // namespace Helpers

#endif
