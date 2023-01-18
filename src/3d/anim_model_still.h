#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_MODEL_STILL_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_MODEL_STILL_H_

#include "a3f.h"
#include "anims.h"

class AnimModelStill : public Anims {
 public:
  AnimModelStill(Model *model, A3F pos, A4C color, float time);
  ~AnimModelStill() override;

  void do_update(float dt) override;
  void do_draw() override;

 private:
  bool is_done_impl() override;

  float timer;
};

#endif
