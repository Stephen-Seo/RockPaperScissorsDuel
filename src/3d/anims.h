#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_ANIMS_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_ANIMS_H_

// standard library includes
#include <functional>
#include <memory>
#include <optional>

// local includes
#include "arrays.h"

// forward declarations
struct Model;

class Anims {
 public:
  using UPtr = std::unique_ptr<Anims>;
  using SPtr = std::shared_ptr<Anims>;

  using FP = std::function<void(void *)>;

  Anims(Model *model, A3F pos, A4C color);
  virtual ~Anims() {}

  bool is_done();
  void reset_is_done();

  virtual void do_update(float dt) = 0;
  virtual void do_draw() = 0;

  void set_end_callback(FP function, void *ud);

 protected:
  virtual bool is_done_impl() = 0;

  A3F pos;
  A4C color;
  Model *model;
  void *userdata;
  std::optional<FP> function;
  bool is_done_finished;
};

#endif
