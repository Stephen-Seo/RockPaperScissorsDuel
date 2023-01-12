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

void Helpers::lerp_v3(const Vector3 *start, const Vector3 *end, Vector3 *out,
                      float value) {
  out->x = start->x * (1.0F - value) + end->x * value;
  out->y = start->y * (1.0F - value) + end->y * value;
  out->z = start->z * (1.0F - value) + end->z * value;
}
