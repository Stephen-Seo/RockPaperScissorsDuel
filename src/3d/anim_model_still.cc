#include "anim_model_still.h"

#include "a3f_conv.h"

// third party includes
#include <raylib.h>

AnimModelStill::AnimModelStill(Model *model, A3F pos, float time)
    : Anims(model), pos(pos), timer(time) {}

AnimModelStill::~AnimModelStill() {}

void AnimModelStill::do_update(float dt) { timer -= dt; }

void AnimModelStill::do_draw() {
  DrawModel(*model, A3FToRV3(pos), 1.0F, WHITE);
}

bool AnimModelStill::is_done_impl() { return timer <= 0.0F; }
