#ifndef ROCK_PAPER_SCISSORS_DUEL_GAME_H_
#define ROCK_PAPER_SCISSORS_DUEL_GAME_H_

// standard library includes
#include <bitset>
#include <optional>
#include <string>

// third party includes
#include <raylib.h>

class Game {
public:
  Game();

  void update_state(const char *playerOne, const char *playerTwo,
                    const char *currentPlayer, char first_first,
                    char first_second, char first_third, char second_first,
                    char second_second, char second_third, bool first_ready,
                    bool second_ready, int pos);

  void do_update();

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
   */
  std::bitset<32> flags;
  float readyTimer;
  float resultsTimer;
  int prevPos;
  int cachedPos;
  char picked[3];
  char opponentPicked[3];
  bool isPlayerOne;
};

#endif
