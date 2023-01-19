#include "deferred_2d_draw.h"

// local includes
#include <raylib.h>

#include "../constants.h"
#include "arrays_conv.h"

int Deferred2DDraw::id_counter = 0;

Deferred2DDraw::Deferred2DDraw(Texture2D *texture, A4F txywh, A2F pos,
                               A2F origin, A4C color, float angle,
                               bool is_going_right)
    : texture(texture),
      txywh(txywh),
      pos(pos),
      origin(origin),
      color(color),
      angle(angle),
      dx(is_going_right ? MODEL_FALLING_2D_DX : -MODEL_FALLING_2D_DX),
      dy(MODEL_FALLING_2D_DY),
      ddy(MODEL_FALLING_2D_DDY),
      id(id_counter++),
      activated(false),
      is_going_right(is_going_right) {}

void Deferred2DDraw::update(float dt) {
  dy += ddy * dt;
  pos.at(0) += dx * dt;
  pos.at(1) += dy * dt;
  angle += MODEL_FALLING_2D_DA * dt * (is_going_right ? 1.0F : -1.0F);
}

void Deferred2DDraw::draw() {
  DrawTexturePro(*texture, A4FToRect(txywh),
                 {pos.at(0), pos.at(1), txywh.at(2), txywh.at(3)},
                 A2FToRV2(origin), angle, A4CToC(color));
}

A2F *Deferred2DDraw::get_pos() { return &pos; }

float *Deferred2DDraw::get_angle() { return &angle; }

int Deferred2DDraw::get_id() { return id; }

void Deferred2DDraw::activate() { activated = true; }

bool Deferred2DDraw::is_activated() const { return activated; }

bool Deferred2DDraw::is_oob() const {
  return pos.at(0) - txywh.at(2) > GetScreenWidth() ||
         pos.at(0) + txywh.at(2) * 2.0F < 0.0F ||
         pos.at(1) - txywh.at(3) > GetScreenHeight() ||
         pos.at(1) + txywh.at(3) * 2.0F < 0.0F;
}
