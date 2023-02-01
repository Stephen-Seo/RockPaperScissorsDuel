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
constexpr int ICON_MAX_WIDTH_2 = 70;

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

constexpr float BUTTON_COLOR_TIME = 9.0F;
constexpr float BUTTON_COLOR_MIN = 40.0F;
constexpr float BUTTON_COLOR_MAX = 180.0F;

constexpr float SCREEN_SHAKE_DEFAULT_FACTOR = 7.0F;
constexpr float SCREEN_SHAKE_TIME = 0.3F;

// src/3D/

constexpr float QM_ANGLE_TIMER_VARIANCE = 2.0F;
constexpr float QM_Y_TIMER_VARIANCE = 2.0F;
constexpr float QM_MAX_ANGLE_OFFSET = 30.0F;
constexpr float QM_MAX_Y_OFFSET = 0.3F;
constexpr float QM_ANGLE_TIMER_MAX = 5.0F;
constexpr float QM_Y_TIMER_MAX = 3.5F;

constexpr float MODEL_SHRINK_TIME = 0.8F;
constexpr float MODEL_GROW_TIME = 0.8F;

constexpr float MODEL_ATTACK_TIME_0 = 0.4F;
constexpr float MODEL_ATTACK_TIME_1 = 0.3F;
constexpr float MODEL_ATTACK_TIME_2 = 0.4F;
constexpr float MODEL_ATTACK_0_X = 0.0F;
constexpr float MODEL_ATTACK_0_Y = 2.0F;
constexpr float MODEL_ATTACK_1_X = 1.0F;
constexpr float MODEL_ATTACK_1_Y = 0.2F;
constexpr float MODEL_ATTACK_2_X = 0.0F;
constexpr float MODEL_ATTACK_2_Y = 0.0F;

constexpr float MODEL_ATTACK_ANGLE_START = 0.0F;
constexpr float MODEL_ATTACK_ANGLE_END = 90.0F;

constexpr float MODEL_FALLING_2D_DX = 90.0F;
constexpr float MODEL_FALLING_2D_DY = -40.0F;
constexpr float MODEL_FALLING_2D_DDY = 180.0F;
constexpr float MODEL_FALLING_2D_DA = 270.0F;

constexpr float MODEL_STILL_FALLING_WAIT_TIME = 0.5F;

#endif
