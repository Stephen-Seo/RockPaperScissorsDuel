#include "anim_falling_2d.h"

// local includes
#include <raylib.h>

#include "../constants.h"
#include "arrays_conv.h"
#include "deferred_2d_draw.h"

AnimFalling2D::AnimFalling2D(A3F pos, A4C color, Texture2D *texture, A4F txywh,
                             bool is_going_right, Deferred2DMap *map)
    : Anims(nullptr, pos, color),
      map(map),
      wh{txywh.at(2), txywh.at(3)},
      dx(is_going_right ? MODEL_FALLING_2D_DX : -MODEL_FALLING_2D_DX),
      dy(MODEL_FALLING_2D_DY),
      ddy(MODEL_FALLING_2D_DDY) {
  Deferred2DDraw def(texture, txywh, A2F{pos.at(0), pos.at(1)},
                     A2F{txywh.at(2) / 2.0F, txywh.at(3) / 2.0F}, color, 0.0F,
                     is_going_right);
  def_id = def.get_id();

  map->insert(std::make_pair(def_id, std::move(def)));
}

AnimFalling2D::~AnimFalling2D() {}

void AnimFalling2D::do_update(float) {
  auto iter = map->find(def_id);
  if (iter != map->end()) {
    iter->second.activate();
  }
}

void AnimFalling2D::do_draw() {}

bool AnimFalling2D::is_done_impl() {
  auto iter = map->find(def_id);
  if (iter != map->end()) {
    if (iter->second.is_activated()) {
      return true;
    }
  }
  return true;
}
