#ifndef ROCK_PAPER_SCISSORS_DUEL_3D_ANIMS_H_
#define ROCK_PAPER_SCISSORS_DUEL_3D_ANIMS_H_

// standard library includes
#include <memory>

// forward declarations
struct Model;

class Anims {
 public:
  using UPtr = std::unique_ptr<Anims>;
  using SPtr = std::shared_ptr<Anims>;

  using FP = void (*)(void *);

  Anims(Model *model);
  virtual ~Anims() {}

  bool is_done();
  void reset_is_done();

  virtual void do_update(float dt) = 0;
  virtual void do_draw() = 0;

  void set_end_callback(FP function_ptr, void *ud);

 protected:
  virtual bool is_done_impl() = 0;

  Model *model;
  void *userdata;
  FP function_ptr;
  bool is_done_finished;
};

#endif
