#include "qm.h"

#ifdef __EMSCRIPTEN__
#include "../ems.h"
#else
#include <random>
#endif

// standard library includes
#include <cmath>

// local includes
#include "../constants.h"
#include "v3_conv.h"

QuestionMark::QuestionMark(Model *m)
    : Object3D(m)
#ifndef __EMSCRIPTEN__
      ,
      re(std::random_device{}())
#endif
{
  randomize_timer_values();
}

QuestionMark::~QuestionMark() {}

void QuestionMark::update(float dt) {
  angle_timer -= dt;
  if (angle_timer <= 0.0F) {
#ifdef __EMSCRIPTEN__
    angle_timer_max =
        QM_ANGLE_TIMER_MAX + QM_ANGLE_TIMER_VARIANCE * call_js_get_random();
#else
    angle_timer_max = QM_ANGLE_TIMER_MAX +
                      QM_ANGLE_TIMER_VARIANCE *
                          std::uniform_real_distribution<float>(0.0F, 1.0F)(re);
#endif
    angle_timer += angle_timer_max;
  }

  y_timer -= dt;
  if (y_timer <= 0.0F) {
#ifdef __EMSCRIPTEN__
    y_timer_max = QM_Y_TIMER_MAX + QM_Y_TIMER_VARIANCE * call_js_get_random();
#else
    y_timer_max = QM_Y_TIMER_MAX +
                  QM_Y_TIMER_VARIANCE *
                      std::uniform_real_distribution<float>(0.0F, 1.0F)(re);
#endif
    y_timer += y_timer_max;
  }
}

void QuestionMark::draw() {
  Vector3 unit{1.0F, 1.0F, 1.0F};
  Vector3 vec3pos = V3ToRV3(pos);
  float angle = angle_timer / angle_timer_max * 2.0F - 1.0F;
  angle = angle >= 0.0F ? (std::cos(PI_F * angle) * QM_MAX_ANGLE_OFFSET)
                        : (std::cos(PI_F * (-angle)) * QM_MAX_ANGLE_OFFSET);
  float offset = (y_timer / y_timer_max) * 2.0F - 1.0F;
  offset = offset >= 0.0F
               ? ((std::cos(PI_F * offset) + 1.0F) / 2.0F * QM_MAX_Y_OFFSET)
               : ((std::cos(PI_F * (-offset)) + 1.0F) / 2.0F * QM_MAX_Y_OFFSET);
  vec3pos.y += offset;
  DrawModelEx(*model, vec3pos, {0.0F, 1.0F, 0.0F}, angle, unit, VC4ToC(color));
}

void QuestionMark::randomize_timer_values() {
#ifdef __EMSCRIPTEN__
  angle_timer = call_js_get_random() * QM_ANGLE_TIMER_MAX;
  y_timer = call_js_get_random() * QM_Y_TIMER_MAX;
#else
  angle_timer =
      std::uniform_real_distribution<float>(0.0F, QM_ANGLE_TIMER_MAX)(re);
  y_timer = std::uniform_real_distribution<float>(0.0F, QM_Y_TIMER_MAX)(re);
#endif
  angle_timer_max = QM_ANGLE_TIMER_MAX;
  y_timer_max = QM_Y_TIMER_MAX;
}
