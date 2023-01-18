#ifndef ROCK_PAPER_SCISSORS_DUEL_GAME_RENDERER_H_
#define ROCK_PAPER_SCISSORS_DUEL_GAME_RENDERER_H_

class GameRenderer {
 public:
  GameRenderer() {}
  virtual ~GameRenderer() {}

  virtual void update_state(const char *playerOne, const char *playerTwo,
                            const char *currentPlayer, char first_first,
                            char first_second, char first_third,
                            char second_first, char second_second,
                            char second_third, bool first_ready,
                            bool second_ready, bool first_matchup_done,
                            bool second_matchup_done, int pos, int prev_pos,
                            bool gameover_called, bool matchup_started) = 0;

  virtual void do_update() = 0;

  virtual void screen_size_changed() = 0;
};

#endif
