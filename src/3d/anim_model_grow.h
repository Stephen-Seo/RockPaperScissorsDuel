#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_MODEL_GROW_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_MODEL_GROW_H_

#include "anims.h"
#include "arrays.h"

class AnimModelGrow : public Anims {
 public:
  AnimModelGrow(Model *model, A3F pos, A4C color);
  ~AnimModelGrow() override;

  void do_update(float dt) override;
  void do_draw() override;

 private:
  bool is_done_impl() override;

  float timer;
};

#endif
