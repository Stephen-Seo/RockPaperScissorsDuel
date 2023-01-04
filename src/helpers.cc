#include "helpers.h"

// third party includes
#include <raylib.h>

bool Helpers::isValidChoice(char choice) {
  return choice == 'r' || choice == 'p' || choice == 's';
}

int Helpers::getFitableSize(const char *text, const int default_size,
                            const int width) {
  int size = default_size;
  while (MeasureText(text, size) > width) {
    --size;
    if (size <= 8) {
      break;
    }
  }

  return size;
}
