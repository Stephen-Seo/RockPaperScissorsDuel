#include "anim_model_still.h"

// third party includes
#include <raylib.h>

// local includes
#include "a3f_conv.h"

AnimModelStill::AnimModelStill(Model *model, A3F pos, A4C color, float time)
    : Anims(model, pos, color), timer(time) {}

AnimModelStill::~AnimModelStill() {}

void AnimModelStill::do_update(float dt) { timer -= dt; }

void AnimModelStill::do_draw() {
  DrawModel(*model, A3FToRV3(pos), 1.0F, A4CToC(color));
}

bool AnimModelStill::is_done_impl() { return timer <= 0.0F; }
