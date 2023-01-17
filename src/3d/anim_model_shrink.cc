#include "anim_model_shrink.h"

// third party includes
#include <raylib.h>

// local includes
#include "../constants.h"
#include "a3f_conv.h"

AnimModelShrink::AnimModelShrink(Model *model, A3F pos)
    : Anims(model), pos(pos), timer(MODEL_SHRINK_TIME) {}

AnimModelShrink::~AnimModelShrink() {}

bool AnimModelShrink::is_done() { return timer <= 0.0F; }

void AnimModelShrink::do_update(float dt) { timer -= dt; }

void AnimModelShrink::do_draw() {
  DrawModel(*model, A3FToRV3(pos),
            timer >= 0.0F ? (timer / MODEL_SHRINK_TIME) : 0.0F, WHITE);
}
