#ifndef ROCK_PAPER_SCISSORS_DUEL_BASIC_RENDERER_H_
#define ROCK_PAPER_SCISSORS_DUEL_BASIC_RENDERER_H_

// standard library includes
#include <bitset>
#include <optional>
#include <string>

// third party includes
#include <raylib.h>

// local includes
#include "game_renderer.h"

class BasicRenderer : public GameRenderer {
 public:
  BasicRenderer();
  ~BasicRenderer() override{};

  void update_state(const char *playerOne, const char *playerTwo,
                    const char *currentPlayer, char first_first,
                    char first_second, char first_third, char second_first,
                    char second_second, char second_third, bool first_ready,
                    bool second_ready, int pos, int matchup_idx, bool gameover,
                    bool matchup_started) override;

  void do_update() override;

  void screen_size_changed() override;

 private:
  void update_impl();
  void draw_impl();

  void draw_choice(const unsigned int idx, const char choice,
                   const bool using_triple, const float y,
                   const Color color = WHITE);
  void draw_qm(const unsigned int idx, const bool using_triple, const float y,
               const Color color = WHITE);

  void draw_helper_coord(float *x, float *width, const unsigned int idx,
                         const bool using_triple);

  bool is_choices_set() const;
  bool is_opponent_choices_set() const;

  void draw_score() const;
  void draw_reveal_choices(const char p[3], const float y);

  std::optional<Texture2D> spriteSheet;
  std::string playerOne;
  std::string playerTwo;
  std::string status;
  /*
   * 0 - ready flag (ready to submit moves)
   * 1 - readyTimer fade to gray (fade to black otherwise)
   * 2 - is spectator
   * 3 - ready flag dirty
   * 4 - animating results
   * 5 - animating dirty
   * 6 - revealed first moves
   * 7 - revealed second moves
   * 8 - revealed third moves
   * 9 - finished revealing a move
   * 10 - first ready
   * 11 - second ready
   * 12 - ready state dirty
   * 13 - screen size changed
   * 14 - is gameover
   */
  std::bitset<32> flags;
  float readyTimer;
  float resultsTimer;
  float scoreChangeTimer;
  float requestTimer;
  int prevPos;
  int cachedPos;
  int statusSize;
  char picked[3];
  char opponentPicked[3];
  bool isPlayerOne;
};

#endif
