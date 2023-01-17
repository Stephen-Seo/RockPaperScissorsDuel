#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_MODEL_SHRINK_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_MODEL_SHRINK_H_

#include "a3f.h"
#include "anims.h"

class AnimModelShrink : public Anims {
 public:
  AnimModelShrink(Model *model, A3F pos);
  ~AnimModelShrink() override;

  bool is_done() override;

  void do_update(float dt) override;
  void do_draw() override;

 private:
  A3F pos;
  float timer;
};

#endif
