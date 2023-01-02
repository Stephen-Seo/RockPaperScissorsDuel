#ifndef ROCK_PAPER_SCISSORS_DUEL_GAME_H_
#define ROCK_PAPER_SCISSORS_DUEL_GAME_H_

class Game {
public:
  Game();

  void update_state(const char *playerOne, const char *playerTwo, const char *currentPlayer,
               char first_first, char first_second, char first_third,
               char second_first, char second_second, char second_third,
               bool first_ready, bool second_ready, int pos);

  void do_update();

private:

  void update_impl();
  void draw_impl();

};

#endif
