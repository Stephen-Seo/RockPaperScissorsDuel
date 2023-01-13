#include "obj.h"

Object3D::Object3D() : pos{0.0F, 0.0F, 0.0F}, color{255, 255, 255, 255} {}

Object3D::Object3D(Model *model)
    : pos{0.0F, 0.0F, 0.0F}, color{255, 255, 255, 255} {
  if (model) {
    this->model = model;
  }
}

Object3D::~Object3D() {}

void Object3D::set_model(Model *model) {
  if (model) {
    this->model = model;
  } else {
    this->model = std::nullopt;
  }
}

const V3 &Object3D::get_pos() const { return pos; }

void Object3D::set_pos(const V3 &pos) { this->pos = pos; }

void Object3D::set_pos(V3 &&pos) { this->pos = std::forward<V3>(pos); }

void Object3D::set_pos_x(float x) { pos[0] = x; }

void Object3D::set_pos_y(float y) { pos[1] = y; }

void Object3D::set_pos_z(float z) { pos[2] = z; }

const VC4 &Object3D::get_color() const { return color; }

void Object3D::set_color(const VC4 &color) { this->color = color; }

void Object3D::set_color(VC4 &&color) {
  this->color = std::forward<VC4>(color);
}

void Object3D::set_color_r(unsigned char r) { color[0] = r; }

void Object3D::set_color_g(unsigned char g) { color[1] = g; }

void Object3D::set_color_b(unsigned char b) { color[2] = b; }

void Object3D::set_color_a(unsigned char a) { color[3] = a; }
