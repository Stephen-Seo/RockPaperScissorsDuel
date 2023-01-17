#include "anim_sequence.h"

AnimSequence::AnimSequence(Model *model) : Anims(model) {}

AnimSequence::~AnimSequence() {}

bool AnimSequence::is_done() { return anims.empty(); }

void AnimSequence::do_update(float dt) {
  if (!anims.empty()) {
    anims.front()->do_update(dt);
    if (anims.front()->is_done()) {
      anims.pop_front();
    }
  }
}

void AnimSequence::do_draw() {
  if (!anims.empty()) {
    anims.front()->do_draw();
  }
}

void AnimSequence::push_anim(UPtr &&p) {
  anims.emplace_back(std::forward<UPtr>(p));
}
