#ifndef ROCK_PAPER_SCISSORS_3D_RENDERER_H_
#define ROCK_PAPER_SCISSORS_3D_RENDERER_H_

// required dependency include
#include "game_renderer.h"

// standard library includes
#include <bitset>

// third party includes
#include <raylib.h>

// local includes
#include "3d/qm.h"

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

  std::array<QuestionMark, 2> qms;

  Camera camera;

  Texture2D spriteSheet;
  Texture2D skybox_texture;
  Texture2D platform_texture;
  Texture2D qm_texture;
  Texture2D rock_texture;
  Texture2D paper_texture;
  Texture2D scissors_texture;

  Model skybox_model;
  Model platform_model;
  Model qm_model;
  Model rock_model;
  Model paper_model;
  Model scissors_model;

  Vector3 root_pos;
  Vector3 p1_pos;
  Vector3 p2_pos;

  /*
   * 0 - focus view if true, overview view if false
   * 1 - overview view direction (opposite is true)
   * 2 - is player one
   * 3 - is spectator
   * 4
   * 5
   * 6 - overview type "654"
   *    000 - pan left to right (opposite is right to left)
   *    001 - from up left zoom out from target (opposite is zoom in)
   *    010 - from up right zoom out from target (opposite is zoom out)
   *    011 - from center zoom out (opposite is zoom in)
   *    100 - orbit from left to right (opposite is right to left)
   *    101 - UNUSED
   *    110 - UNUSED
   *    111 - UNUSED
   * 7 - p1_pos/p2_pos dirty
   */
  std::bitset<64> flags;

  float overview_timer;
};

#endif
