#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_CONCURRENT_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_CONCURRENT_H_

#include "anims.h"

// standard library includes
#include <list>

class AnimConcurrent : public Anims {
 public:
  AnimConcurrent(Model *model);
  ~AnimConcurrent() override;

  void do_update(float dt) override;
  void do_draw() override;

  void push_anim(UPtr &&p);

 protected:
  bool is_done_impl() override;

 private:
  std::list<UPtr> anims;
};

#endif
