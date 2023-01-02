// emscripten includes
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

#include "ems.h"
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

EM_BOOL resize_event_callback(int event_type, const EmscriptenUiEvent *event,
                              void *ud) {
  if (event_type == EMSCRIPTEN_EVENT_RESIZE) {
    SetWindowSize(call_js_get_canvas_width(), call_js_get_canvas_height());
  }
  return false;
}
#endif

void game_update(void *game_ptr) {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawText("Testing...", 100, 100, 30, RAYWHITE);
  EndDrawing();
}

int main() {
#ifdef __EMSCRIPTEN__
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
             "RockPaperScissorsDuel");
#else
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "RPSDuel_Native");
#endif

#ifdef __EMSCRIPTEN__
  SetWindowSize(call_js_get_canvas_width(), call_js_get_canvas_height());

  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, false,
                                 resize_event_callback);

  // TODO set game ptr
  emscripten_set_main_loop_arg(game_update, nullptr, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    game_update(nullptr);
  }

  CloseAudioDevice();
  CloseWindow();
#endif

  return 0;
}
