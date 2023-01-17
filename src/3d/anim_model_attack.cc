#include "anim_model_attack.h"

// third party includes
#include <raylib.h>

// local includes
#include "../constants.h"
#include "../helpers.h"
#include "a3f_conv.h"

AnimModelAttack::AnimModelAttack(Model *model, A3F pos)
    : Anims(model),
      pos(pos),
      offset{0.0F, 0.0F, 0.0F},
      timer(MODEL_ATTACK_TIME_0),
      state(0) {}

AnimModelAttack::~AnimModelAttack() {}

bool AnimModelAttack::is_done() { return state == 3; }

void AnimModelAttack::do_update(float dt) {
  timer -= dt;
  if (timer <= 0.0F) {
    switch (state) {
      case 0:
        timer += MODEL_ATTACK_TIME_1;
        state = 1;
        break;
      case 1:
        timer += MODEL_ATTACK_TIME_2;
        state = 2;
        break;
      default:
        state = 3;
        break;
    }
  }

  switch (state) {
    case 0:
      offset.at(1) = Helpers::lerp(0.0F, MODEL_ATTACK_0_Y,
                                   1.0F - timer / MODEL_ATTACK_TIME_0);
      break;
    case 1:
      offset.at(0) = Helpers::lerp(MODEL_ATTACK_0_X, MODEL_ATTACK_1_X,
                                   1.0F - timer / MODEL_ATTACK_TIME_1);
      offset.at(1) = Helpers::lerp(MODEL_ATTACK_0_Y, MODEL_ATTACK_1_Y,
                                   1.0F - timer / MODEL_ATTACK_TIME_1);
      break;
    case 2:
      offset.at(0) = Helpers::lerp(MODEL_ATTACK_1_X, MODEL_ATTACK_2_X,
                                   1.0F - timer / MODEL_ATTACK_TIME_2);
      offset.at(1) = Helpers::lerp(MODEL_ATTACK_1_Y, MODEL_ATTACK_2_Y,
                                   1.0F - timer / MODEL_ATTACK_TIME_2);
      break;
    default:
      offset.at(0) = 0.0F;
      offset.at(1) = 0.0F;
      break;
  }
}

void AnimModelAttack::do_draw() {
  DrawModel(*model, A3FToRV3(pos + offset), 1.0F, WHITE);
}
