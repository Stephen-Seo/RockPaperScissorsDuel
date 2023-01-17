// emscripten includes
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

#include "ems.h"
#else
#include <random>
#endif

// standard library includes
#include <memory>

// third party includes
#include <raylib.h>

// local includes
#include "3d_renderer.h"
#include "basic_renderer.h"
#include "constants.h"
#include "game_renderer.h"

#ifdef __EMSCRIPTEN__
static void *global_game_ptr = nullptr;

// em exposed fns
extern "C" {

int EMSCRIPTEN_KEEPALIVE game_visual_update(
    const char *playerOne, const char *playerTwo, const char *currentPlayer,
    char first_first, char first_second, char first_third, char second_first,
    char second_second, char second_third, bool first_ready, bool second_ready,
    int pos, int matchup_idx, bool gameover, bool matchup_started) {
  ((GameRenderer *)global_game_ptr)
      ->update_state(playerOne, playerTwo, currentPlayer, first_first,
                     first_second, first_third, second_first, second_second,
                     second_third, first_ready, second_ready, pos, matchup_idx,
                     gameover, matchup_started);
  return 0;
}

}  // end em exposed functions

EM_BOOL resize_event_callback(int event_type, const EmscriptenUiEvent *event,
                              void *ud) {
  if (event_type == EMSCRIPTEN_EVENT_RESIZE) {
    SetWindowSize(call_js_get_canvas_width(), call_js_get_canvas_height());
    ((GameRenderer *)ud)->screen_size_changed();
  }
  return false;
}
#endif

void game_update(void *game_ptr) { ((GameRenderer *)game_ptr)->do_update(); }

int main() {
#ifdef __EMSCRIPTEN__
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
             "RockPaperScissorsDuel");
#else
  InitWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "RPSDuel_Native");
#endif

  std::unique_ptr<GameRenderer> renderer = std::make_unique<Renderer3D>();

#ifdef __EMSCRIPTEN__
  global_game_ptr = renderer.get();

  SetWindowSize(call_js_get_canvas_width(), call_js_get_canvas_height());

  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, renderer.get(),
                                 false, resize_event_callback);

  emscripten_set_main_loop_arg(game_update, renderer.get(), 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    game_update(renderer.get());
  }

  renderer.reset();

  CloseAudioDevice();
  CloseWindow();
#endif

  return 0;
}
