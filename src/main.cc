// emscripten includes
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#else
#include <random>
#endif

// third party includes
#include <raylib.h>

// local includes
#include "constants.h"

#ifdef __EMSCRIPTEN__
// em exposed fns
extern "C" {

void EMSCRIPTEN_KEEPALIVE game_visual_update(
    const char *playerOne, const char *playerTwo, const char *currentPlayer,
    char first_first, char first_second, char first_third, char second_first,
    char second_second, char second_third, bool first_ready, bool second_ready,
    int pos) {
  // TODO
}

} // end em exposed functions

EM_JS(void, js_set_ready, (), { Rune.actions.set_ready(); });

EM_JS(void, js_set_choices,
      (const char *first, const char *second, const char *third), {
        Rune.actions.set_choices(UTF8ToString(first), UTF8ToString(second),
                                 UTF8ToString(third));
      });
#endif

int main() {
#ifdef __EMSCRIPTEN__
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
             "RockPaperScissorsDuel");
#else
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "RPSDuel_Native");
#endif

#ifdef __EMSCRIPTEN__
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Testing...", 100, 100, 30, RAYWHITE);
    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
#endif

  return 0;
}
