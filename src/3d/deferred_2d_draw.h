#ifndef ROCK_PAPER_SCISSORS_DUEL_DEFERRED_2D_DRAW_H_
#define ROCK_PAPER_SCISSORS_DUEL_DEFERRED_2D_DRAW_H_

// third party includes
#include <raylib.h>

// local includes
#include "arrays.h"

class Deferred2DDraw {
 public:
  Deferred2DDraw(Texture2D *texture, A4F txywh, A2F pos, A2F origin, A4C color,
                 float angle, bool is_going_right);

  // no copy
  Deferred2DDraw(const Deferred2DDraw &) = delete;
  Deferred2DDraw &operator=(const Deferred2DDraw &) = delete;

  // allow move
  Deferred2DDraw(Deferred2DDraw &&) = default;
  Deferred2DDraw &operator=(Deferred2DDraw &&) = default;

  void update(float dt);
  void draw();

  A2F *get_pos();
  float *get_angle();
  int get_id();
  void activate();
  bool is_activated() const;
  bool is_oob() const;

 private:
  static int id_counter;
  Texture2D *texture;
  A4F txywh;
  A2F pos;
  A2F origin;
  A4C color;
  float angle;
  float dx;
  float dy;
  float ddy;
  int id;
  bool activated;
  bool is_going_right;
};

#endif
