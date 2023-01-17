#include "anim_concurrent.h"

AnimConcurrent::AnimConcurrent(Model *model) : Anims(model) {}

AnimConcurrent::~AnimConcurrent() {}

bool AnimConcurrent::is_done() { return anims.empty(); }

void AnimConcurrent::do_update(float dt) {
  for (auto iter = anims.begin(); iter != anims.end();) {
    (*iter)->do_update(dt);
    if ((*iter)->is_done()) {
      iter = anims.erase(iter);
    } else {
      ++iter;
    }
  }
}

void AnimConcurrent::do_draw() {
  for (auto &anim : anims) {
    anim->do_draw();
  }
}

void AnimConcurrent::push_anim(UPtr &&p) {
  anims.emplace_back(std::forward<UPtr>(p));
}
