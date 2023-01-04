#include "game.h"

// standard library includes
#include <cstring>
#include <iostream>

// third party includes
#include <raylib.h>

// local includes
#include "constants.h"
#include "ems.h"
#include "helpers.h"

Game::Game()
    : spriteSheet(std::nullopt), status("Unknown status"), readyTimer(0.0F),
      resultsTimer(RESULTS_TIMER_MAX), scoreChangeTimer(SCORE_CHANGE_TIMER_MAX),
      requestTimer(REQUEST_TIMER_MAX), prevPos(0), cachedPos(0),
      statusSize(DEFAULT_STATUS_TEXT_SIZE) {
  spriteSheet = LoadTexture("resources/rockpaperscissorsSpriteSheet.png");

  picked[0] = 0;
  picked[1] = 0;
  picked[2] = 0;

  opponentPicked[0] = 0;
  opponentPicked[1] = 0;
  opponentPicked[2] = 0;
}

void Game::update_state(const char *playerOne, const char *playerTwo,
                        const char *currentPlayer, char first_first,
                        char first_second, char first_third, char second_first,
                        char second_second, char second_third, bool first_ready,
                        bool second_ready, int pos, int matchup_idx) {
  // TODO DEBUG
  // if (std::strcmp(playerOne, currentPlayer) == 0) {
  //  std::clog << "update_state:\n"
  //            << "  is p1: "
  //            << (std::strcmp(playerOne, currentPlayer) == 0 ? "true" :
  //            "false")
  //            << std::endl
  //            << "  p1: " << first_first << ", " << first_second << ", "
  //            << first_third << "\n  p2: " << second_first << ", "
  //            << second_second << ", " << second_third << "\nfirst is "
  //            << (first_ready ? "ready" : "NOT ready") << "\nsecond is "
  //            << (second_ready ? "ready" : "NOT ready") << "\npos: " << pos
  //            << " matchup_idx: " << matchup_idx << std::endl;
  //  std::clog << "flags: " << flags.to_string().substr(32 - 13) << std::endl;
  //}
  // TODO handle changing choices from r/p/s to w/l and etc.
  if (playerOne) {
    this->playerOne = playerOne;
  }
  if (playerTwo) {
    this->playerTwo = playerTwo;
  }

  if (std::strcmp(playerOne, currentPlayer) == 0) {
    isPlayerOne = true;
    if (Helpers::isValidChoice(second_first) &&
        Helpers::isValidChoice(second_second) &&
        Helpers::isValidChoice(second_third)) {
      opponentPicked[0] = second_first;
      opponentPicked[1] = second_second;
      opponentPicked[2] = second_third;
    }
  } else if (std::strcmp(playerTwo, currentPlayer) == 0) {
    isPlayerOne = false;
    if (Helpers::isValidChoice(first_first) &&
        Helpers::isValidChoice(first_second) &&
        Helpers::isValidChoice(first_third)) {
      opponentPicked[0] = first_first;
      opponentPicked[1] = first_second;
      opponentPicked[2] = first_third;
    }
  } else {
    isPlayerOne = false;
  }

  if ((!flags.test(10) && first_ready) || (!flags.test(11) && second_ready)) {
    flags.set(12);
  }
  flags.set(10, first_ready);
  flags.set(11, second_ready);

  if (std::strcmp(currentPlayer, "undefined") == 0) {
    status = "Watching a Game...";
    statusSize = Helpers::getFitableSize(
        status.c_str(), DEFAULT_STATUS_TEXT_SIZE, GetScreenWidth());
    flags.set(2);
    if (Helpers::isValidChoice(first_first) &&
        Helpers::isValidChoice(first_second) &&
        Helpers::isValidChoice(first_third)) {
      picked[0] = first_first;
      picked[1] = first_second;
      picked[2] = first_third;
    }
    if (Helpers::isValidChoice(second_first) &&
        Helpers::isValidChoice(second_second) &&
        Helpers::isValidChoice(second_third)) {
      opponentPicked[0] = second_first;
      opponentPicked[1] = second_second;
      opponentPicked[2] = second_third;
    }
  } else if (std::strcmp(currentPlayer, playerOne) == 0) {
  } else if (std::strcmp(currentPlayer, playerTwo) == 0) {
  } else {
    // This should never happen.
    status = "unknown player";
    statusSize = Helpers::getFitableSize(
        status.c_str(), DEFAULT_STATUS_TEXT_SIZE, GetScreenWidth());
  }

  if (cachedPos != pos) {
    prevPos = cachedPos;
    cachedPos = pos;
  }
}

void Game::do_update() {
  update_impl();
  draw_impl();
}

void Game::screen_size_changed() { flags.set(13); }

void Game::update_impl() {
  const float dt = GetFrameTime();

  if (flags.test(13)) {
    flags.reset(13);
    statusSize =
        !status.empty()
            ? Helpers::getFitableSize(status.c_str(), DEFAULT_STATUS_TEXT_SIZE,
                                      GetScreenWidth())
            : DEFAULT_STATUS_TEXT_SIZE;
  }

  if (prevPos != cachedPos) {
    scoreChangeTimer -= dt;
    if (scoreChangeTimer <= 0) {
      scoreChangeTimer = SCORE_CHANGE_TIMER_MAX;
      prevPos = cachedPos;
    }
  }

  if (flags.test(2)) {
    if (!flags.test(4) && Helpers::isValidChoice(picked[0]) &&
        Helpers::isValidChoice(picked[1]) &&
        Helpers::isValidChoice(picked[2]) &&
        Helpers::isValidChoice(opponentPicked[0]) &&
        Helpers::isValidChoice(opponentPicked[1]) &&
        Helpers::isValidChoice(opponentPicked[2])) {
      flags.set(4);
      flags.set(5);
      resultsTimer = RESULTS_TIMER_MAX;
    } else if (flags.test(4)) {
      resultsTimer -= dt;
      if (resultsTimer <= 0.0F) {
        resultsTimer = RESULTS_TIMER_MAX;
        if (!flags.test(6)) {
          flags.set(6);
          flags.set(9);
        } else if (!flags.test(7)) {
          flags.set(7);
          flags.set(9);
        } else if (!flags.test(8)) {
          flags.set(8);
          flags.set(9);
        } else {
          flags.reset(4);
          flags.reset(5);
          flags.reset(6);
          flags.reset(7);
          flags.reset(8);
          flags.reset(9);
          flags.reset(10);
          flags.reset(11);
          picked[0] = '?';
          picked[1] = '?';
          picked[2] = '?';
          opponentPicked[0] = '?';
          opponentPicked[1] = '?';
          opponentPicked[2] = '?';
        }
      }
    }

    if (IsMouseButtonPressed(0)) {
      // TODO DEBUG
      // if (GetTouchX() >= 0 && GetTouchX() <= 100 && GetTouchY() >= 0 &&
      //    GetTouchY() <= 100) {
      //  std::clog << "flags: " << flags.to_string().substr(32 - 14)
      //            << std::endl;
      //}
    }
    return;
  }

  readyTimer -= dt;
  if (readyTimer <= 0.0F) {
    readyTimer = READY_TIMER_MAX;
    flags.flip(1);
  }

  if (IsMouseButtonPressed(0) && !flags.test(0)) {
    int triple_single_width = GetScreenWidth() / 3.0F + 0.5F;
    if (triple_single_width > ICON_MAX_WIDTH) {
      triple_single_width = ICON_MAX_WIDTH;
    }

    // selected Rock
    if (GetTouchX() >= 0 && GetTouchX() <= GetScreenWidth() / 3 &&
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
    else if (GetTouchX() >= GetScreenWidth() / 3 &&
             GetTouchX() <= GetScreenWidth() * 2 / 3 &&
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
    else if (GetTouchX() >= GetScreenWidth() * 2 / 3 &&
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
    else if (GetTouchX() >= 0 && GetTouchX() <= GetScreenWidth() / 3 &&
             GetTouchY() >= GetScreenHeight() - triple_single_width * 2 &&
             GetTouchY() <= GetScreenHeight() - triple_single_width) {
      picked[0] = 0;
    }
    // selected Slot 1
    else if (GetTouchX() >= GetScreenWidth() / 3 &&
             GetTouchX() <= GetScreenWidth() * 2 / 3 &&
             GetTouchY() >= GetScreenHeight() - triple_single_width * 2 &&
             GetTouchY() <= GetScreenHeight() - triple_single_width) {
      picked[1] = 0;
    }
    // selected Slot 2
    else if (GetTouchX() >= GetScreenWidth() * 2 / 3 &&
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
      if (flags.test(4)) {
        status.clear();
        statusSize = DEFAULT_STATUS_TEXT_SIZE;
      } else {
        status = "Waiting...";
        statusSize = Helpers::getFitableSize(
            status.c_str(), DEFAULT_STATUS_TEXT_SIZE, GetScreenWidth());
      }
    } else {
      status = "Hit Ready!";
      statusSize = Helpers::getFitableSize(
          status.c_str(), DEFAULT_STATUS_TEXT_SIZE, GetScreenWidth());
    }
  } else {
    status = "Pick Moves!";
    statusSize = Helpers::getFitableSize(
        status.c_str(), DEFAULT_STATUS_TEXT_SIZE, GetScreenWidth());
  }

  if (flags.test(0) && flags.test(3) && flags.test(10) && flags.test(11)) {
    char buf[6] = {picked[0], 0, picked[1], 0, picked[2], 0};
    call_js_set_choices(&buf[0], &buf[2], &buf[4]);
    flags.reset(3);
    flags.set(4);
  } else if (flags.test(0) && !flags.test(3) && flags.test(4)) {
    // updates for result animations

    if (flags.test(5)) {
      flags.reset(5);
      flags.reset(9);
      resultsTimer = RESULTS_TIMER_MAX;
    } else if (flags.test(9)) {
      if (!flags.test(8)) {
        call_js_set_ready();
        flags.reset(9);
        flags.set(5);
      } else {
      }
    } else {
      resultsTimer -= dt;
      if (resultsTimer <= 0) {
        resultsTimer = RESULTS_TIMER_MAX;
        if (!flags.test(6)) {
          flags.set(6);
          flags.set(9);
        } else if (!flags.test(7)) {
          flags.set(7);
          flags.set(9);
        } else if (!flags.test(8)) {
          flags.set(8);
          flags.set(9);
        }
      }
    }
  }

  if (flags.test(12) && flags.test(10) && flags.test(11) &&
      prevPos == cachedPos && is_choices_set() && is_opponent_choices_set()) {
    flags.reset(12);
    call_js_request_update();
    // std::cout << "Requesting update..." << std::endl; // TODO DEBUG
  }

  requestTimer -= dt;
  if (requestTimer <= 0.0F) {
    requestTimer = REQUEST_TIMER_MAX;
    if (flags.test(10) && flags.test(11)) {
      call_js_request_update();
      // std::cout << "Requesting update (timer)..." << std::endl; // TODO DEBUG
    }
  }

  if (flags.test(0) && flags.test(6) && flags.test(7) && flags.test(8)) {
    // std::cout << "Resetting for next round" << (isPlayerOne ? " (1) " : " (2)
    // ") << "..." << std::endl; // TODO DEBUG
    flags.reset(0);
    flags.reset(1);
    flags.reset(3);
    flags.reset(4);
    flags.reset(5);
    flags.reset(6);
    flags.reset(7);
    flags.reset(8);
    flags.reset(9);
    flags.reset(10);
    flags.reset(11);
    flags.reset(12);

    readyTimer = 0;
    resultsTimer = RESULTS_TIMER_MAX;

    picked[0] = 0;
    picked[1] = 0;
    picked[2] = 0;

    opponentPicked[0] = 0;
    opponentPicked[1] = 0;
    opponentPicked[2] = 0;

    // TODO DEBUG
    // std::clog << "flags: " << flags.to_string().substr(32 - 13) << std::endl;
  }
}

void Game::draw_impl() {
  if (flags.test(2)) {
    BeginDrawing();
    ClearBackground(BLACK);
    draw_score();
    DrawText(status.c_str(), 0, 20, statusSize, RAYWHITE);

    if (flags.test(4)) {
      if (flags.test(5)) {
        flags.reset(5);
      }

      float triple_single_width = GetScreenWidth() / 3.0F;
      draw_reveal_choices(opponentPicked, triple_single_width);
      draw_reveal_choices(picked, triple_single_width * 2.0F);
    }

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
      draw_choice(0, picked[0], false, triple_single_width * 2.0F, WHITE);
      draw_choice(1, picked[1], false, triple_single_width * 2.0F, WHITE);
      draw_choice(2, picked[2], false, triple_single_width * 2.0F, WHITE);
      draw_reveal_choices(opponentPicked, triple_single_width);
    } else { // flags.test(0)
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
        if (picked[i] != 0) {
          draw_choice(i, picked[i], true,
                      (float)GetScreenHeight() - triple_single_width * 2.0F);
        }
      }

      DrawRectangle(0, GetScreenHeight() - triple_single_width,
                    GetScreenWidth(), triple_single_width,
                    {127, 127, 127, 255});
      draw_choice(0, 'r', true, (float)GetScreenHeight() - triple_single_width);
      draw_choice(1, 'p', true, (float)GetScreenHeight() - triple_single_width);
      draw_choice(2, 's', true, (float)GetScreenHeight() - triple_single_width);
    }
  }
  draw_score();
  DrawText(status.c_str(), 0, 20, statusSize, RAYWHITE);
  EndDrawing();
}

void Game::draw_choice(const unsigned int idx, const char choice,
                       const bool using_triple, const float y,
                       const Color color) {
  if (!spriteSheet.has_value()) {
    return;
  }
  float x = 0.0F;
  float width = ICON_MAX_WIDTH;
  draw_helper_coord(&x, &width, idx, using_triple);

  switch (choice) {
  case 'r':
    DrawTexturePro(spriteSheet.value(),
                   {ROCK_DIMS[0], ROCK_DIMS[1], ROCK_DIMS[2], ROCK_DIMS[3]},
                   {x, y, width, width}, {0.0F, 0.0F}, 0.0F, color);
    break;
  case 'p':
    DrawTexturePro(spriteSheet.value(),
                   {PAPER_DIMS[0], PAPER_DIMS[1], PAPER_DIMS[2], PAPER_DIMS[3]},
                   {x, y, width, width}, {0.0F, 0.0F}, 0.0F, color);
    break;
  case 's':
    DrawTexturePro(spriteSheet.value(),
                   {SCISSORS_DIMS[0], SCISSORS_DIMS[1], SCISSORS_DIMS[2],
                    SCISSORS_DIMS[3]},
                   {x, y, width, width}, {0.0F, 0.0F}, 0.0F, color);
    break;
  case '?':
    DrawTexturePro(spriteSheet.value(),
                   {QUESTIONMARK_DIMS[0], QUESTIONMARK_DIMS[1],
                    QUESTIONMARK_DIMS[2], QUESTIONMARK_DIMS[3]},
                   {x, y, width, width}, {0.0F, 0.0F}, 0.0F, color);
    break;
  default:
    // Should never happen.
    std::cerr << "WARNING: Invalid choice passed to draw_choice()!"
                 " (value is \""
              << choice << "\" or \"" << (int)choice << "\")" << std::endl;
    break;
  }
}

void Game::draw_qm(const unsigned int idx, const bool using_triple,
                   const float y, const Color color) {
  if (!spriteSheet.has_value()) {
    return;
  }
  float x = 0.0F;
  float width = ICON_MAX_WIDTH;
  draw_helper_coord(&x, &width, idx, using_triple);

  DrawTexturePro(spriteSheet.value(),
                 {QUESTIONMARK_DIMS[0], QUESTIONMARK_DIMS[1],
                  QUESTIONMARK_DIMS[2], QUESTIONMARK_DIMS[3]},
                 {x, y, width, width}, {0.0F, 0.0F}, 0.0F, color);
}

void Game::draw_helper_coord(float *x, float *width, const unsigned int idx,
                             const bool using_triple) {
  if (x) {
    *x = 0.0F;
    *width = ICON_MAX_WIDTH;
    if (using_triple) {
      *width = GetScreenWidth() / 3.0F;
      if (*width > ICON_MAX_WIDTH) {
        *width = ICON_MAX_WIDTH;
      }

      switch (idx) {
      case 0:
        *x = 0.0F;
        break;
      case 1:
        *x = (GetScreenWidth() - *width) / 2.0F;
        break;
      case 2:
        *x = GetScreenWidth() - *width;
        break;
      default:
        // Should never happen
        std::cerr << "WARNING: Invalid idx passed to draw_helper_coord()!"
                  << std::endl;
        return;
      }
    } else {
      *width = GetScreenWidth() / 5.0F;
      if (*width > ICON_MAX_WIDTH) {
        *width = ICON_MAX_WIDTH;
      }

      switch (idx) {
      case 0:
        *x = GetScreenWidth() - *width * 4.0F;
        break;
      case 1:
        *x = GetScreenWidth() - *width * 3.0F;
        break;
      case 2:
        *x = GetScreenWidth() - *width * 2.0F;
        break;
      default:
        // Should never happen.
        std::cerr << "WARNING: Invalid idx passed to draw_helper_coord()!"
                  << std::endl;
        return;
      }
    }
  }
}

bool Game::is_choices_set() const {
  return picked[0] != 0 && picked[1] != 0 && picked[2] != 0;
}

bool Game::is_opponent_choices_set() const {
  return opponentPicked[0] != 0 && opponentPicked[1] != 0 &&
         opponentPicked[2] != 0 && opponentPicked[0] != '?' &&
         opponentPicked[1] != '?' && opponentPicked[2] != '?';
}

void Game::draw_score() const {
  char buf[6] = {prevPos < 0 ? '-' : ' ',
                 prevPos < 0 ? (char)('0' - prevPos) : (char)('0' + prevPos),
                 0,
                 cachedPos < 0 ? '-' : ' ',
                 cachedPos < 0 ? (char)('0' - cachedPos)
                               : (char)('0' + cachedPos),
                 0};
  if (prevPos != cachedPos) {
    float ratio = 1.0F - scoreChangeTimer / SCORE_CHANGE_TIMER_MAX;
    DrawText(&buf[3], 0, 0, 20,
             {255, 255, 255, (unsigned char)(ratio * 255.0F)});
    DrawText(buf, 0, 0, 20,
             {255, 255, 255, (unsigned char)((1.0F - ratio) * 255.0F)});
  } else {
    DrawText(&buf[3], 0, 0, 20, WHITE);
  }
}

void Game::draw_reveal_choices(const char p[3], const float y) {
  float ratio = 1.0F - resultsTimer / RESULTS_TIMER_MAX;
  char otherPicked = Helpers::isValidChoice(p[0]) ? p[0] : '?';
  if (!flags.test(6)) {
    if (ratio < 1.0F) {
      draw_choice(0, otherPicked, false, y,
                  {255, 255, 255, (unsigned char)(ratio * 255.0F)});
      draw_qm(0, false, y,
              {255, 255, 255, (unsigned char)((1.0F - ratio) * 255.0f)});
    } else {
      draw_choice(0, otherPicked, false, y);
    }
  } else {
    draw_choice(0, otherPicked, false, y);
  }

  otherPicked = Helpers::isValidChoice(p[1]) ? p[1] : '?';
  if (!flags.test(7)) {
    if (!flags.test(6)) {
      draw_qm(1, false, y, WHITE);
    } else if (ratio < 1.0F) {
      draw_choice(1, otherPicked, false, y,
                  {255, 255, 255, (unsigned char)(ratio * 255.0F)});
      draw_qm(1, false, y,
              {255, 255, 255, (unsigned char)((1.0F - ratio) * 255.0f)});
    } else {
      draw_choice(1, otherPicked, false, y);
    }
  } else {
    draw_choice(1, otherPicked, false, y);
  }

  otherPicked = Helpers::isValidChoice(p[2]) ? p[2] : '?';
  if (!flags.test(8)) {
    if (!flags.test(7)) {
      draw_qm(2, false, y, WHITE);
    } else if (ratio < 1.0F) {
      draw_choice(2, otherPicked, false, y,
                  {255, 255, 255, (unsigned char)(ratio * 255.0F)});
      draw_qm(2, false, y,
              {255, 255, 255, (unsigned char)((1.0F - ratio) * 255.0f)});
    } else {
      draw_choice(2, otherPicked, false, y);
    }
  } else {
    draw_choice(2, otherPicked, false, y);
  }
}
