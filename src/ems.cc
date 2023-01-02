#include "ems.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>

EM_JS(void, js_set_ready, (), { Rune.actions.set_ready("unused"); });

EM_JS(void, js_set_choices,
      (const char *first, const char *second, const char *third), {
        Rune.actions.set_choices(UTF8ToString(first), UTF8ToString(second),
                                 UTF8ToString(third));
      });

EM_JS(int, canvas_get_width, (),
      { return document.getElementById("canvas").clientWidth; });

EM_JS(int, canvas_get_height, (),
      { return document.getElementById("canvas").clientHeight; });
#else
#include <iostream>
#endif

void call_js_set_ready() {
#ifdef __EMSCRIPTEN__
  js_set_ready();
#else
  std::clog << "WARNING: emscripten not enabled, cannot call js_set_ready()!"
            << std::endl;
#endif
}

void call_js_set_choices(const char *first, const char *second,
                         const char *third) {
#ifdef __EMSCRIPTEN__
  js_set_choices(first, second, third);
#else
  std::clog << "WARNING: emscripten not enabled, cannot call js_set_choices()!"
            << std::endl;
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
