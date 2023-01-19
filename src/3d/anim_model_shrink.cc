#include "anim_model_shrink.h"

// third party includes
#include <raylib.h>

// local includes
#include "../constants.h"
#include "arrays_conv.h"

AnimModelShrink::AnimModelShrink(Model *model, A3F pos, A4C color)
    : Anims(model, pos, color), timer(MODEL_SHRINK_TIME) {}

AnimModelShrink::~AnimModelShrink() {}

void AnimModelShrink::do_update(float dt) { timer -= dt; }

void AnimModelShrink::do_draw() {
  DrawModel(*model, A3FToRV3(pos),
            timer >= 0.0F ? (timer / MODEL_SHRINK_TIME) : 0.0F, A4CToC(color));
}

bool AnimModelShrink::is_done_impl() { return timer <= 0.0F; }
