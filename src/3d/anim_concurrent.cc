#include "anim_concurrent.h"

AnimConcurrent::AnimConcurrent(Model *model)
    : Anims(model, {0.0F, 0.0F, 0.0F}, {255, 255, 255, 255}) {}

AnimConcurrent::~AnimConcurrent() {}

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

bool AnimConcurrent::is_done_impl() { return anims.empty(); }
