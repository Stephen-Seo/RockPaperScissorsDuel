#include "game.h"

// standard library includes
#include <cstring>

// third party includes
#include <raylib.h>

// local includes
#include "constants.h"
#include "ems.h"

Game::Game()
    : spriteSheet(std::nullopt), status("Unknown status"), readyTimer(0.0F),
      prevPos(0), cachedPos(0) {
  spriteSheet = LoadTexture("resources/rockpaperscissorsSpriteSheet.png");

  picked[0] = 0;
  picked[1] = 0;
  picked[2] = 0;
}

void Game::update_state(const char *playerOne, const char *playerTwo,
                        const char *currentPlayer, char first_first,
                        char first_second, char first_third, char second_first,
                        char second_second, char second_third, bool first_ready,
                        bool second_ready, int pos) {
  if (playerOne) {
    this->playerOne = playerOne;
  }
  if (playerTwo) {
    this->playerTwo = playerTwo;
  }

  if (std::strcmp(currentPlayer, "undefined") == 0) {
    status = "Watching a Game...";
    flags.set(2);
  } else if (std::strcmp(currentPlayer, playerOne) == 0) {
  } else if (std::strcmp(currentPlayer, playerTwo) == 0) {
  } else {
    // This should never happen.
    status = "unknown player";
  }

  if (cachedPos != pos) {
    prevPos = cachedPos;
    cachedPos = pos;
  }

  if (flags.test(0) && flags.test(3) && first_ready && second_ready) {
    flags.reset(3);
    flags.set(4);
  }
}

void Game::do_update() {
  update_impl();
  draw_impl();
}

void Game::update_impl() {
  if (flags.test(2)) {
    return;
  }

  readyTimer -= GetFrameTime();
  if (readyTimer <= 0.0F) {
    readyTimer = READY_TIMER_MAX;
    flags.flip(1);
  }

  if (IsMouseButtonPressed(0)) {
    int triple_single_width = GetScreenWidth() / 3.0F + 0.5F;
    if (triple_single_width > ICON_MAX_WIDTH) {
      triple_single_width = ICON_MAX_WIDTH;
    }

    // selected Rock
    if (GetTouchX() >= 0 && GetTouchX() <= triple_single_width &&
        GetTouchY() >= GetScreenHeight() - triple_single_width &&
        GetTouchY() <= GetScreenHeight()) {
      bool set_picked = false;
      for (unsigned int i = 0; i < 3; ++i) {
        if (picked[i] == 0) {
          picked[i] = 'r';
          set_picked = true;
          break;
        }
      }
      if (!set_picked) {
        picked[2] = 'r';
      }
    }
    // selected Paper
    else if (GetTouchX() >= triple_single_width &&
             GetTouchX() <= triple_single_width * 2 &&
             GetTouchY() >= GetScreenHeight() - triple_single_width &&
             GetTouchY() <= GetScreenHeight()) {
      bool set_picked = false;
      for (unsigned int i = 0; i < 3; ++i) {
        if (picked[i] == 0) {
          picked[i] = 'p';
          set_picked = true;
          break;
        }
      }
      if (!set_picked) {
        picked[2] = 'p';
      }
    }
    // selected Scissors
    else if (GetTouchX() >= triple_single_width * 2 &&
             GetTouchX() <= GetScreenWidth() &&
             GetTouchY() >= GetScreenHeight() - triple_single_width &&
             GetTouchY() <= GetScreenHeight()) {
      bool set_picked = false;
      for (unsigned int i = 0; i < 3; ++i) {
        if (picked[i] == 0) {
          picked[i] = 's';
          set_picked = true;
          break;
        }
      }
      if (!set_picked) {
        picked[2] = 's';
      }
    }
    // selected Slot 0
    else if (GetTouchX() >= 0 && GetTouchX() <= triple_single_width &&
             GetTouchY() >= GetScreenHeight() - triple_single_width * 2 &&
             GetTouchY() <= GetScreenHeight() - triple_single_width) {
      picked[0] = 0;
    }
    // selected Slot 1
    else if (GetTouchX() >= triple_single_width &&
             GetTouchX() <= triple_single_width * 2 &&
             GetTouchY() >= GetScreenHeight() - triple_single_width * 2 &&
             GetTouchY() <= GetScreenHeight() - triple_single_width) {
      picked[1] = 0;
    }
    // selected Slot 2
    else if (GetTouchX() >= triple_single_width * 2 &&
             GetTouchX() <= GetScreenWidth() &&
             GetTouchY() >= GetScreenHeight() - triple_single_width * 2 &&
             GetTouchY() <= GetScreenHeight() - triple_single_width) {
      picked[2] = 0;
    }
    // selected Ready
    else if (GetTouchX() >= 0 && GetTouchX() <= GetScreenWidth() &&
             GetTouchY() >= GetScreenHeight() - triple_single_width * 3 &&
             GetTouchY() <= GetScreenHeight() - triple_single_width * 2) {
      if (picked[0] != 0 && picked[1] != 0 && picked[2] != 0 &&
          !flags.test(0)) {
        call_js_set_ready();
        flags.set(0);
        flags.set(3);
      }
    }
  }

  if (picked[0] != 0 && picked[1] != 0 && picked[2] != 0) {
    if (flags.test(0)) {
      status = "Waiting...";
    } else {
      status = "Hit Ready!";
    }
  } else {
    status = "Pick Moves!";
  }
}

void Game::draw_impl() {
  if (flags.test(2)) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(status.c_str(), 0, 0, 30, RAYWHITE);
    EndDrawing();
    return;
  }

  BeginDrawing();
  ClearBackground(BLACK);
  if (spriteSheet.has_value()) {
    float fifth_width = GetScreenWidth() / 5.0F;
    float triple_single_width = GetScreenWidth() / 3.0F;
    if (triple_single_width > (float)ICON_MAX_WIDTH) {
      triple_single_width = ICON_MAX_WIDTH;
    }

    if (flags.test(0)) {
    } else {
      unsigned char value = 0;
      if (flags.test(1)) {
        // fade ready bg to gray
        value = (1.0F - readyTimer / READY_TIMER_MAX) * 127.0F;
      } else {
        // fade ready bg to black
        value = (readyTimer / READY_TIMER_MAX) * 127.0F;
      }
      DrawRectangle(0, GetScreenHeight() - triple_single_width * 3.0F,
                    GetScreenWidth(), triple_single_width,
                    {value, value, value, 255});

      DrawTexturePro(
          spriteSheet.value(),
          {READY_DIMS[0], READY_DIMS[1], READY_DIMS[2], READY_DIMS[3]},
          {0, GetScreenHeight() - triple_single_width * 3.0F,
           GetScreenWidth() - fifth_width, triple_single_width},
          {0.0F, 0.0F}, 0.0F, WHITE);

      if (flags.test(0)) {
        // is ready
        DrawTexturePro(spriteSheet.value(),
                       {EXCLAMATIONMARKS_DIMS[0], EXCLAMATIONMARKS_DIMS[1],
                        EXCLAMATIONMARKS_DIMS[2], EXCLAMATIONMARKS_DIMS[3]},
                       {GetScreenWidth() - fifth_width,
                        GetScreenHeight() - triple_single_width * 3.0F,
                        fifth_width, triple_single_width},
                       {0.0F, 0.0F}, 0.0F, WHITE);
      } else {
        // not ready yet
        DrawTexturePro(spriteSheet.value(),
                       {QUESTIONMARK_DIMS[0], QUESTIONMARK_DIMS[1],
                        QUESTIONMARK_DIMS[2], QUESTIONMARK_DIMS[3]},
                       {GetScreenWidth() - fifth_width,
                        GetScreenHeight() - triple_single_width * 3.0F,
                        fifth_width, triple_single_width},
                       {0.0F, 0.0F}, 0.0F, WHITE);
      }

      DrawRectangle(0, GetScreenHeight() - triple_single_width * 2.0F,
                    GetScreenWidth(), triple_single_width,
                    {200, 200, 200, 255});

      for (unsigned int i = 0; i < 3; ++i) {
        float x = 0;
        if (i == 1) {
          x = (GetScreenWidth() - triple_single_width) / 2.0F;
        } else if (i == 2) {
          x = GetScreenWidth() - triple_single_width;
        }
        switch (picked[i]) {
        case 0:
          break;
        case 'r':
          DrawTexturePro(
              spriteSheet.value(),
              {ROCK_DIMS[0], ROCK_DIMS[1], ROCK_DIMS[2], ROCK_DIMS[3]},
              {x, (float)GetScreenHeight() - triple_single_width * 2.0F,
               triple_single_width, triple_single_width},
              {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case 'p':
          DrawTexturePro(
              spriteSheet.value(),
              {PAPER_DIMS[0], PAPER_DIMS[1], PAPER_DIMS[2], PAPER_DIMS[3]},
              {x, (float)GetScreenHeight() - triple_single_width * 2.0F,
               triple_single_width, triple_single_width},
              {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case 's':
          DrawTexturePro(spriteSheet.value(),
                         {SCISSORS_DIMS[0], SCISSORS_DIMS[1], SCISSORS_DIMS[2],
                          SCISSORS_DIMS[3]},
                         {x,
                          (float)GetScreenHeight() - triple_single_width * 2.0F,
                          triple_single_width, triple_single_width},
                         {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        default:
          break;
        }
      }

      DrawRectangle(0, GetScreenHeight() - triple_single_width,
                    GetScreenWidth(), triple_single_width,
                    {127, 127, 127, 255});
      DrawTexturePro(spriteSheet.value(),
                     {ROCK_DIMS[0], ROCK_DIMS[1], ROCK_DIMS[2], ROCK_DIMS[3]},
                     {0.0F, (float)GetScreenHeight() - triple_single_width,
                      triple_single_width, triple_single_width},
                     {0.0F, 0.0F}, 0.0F, WHITE);
      DrawTexturePro(
          spriteSheet.value(),
          {PAPER_DIMS[0], PAPER_DIMS[1], PAPER_DIMS[2], PAPER_DIMS[3]},
          {(GetScreenWidth() - triple_single_width) / 2.0F,
           (float)GetScreenHeight() - triple_single_width, triple_single_width,
           triple_single_width},
          {0.0F, 0.0F}, 0.0F, WHITE);
      DrawTexturePro(spriteSheet.value(),
                     {SCISSORS_DIMS[0], SCISSORS_DIMS[1], SCISSORS_DIMS[2],
                      SCISSORS_DIMS[3]},
                     {GetScreenWidth() - triple_single_width,
                      (float)GetScreenHeight() - triple_single_width,
                      triple_single_width, triple_single_width},
                     {0.0F, 0.0F}, 0.0F, WHITE);
    }
  }
  DrawText(status.c_str(), 0, 0, 20, RAYWHITE);
  EndDrawing();
}
