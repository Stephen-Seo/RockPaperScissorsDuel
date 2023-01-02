#include "game.h"

// third party includes
#include <raylib.h>

Game::Game() {}

void Game::update_state(const char *playerOne, const char *playerTwo,
                        const char *currentPlayer, char first_first,
                        char first_second, char first_third, char second_first,
                        char second_second, char second_third, bool first_ready,
                        bool second_ready, int pos) {}

void Game::do_update() {
  update_impl();
  draw_impl();
}

void Game::update_impl() {}

void Game::draw_impl() {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("Testing...", 100, 100, 30, RAYWHITE);
  EndDrawing();
}
