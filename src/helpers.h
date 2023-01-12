#ifndef ROCK_PAPER_SCISSORS_DUEL_HELPERS_H_
#define ROCK_PAPER_SCISSORS_DUEL_HELPERS_H_

// forard declarations
struct Vector3;

namespace Helpers {

extern bool isValidChoice(char choice);
extern int getFitableSize(const char *text, const int default_size,
                          const int width);

extern float lerp(const float start, const float end, const float value);

extern void lerp_v3(const Vector3 *start, const Vector3 *end, Vector3 *out,
                    float value);

extern void overview_pan_lr(Vector3 *out, float value, bool is_opposite,
                            float offset_x);
extern void overview_zoom_out_l(Vector3 *out, float value, bool is_opposite,
                                float offset_x);
extern void overview_zoom_out_r(Vector3 *out, float value, bool is_opposite,
                                float offset_x);
extern void overview_zoom_out_c(Vector3 *out, float value, bool is_opposite,
                                float offset_x);

}  // namespace Helpers

#endif
