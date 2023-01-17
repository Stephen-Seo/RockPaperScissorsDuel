#include "anim_model_grow.h"

// third party includes
#include <raylib.h>

// local includes
#include "../constants.h"
#include "a3f_conv.h"

AnimModelGrow::AnimModelGrow(Model *model, A3F pos)
    : Anims(model), pos(pos), timer(MODEL_GROW_TIME) {}

AnimModelGrow::~AnimModelGrow() {}

void AnimModelGrow::do_update(float dt) { timer -= dt; }

void AnimModelGrow::do_draw() {
  DrawModel(*model, A3FToRV3(pos),
            timer >= 0.0F ? (1.0F - timer / MODEL_GROW_TIME) : 1.0F, WHITE);
}

bool AnimModelGrow::is_done_impl() { return timer <= 0.0F; }
