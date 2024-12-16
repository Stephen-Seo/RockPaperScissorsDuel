#include "ems.h"

#include <random>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/fetch.h>
#include <emscripten/html5.h>

#include <cstring>

#include "game_renderer.h"

EM_JS(void, js_set_ready, (), { Rune.actions.set_ready("unused"); });

EM_JS(void, js_set_choices,
      (const char *first, const char *second, const char *third), {
        Rune.actions.set_choices({
          first : UTF8ToString(first),
          second : UTF8ToString(second),
          third : UTF8ToString(third)
        });
      });

EM_JS(void, js_request_update, (), { Rune.actions.request_update("unused"); });

EM_JS(void, js_set_matchup_done, (),
      { Rune.actions.set_matchup_done("unused"); });

EM_JS(int, canvas_get_width, (),
      { return document.getElementById("canvas").clientWidth; });

EM_JS(int, canvas_get_height, (),
      { return document.getElementById("canvas").clientHeight; });

EM_JS(float, get_random, (), { return Math.random(); });

EM_JS(void, js_rune_init, (), {
  console.log("WASM loaded, calling Rune init...");
  do_rune_init();
  console.log("Called Rune init.")
});
#endif

#include <iostream>

// void call_js_set_ready() {
// #ifdef __EMSCRIPTEN__
//   js_set_ready();
// #else
//   std::clog << "WARNING: emscripten not enabled, cannot call js_set_ready()!"
//             << std::endl;
// #endif
// }

// void call_js_set_choices(const char *first, const char *second,
//                          const char *third) {
// #ifdef __EMSCRIPTEN__
//   js_set_choices(first, second, third);
// #else
//   std::clog << "WARNING: emscripten not enabled, cannot call
//   js_set_choices()!"
//             << std::endl;
// #endif
// }

// void call_js_request_update() {
// #ifdef __EMSCRIPTEN__
//   js_request_update();
// #else
//   std::clog
//       << "WARNING: emscripten not enabled, cannot call js_request_update()!"
//       << std::endl;
// #endif
// }

void call_js_set_matchup_done() {
#ifdef __EMSCRIPTEN__
  js_set_matchup_done();
#else
  // std::clog
  //     << "WARNING: emscripten not enabled, cannot call
  //     js_set_matchup_done()!"
  //     << std::endl;
#endif
}

int call_js_get_canvas_width() {
#ifdef __EMSCRIPTEN__
  return canvas_get_width();
#else
  return 800;
#endif
}

int call_js_get_canvas_height() {
#ifdef __EMSCRIPTEN__
  return canvas_get_height();
#else
  return 500;
#endif
}

float call_js_get_random() {
#ifdef __EMSCRIPTEN__
  return get_random();
#else

  // TODO Maybe persist random state.

  std::random_device rd{};
  std::default_random_engine re(rd());
  std::uniform_real_distribution<float> dist(0.0F, 1.0F);

  return dist(re);
#endif
}

void call_js_init_rune() {
#ifdef __EMSCRIPTEN__
  js_rune_init();
#endif
}

// #ifdef __EMSCRIPTEN__
// void fetch_avatar1_url_success(emscripten_fetch_t *fetch) {
//   GameRenderer *game = (GameRenderer *)fetch->userData;
//   game->avatar1_loaded(fetch->numBytes, fetch->data);
//   emscripten_fetch_close(fetch);
// }
//
// void fetch_avatar1_url_fail(emscripten_fetch_t *fetch) {
//   GameRenderer *game = (GameRenderer *)fetch->userData;
//   game->avatar1_loaded(0, nullptr);
//   emscripten_fetch_close(fetch);
// }
//
// void fetch_avatar2_url_success(emscripten_fetch_t *fetch) {
//   GameRenderer *game = (GameRenderer *)fetch->userData;
//   game->avatar2_loaded(fetch->numBytes, fetch->data);
//   emscripten_fetch_close(fetch);
// }
//
// void fetch_avatar2_url_fail(emscripten_fetch_t *fetch) {
//   GameRenderer *game = (GameRenderer *)fetch->userData;
//   game->avatar2_loaded(0, nullptr);
//   emscripten_fetch_close(fetch);
// }
// #endif

// void fetch_avatar1_url(const char *url, void *game_ptr) {
// #ifdef __EMSCRIPTEN__
//   emscripten_fetch_attr_t attr;
//   emscripten_fetch_attr_init(&attr);
//   std::strcpy(attr.requestMethod, "GET");
//   attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
//   attr.onsuccess = fetch_avatar1_url_success;
//   attr.onerror = fetch_avatar1_url_fail;
//   attr.userData = game_ptr;
//   emscripten_fetch(&attr, url);
// #endif
// }
//
// void fetch_avatar2_url(const char *url, void *game_ptr) {
// #ifdef __EMSCRIPTEN__
//   emscripten_fetch_attr_t attr;
//   emscripten_fetch_attr_init(&attr);
//   std::strcpy(attr.requestMethod, "GET");
//   attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
//   attr.onsuccess = fetch_avatar2_url_success;
//   attr.onerror = fetch_avatar2_url_fail;
//   attr.userData = game_ptr;
//   emscripten_fetch(&attr, url);
// #endif
// }
