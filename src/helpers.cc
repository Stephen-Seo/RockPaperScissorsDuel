#include "helpers.h"

// third party includes
#include <raylib.h>

// local includes
#include "constants.h"

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

float Helpers::lerp(const float start, const float end, const float value) {
  return start * (1.0F - value) + end * value;
}

void Helpers::lerp_v3(const Vector3 *start, const Vector3 *end, Vector3 *out,
                      float value) {
  out->x = lerp(start->x, end->x, value);
  out->y = lerp(start->y, end->y, value);
  out->z = lerp(start->z, end->z, value);
}

void Helpers::overview_pan_lr(Vector3 *out, float value, bool is_opposite,
                              float offset_x) {
  if (is_opposite) {
    out->x = lerp(OVERVIEW_RIGHT_X, OVERVIEW_LEFT_X, value) + offset_x;
    out->y = lerp(OVERVIEW_RIGHT_Y, OVERVIEW_LEFT_Y, value);
    out->z = lerp(OVERVIEW_RIGHT_Z, OVERVIEW_LEFT_Z, value);
  } else {
    out->x = lerp(OVERVIEW_LEFT_X, OVERVIEW_RIGHT_X, value) + offset_x;
    out->y = lerp(OVERVIEW_LEFT_Y, OVERVIEW_RIGHT_Y, value);
    out->z = lerp(OVERVIEW_LEFT_Z, OVERVIEW_RIGHT_Z, value);
  }
}

void Helpers::overview_zoom_out_l(Vector3 *out, float value, bool is_opposite,
                                  float offset_x) {
  if (is_opposite) {
    out->x = lerp(OVERVIEW_UP_L_E_X, OVERVIEW_UP_L_B_X, value) + offset_x;
    out->y = lerp(OVERVIEW_UP_L_E_Y, OVERVIEW_UP_L_B_Y, value);
    out->z = lerp(OVERVIEW_UP_L_E_Z, OVERVIEW_UP_L_B_Z, value);
  } else {
    out->x = lerp(OVERVIEW_UP_L_B_X, OVERVIEW_UP_L_E_X, value) + offset_x;
    out->y = lerp(OVERVIEW_UP_L_B_Y, OVERVIEW_UP_L_E_Y, value);
    out->z = lerp(OVERVIEW_UP_L_B_Z, OVERVIEW_UP_L_E_Z, value);
  }
}

void Helpers::overview_zoom_out_r(Vector3 *out, float value, bool is_opposite,
                                  float offset_x) {
  if (is_opposite) {
    out->x = lerp(OVERVIEW_UP_R_E_X, OVERVIEW_UP_R_B_X, value) + offset_x;
    out->y = lerp(OVERVIEW_UP_R_E_Y, OVERVIEW_UP_R_B_Y, value);
    out->z = lerp(OVERVIEW_UP_R_E_Z, OVERVIEW_UP_R_B_Z, value);
  } else {
    out->x = lerp(OVERVIEW_UP_R_B_X, OVERVIEW_UP_R_E_X, value) + offset_x;
    out->y = lerp(OVERVIEW_UP_R_B_Y, OVERVIEW_UP_R_E_Y, value);
    out->z = lerp(OVERVIEW_UP_R_B_Z, OVERVIEW_UP_R_E_Z, value);
  }
}

void Helpers::overview_zoom_out_c(Vector3 *out, float value, bool is_opposite,
                                  float offset_x) {
  if (is_opposite) {
    out->x = lerp(OVERVIEW_C_E_X, OVERVIEW_C_B_X, value) + offset_x;
    out->y = lerp(OVERVIEW_C_E_Y, OVERVIEW_C_B_Y, value);
    out->z = lerp(OVERVIEW_C_E_Z, OVERVIEW_C_B_Z, value);
  } else {
    out->x = lerp(OVERVIEW_C_B_X, OVERVIEW_C_E_X, value) + offset_x;
    out->y = lerp(OVERVIEW_C_B_Y, OVERVIEW_C_E_Y, value);
    out->z = lerp(OVERVIEW_C_B_Z, OVERVIEW_C_E_Z, value);
  }
}

void Helpers::overview_orbit(Vector3 *out, float value, bool is_opposite,
                             float offset_x) {
  value = (value * 2.0F - 1.0F) * OVERVIEW_ORBIT_MODIFIER;

  if (is_opposite) {
    out->x = -value * OVERVIEW_ORBIT_RADIUS + offset_x;
  } else {
    out->x = value * OVERVIEW_ORBIT_RADIUS + offset_x;
  }
  out->y = OVERVIEW_ORBIT_Y;
  out->z = -(value * value - 1.0F) * OVERVIEW_ORBIT_RADIUS;
}
