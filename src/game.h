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

  std::optional<Texture2D> spriteSheet;
  std::string playerOne;
  std::string playerTwo;
  std::string status;
  /*
   * 0 - ready flag
   * 1 - readyTimer fade to gray (fade to black otherwise)
   * 2 - is spectator
   * 3 - ready flag dirty
   * 4 - animating results
   */
  std::bitset<32> flags;
  float readyTimer;
  int prevPos;
  int cachedPos;
  char picked[3];
  bool isPlayerOne;
};

#endif
