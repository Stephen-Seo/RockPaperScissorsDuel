#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_MODEL_ATTACK_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_MODEL_ATTACK_H_

#include "a3f.h"
#include "anims.h"

class AnimModelAttack : public Anims {
 public:
  AnimModelAttack(Model *model, A3F pos, bool is_p1);
  ~AnimModelAttack() override;

  void do_update(float dt) override;
  void do_draw() override;

 private:
  bool is_done_impl() override;

  A3F pos;
  A3F offset;
  float timer;
  /*
   * 0 - rising
   * 1 - attacking
   * 2 - fallback
   * 3 - done
   */
  int state;
  bool is_p1;
};

#endif
