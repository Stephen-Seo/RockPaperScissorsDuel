#include "game.h"

// standard library includes
#include <cstring>

// third party includes
#include <raylib.h>

Game::Game() : status("Unknown status"), prevPos(0), cachedPos(0) {}

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
    status = "spectator";
  } else if (std::strcmp(currentPlayer, playerOne) == 0) {
    status = "player one";
  } else if (std::strcmp(currentPlayer, playerTwo) == 0) {
    status = "player two";
  } else {
    status = "unknown player";
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

void Game::update_impl() {}

void Game::draw_impl() {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("Testing...", 100, 100, 30, RAYWHITE);
  DrawText(status.c_str(), 0, 200, 30, RAYWHITE);
  EndDrawing();
}
