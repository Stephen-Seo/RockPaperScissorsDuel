#ifndef ROCK_PAPER_SCISSORS_3D_OBJECT_BASE_H_
#define ROCK_PAPER_SCISSORS_3D_OBJECT_BASE_H_

// standard library includes
#include <optional>

// local includes
#include "a3f.h"

// forward declarations
struct Model;

class Object3D {
 public:
  Object3D();
  Object3D(Model *model);
  virtual ~Object3D();

  virtual void update(float dt) = 0;
  virtual void draw() = 0;

  void set_model(Model *model);

  const A3F &get_pos() const;
  void set_pos(const A3F &pos);
  void set_pos(A3F &&pos);
  void set_pos_x(float x);
  void set_pos_y(float y);
  void set_pos_z(float z);

  const A4C &get_color() const;
  void set_color(const A4C &color);
  void set_color(A4C &&color);
  void set_color_r(unsigned char r);
  void set_color_g(unsigned char g);
  void set_color_b(unsigned char b);
  void set_color_a(unsigned char a);

 protected:
  A3F pos;
  A4C color;
  std::optional<Model *> model;
};

#endif
