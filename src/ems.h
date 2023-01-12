#ifndef ROCK_PAPER_SCISSORS_DUEL_EMSCRIPTEN_H_
#define ROCK_PAPER_SCISSORS_DUEL_EMSCRIPTEN_H_

extern void call_js_set_ready();
extern void call_js_set_choices(const char *first, const char *second,
                                const char *third);
extern void call_js_request_update();
extern int call_js_get_canvas_width();
extern int call_js_get_canvas_height();
extern float call_js_get_random();

#endif
