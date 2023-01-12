#ifndef ROCK_PAPER_SCISSORS_3D_RENDERER_H_
#define ROCK_PAPER_SCISSORS_3D_RENDERER_H_

#include "game_renderer.h"

class Renderer3D : public GameRenderer {
 public:
  Renderer3D();
  ~Renderer3D() override;

  void update_state(const char *playerOne, const char *playerTwo,
                    const char *currentPlayer, char first_first,
                    char first_second, char first_third, char second_first,
                    char second_second, char second_third, bool first_ready,
                    bool second_ready, int pos, int matchup_idx,
                    bool gameover) override;

  void do_update() override;

  void screen_size_changed() override;

 private:
  void update_impl();
  void draw_impl();
};

#endif
