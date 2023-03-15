#ifndef ROCK_PAPER_SCISSORS_3D_RENDERER_H_
#define ROCK_PAPER_SCISSORS_3D_RENDERER_H_

// required dependency include
#include "game_renderer.h"

// standard library includes
#include <array>
#include <bitset>
#include <optional>
#include <unordered_map>

// third party includes
#include <raylib.h>

// local includes
#include "3d/anim_sequence.h"
#include "3d/anims.h"
#include "3d/deferred_2d_draw.h"
#include "3d/qm.h"

class Renderer3D : public GameRenderer {
 public:
  using Deferred2DMap = std::unordered_map<int, Deferred2DDraw>;

  Renderer3D();
  ~Renderer3D() override;

  void update_state(const char *playerOne, const char *playerTwo,
                    const char *currentPlayer, char first_first,
                    char first_second, char first_third, char second_first,
                    char second_second, char second_third, bool first_ready,
                    bool second_ready, bool first_matchup_done,
                    bool second_matchup_done, int pos, int prev_pos,
                    bool gameover_called, bool matchup_started,
                    const char *currentName, const char *player1AvatarUrl,
                    const char *player2AvatarUrl) override;

  void do_update() override;

  void screen_size_changed() override;

  void avatar1_loaded(unsigned long long size, const char *data) override;
  void avatar2_loaded(unsigned long long size, const char *data) override;

 private:
  void update_impl();
  void draw_impl();

  void set_random_overview();

  // Returns score after round "idx"
  int setup_anims(int idx, int score);

  void reset_for_next();

  void load_sounds();

  Sound *get_random_rock_sfx();
  Sound *get_random_paper_sfx();
  Sound *get_random_scissors_sfx();
  Sound *get_random_draw_sfx();

  Sound *type_to_sfx(char type);

  void draw_waiting_spinner();

  std::array<QuestionMark, 2> qms;

  Deferred2DMap deferred_2d_draw_map;

  Camera camera;

  std::optional<RenderTexture2D> renderTexture;

  Texture2D spriteSheet;
  Texture2D skybox_texture;
  Texture2D platform_texture;
  Texture2D qm_texture;
  Texture2D rock_texture;
  Texture2D paper_texture;
  Texture2D scissors_texture;

  std::optional<Texture2D> avatar1_texture;
  std::optional<Texture2D> avatar2_texture;

  Mesh avatar_mesh;

  std::optional<Material> avatar1_material;
  std::optional<Material> avatar2_material;

  Model skybox_model;
  Model platform_model;
  Model qm_model;
  Model rock_model;
  Model paper_model;
  Model scissors_model;

  std::array<Sound, 5> paper_sfx;
  std::array<Sound, 5> scissors_sfx;
  std::array<Sound, 4> rock_sfx;
  std::array<Sound, 3> draw_sfx;

  AnimSequence anims;

  Vector3 root_pos;

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
   * 7 - anims set for current matchup
   * 8 - choices locked
   * 9 - p1 ready
   * 10 - p2 ready
   * 11 - choices submitted
   * 12 - update received
   * 13 - matchup started
   * 14 - gameover called
   * 15 - anims was set for matchup
   * 16 - spectator saw matchup
   * 17 - spectator did reset after matchup
   * 18 - sounds loaded
   * 19 - size dirty for render texture
   * 20 - rendering to render texture
   * 21 - screen shake active
   * 22 - try to load p1 avatar
   * 23 - try to load p2 avatar
   * 24 - tried to load p1 avatar
   * 25 - tried to load p2 avatar
   */
  std::bitset<64> flags;

  float overview_timer;
  float button_color_timer;
  float screen_shake_factor;
  float screen_shake_rot_factor;
  float screen_shake_timer;
  float waiting_spinner_timer;

  int received_pos;
  int prev_pos;

  std::array<unsigned char, 3> choices;
  std::array<unsigned char, 3> opponent_choices;
};

#endif
