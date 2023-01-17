#ifndef ROCK_PAPER_SCISSORS_DUEL_ANIM_SEQUENCE_H_
#define ROCK_PAPER_SCISSORS_DUEL_ANIM_SEQUENCE_H_

#include "anims.h"

// standard library includes
#include <list>

class AnimSequence : public Anims {
 public:
  AnimSequence(Model *model);
  ~AnimSequence() override;

  bool is_done() override;

  void do_update(float dt) override;
  void do_draw() override;

  void push_anim(UPtr &&p);

 private:
  std::list<UPtr> anims;
};

#endif
