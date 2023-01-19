#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_FALLING_2D_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_ANIM_FALLING_2D_H_

#include "anims.h"

// standard libary includes
#include <unordered_map>

// third party includes
#include <raylib.h>

// local includes
#include "arrays.h"
#include "deferred_2d_draw.h"

// redef map type
using Deferred2DMap = std::unordered_map<int, Deferred2DDraw>;

class AnimFalling2D : public Anims {
 public:
  AnimFalling2D(A3F pos, A4C color, Texture2D *texture, A4F txywh,
                bool is_going_right, Deferred2DMap *map);
  ~AnimFalling2D() override;

  // disable copy
  AnimFalling2D(const AnimFalling2D &) = delete;
  AnimFalling2D &operator=(const AnimFalling2D &) = delete;

  // allow move
  AnimFalling2D(AnimFalling2D &&) = default;
  AnimFalling2D &operator=(AnimFalling2D &&) = default;

  void do_update(float dt) override;
  void do_draw() override;

 protected:
  bool is_done_impl() override;

 private:
  Deferred2DMap *map;
  A2F wh;
  float dx;
  float dy;
  float ddy;
  int def_id;
};

#endif
