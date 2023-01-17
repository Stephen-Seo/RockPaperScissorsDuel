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

  Anims() {}
  virtual ~Anims() {}

  virtual bool is_done() = 0;

  virtual void do_update(float dt) = 0;
  virtual void do_draw(Model *m) = 0;
};

#endif
