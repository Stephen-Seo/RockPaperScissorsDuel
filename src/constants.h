#ifndef ROCK_PAPER_SCISSORS_DUEL_CONSTANTS_H_
#define ROCK_PAPER_SCISSORS_DUEL_CONSTANTS_H_

extern const float PI_F;

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

// Renderer3D

constexpr float OVERVIEW_TIMER_MAX = 14.0F;

constexpr float OVERVIEW_LEFT_X = -20.0F;
constexpr float OVERVIEW_LEFT_Y = 5.0F;
constexpr float OVERVIEW_LEFT_Z = 20.0F;

constexpr float OVERVIEW_RIGHT_X = 20.0F;
constexpr float OVERVIEW_RIGHT_Y = 5.0F;
constexpr float OVERVIEW_RIGHT_Z = 20.0F;

constexpr float OVERVIEW_UP_L_B_X = -4.0F;
constexpr float OVERVIEW_UP_L_B_Y = 10.0F;
constexpr float OVERVIEW_UP_L_B_Z = 10.0F;
constexpr float OVERVIEW_UP_L_E_X = -20.0F;
constexpr float OVERVIEW_UP_L_E_Y = 20.0F;
constexpr float OVERVIEW_UP_L_E_Z = 5.0F;

constexpr float OVERVIEW_UP_R_B_X = -OVERVIEW_UP_L_B_X;
constexpr float OVERVIEW_UP_R_B_Y = OVERVIEW_UP_L_B_Y;
constexpr float OVERVIEW_UP_R_B_Z = OVERVIEW_UP_L_B_Z;
constexpr float OVERVIEW_UP_R_E_X = -OVERVIEW_UP_L_E_X;
constexpr float OVERVIEW_UP_R_E_Y = OVERVIEW_UP_L_E_Y;
constexpr float OVERVIEW_UP_R_E_Z = OVERVIEW_UP_L_E_Z;

constexpr float OVERVIEW_C_B_X = 0.0F;
constexpr float OVERVIEW_C_B_Y = 5.0F;
constexpr float OVERVIEW_C_B_Z = 9.0F;
constexpr float OVERVIEW_C_E_X = 0.0F;
constexpr float OVERVIEW_C_E_Y = 7.0F;
constexpr float OVERVIEW_C_E_Z = 22.0F;

constexpr float OVERVIEW_ORBIT_RADIUS = 12.0F;
constexpr float OVERVIEW_ORBIT_Y = 7.0F;
constexpr float OVERVIEW_ORBIT_MODIFIER = 0.9F;

#endif
