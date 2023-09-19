#ifndef ROCK_PAPER_SCISSORS_DUEL_EMSCRIPTEN_H_
#define ROCK_PAPER_SCISSORS_DUEL_EMSCRIPTEN_H_

extern void call_js_set_ready();
extern void call_js_set_choices(const char *first, const char *second,
                                const char *third);
// extern void call_js_request_update();
extern void call_js_set_matchup_done();
extern int call_js_get_canvas_width();
extern int call_js_get_canvas_height();
extern float call_js_get_random();
extern void call_js_init_rune();

extern void fetch_avatar1_url(const char *url, void *game_ptr);
extern void fetch_avatar2_url(const char *url, void *game_ptr);

#endif
