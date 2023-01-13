#ifndef ROCK_PAPER_SCISSORS_3D_QUESTION_MARK_H_
#define ROCK_PAPER_SCISSORS_3D_QUESTION_MARK_H_

#include "obj.h"

#ifndef __EMSCRIPTEN__
#include <random>
#endif

class QuestionMark : public Object3D {
 public:
  QuestionMark();
  QuestionMark(Model *m);
  ~QuestionMark() override;

  void update(float dt) override;
  void draw() override;

 private:
  void randomize_timer_values();

#ifndef __EMSCRIPTEN__
  std::default_random_engine re;
#endif
  float angle_timer;
  float angle_timer_max;
  float y_timer;
  float y_timer_max;
};

#endif
