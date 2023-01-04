#ifndef ROCK_PAPER_SCISSORS_DUEL_CONSTANTS_H_
#define ROCK_PAPER_SCISSORS_DUEL_CONSTANTS_H_

constexpr int DEFAULT_SCREEN_WIDTH = 500;
constexpr int DEFAULT_SCREEN_HEIGHT = 800;

constexpr int ROCK_DIMS[4] = {0, 0, 32, 32};
constexpr int PAPER_DIMS[4] = {32, 0, 32, 32};
constexpr int SCISSORS_DIMS[4] = {64, 0, 32, 32};
constexpr int READY_DIMS[4] = {0, 32, 192, 56};
constexpr int QUESTIONMARK_DIMS[4] = {0, 88, 40, 56};
constexpr int EXCLAMATIONMARKS_DIMS[4] = {40, 88, 32, 56};
constexpr int OK_DIMS[4] = {72, 88, 80, 56};

constexpr int ICON_MAX_WIDTH = 100;

constexpr float READY_TIMER_MAX = 1.0F;

constexpr float RESULTS_TIMER_MAX = 1.0F;

constexpr float SCORE_CHANGE_TIMER_MAX = 1.0F;

constexpr float REQUEST_TIMER_MAX = 3.0F;

constexpr int DEFAULT_STATUS_TEXT_SIZE = 30;

#endif
