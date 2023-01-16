#include "3d_renderer.h"

// standard library includes
#include <raylib.h>

#include <cmath>
#include <cstring>
#include <iostream>

// local includes
#include "3d/a3f_conv.h"
#include "constants.h"
#include "ems.h"
#include "helpers.h"

Renderer3D::Renderer3D()
    : qms{},
      root_pos{0.0F, 0.0F, 0.0F},
      p1_pos{-1.0F, 0.0F, 0.0F},
      p2_pos{1.0F, 0.0F, 0.0F},
      overview_timer(OVERVIEW_TIMER_MAX),
      button_color_timer(BUTTON_COLOR_TIME),
      choices{'?', '?', '?'},
      opponent_choices{'?', '?', '?'} {
  camera.position.x = 0.0F;
  camera.position.y = 5.0F;
  camera.position.z = 10.0F;

  camera.up.x = 0.0F;
  camera.up.y = 1.0F;
  camera.up.z = 0.0F;

  camera.target.x = 0.0F;
  camera.target.y = 0.0F;
  camera.target.z = 0.0F;

  camera.fovy = 45.0F;

  camera.projection = CAMERA_PERSPECTIVE;

  SetCameraMode(camera, CAMERA_CUSTOM);

  spriteSheet = LoadTexture("resources/rockpaperscissorsSpriteSheet.png");

  skybox_texture = LoadTexture("resources/skybox.gif");
  platform_texture = LoadTexture("resources/platform_texture.png");
  qm_texture = LoadTexture("resources/question_mark_texture.png");
  rock_texture = LoadTexture("resources/rock_texture.png");
  paper_texture = LoadTexture("resources/paper_texture.png");
  scissors_texture = LoadTexture("resources/scissors_texture.png");

  skybox_model = LoadModel("resources/skybox.obj");
  platform_model = LoadModel("resources/platform.obj");
  qm_model = LoadModel("resources/question_mark.obj");
  rock_model = LoadModel("resources/rock.obj");
  paper_model = LoadModel("resources/paper.obj");
  scissors_model = LoadModel("resources/scissors.obj");

  skybox_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = skybox_texture;
  platform_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
      platform_texture;
  qm_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = qm_texture;
  rock_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = rock_texture;
  paper_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = paper_texture;
  scissors_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
      scissors_texture;

  flags.set(1);
  flags.set(4);
  flags.set(5);
  flags.set(7);

  qms.at(0).set_model(&qm_model);
  qms.at(0).set_pos({-1.0F, 0.0F, 0.0F});
  qms.at(0).set_color_g(0);
  qms.at(0).set_color_b(0);
  qms.at(1).set_model(&qm_model);
  qms.at(1).set_pos({1.0F, 0.0F, 0.0F});
  qms.at(1).set_color_r(0);
  qms.at(1).set_color_g(0);
}

Renderer3D::~Renderer3D() {
  UnloadTexture(skybox_texture);
  UnloadTexture(platform_texture);
  UnloadTexture(qm_texture);
  UnloadTexture(rock_texture);
  UnloadTexture(paper_texture);
  UnloadTexture(scissors_texture);

  UnloadModel(skybox_model);
  UnloadModel(platform_model);
  UnloadModel(qm_model);
  UnloadModel(rock_model);
  UnloadModel(paper_model);
  UnloadModel(scissors_model);
}

void Renderer3D::update_state(const char *playerOne, const char *playerTwo,
                              const char *currentPlayer, char first_first,
                              char first_second, char first_third,
                              char second_first, char second_second,
                              char second_third, bool first_ready,
                              bool second_ready, int pos, int matchup_idx,
                              bool gameover) {
  if (std::strcmp(playerOne, currentPlayer) == 0) {
    flags.set(2);
    flags.reset(3);
  } else if (std::strcmp(playerTwo, currentPlayer) == 0) {
    flags.reset(2);
    flags.reset(3);
  } else {
    flags.reset(2);
    flags.set(3);
  }
}

void Renderer3D::do_update() {
  update_impl();
  draw_impl();
}

void Renderer3D::screen_size_changed() {}

void Renderer3D::update_impl() {
  const float dt = GetFrameTime();
  const float triple_single_width = GetScreenWidth() / 3.0F;
  float actual_width = triple_single_width;
  if (actual_width > (float)ICON_MAX_WIDTH) {
    actual_width = ICON_MAX_WIDTH;
  }
  float actual_width2 = triple_single_width;
  if (actual_width2 > (float)ICON_MAX_WIDTH_2) {
    actual_width2 = ICON_MAX_WIDTH_2;
  }

  if (flags.test(0)) {
  } else {
    overview_timer -= dt;
    if (overview_timer <= 0.0F) {
      overview_timer += OVERVIEW_TIMER_MAX;
      const decltype(flags) prevFlags = flags;
      const auto is_same = [](const decltype(flags) &l,
                              const decltype(flags) &r) {
        return l.test(4) == r.test(4) && l.test(5) == r.test(5) &&
               l.test(6) == r.test(6);
      };
      while (is_same(prevFlags, flags) ||
             (flags.test(6) && (flags.test(4) || flags.test(5)))) {
#ifdef __EMSCRIPTEN__
        flags.set(1, call_js_get_random() > 0.5F);
        int value = call_js_get_random() * 4.99F;
        flags.set(4, (value & 1) != 0);
        flags.set(5, (value & 2) != 0);
        flags.set(6, (value & 4) != 0);
#else
        flags.set(1, GetRandomValue(0, 1) == 0);
        int value = GetRandomValue(0, 4);
        flags.set(4, (value & 1) != 0);
        flags.set(5, (value & 2) != 0);
        flags.set(6, (value & 4) != 0);
#endif
      }
    }

    float value =
        (std::cos(PI_F * (1.0F - overview_timer / OVERVIEW_TIMER_MAX)) + 1.0F) /
        2.0F;
    if (!flags.test(4) && !flags.test(5) && !flags.test(6)) {
      Helpers::overview_pan_lr(&camera.position, value, flags.test(1),
                               camera.target.x);
    } else if (flags.test(4) && !flags.test(5) && !flags.test(6)) {
      Helpers::overview_zoom_out_l(&camera.position, value, flags.test(1),
                                   camera.target.x);
    } else if (!flags.test(4) && flags.test(5) && !flags.test(6)) {
      Helpers::overview_zoom_out_r(&camera.position, value, flags.test(1),
                                   camera.target.x);
    } else if (flags.test(4) && flags.test(5) && !flags.test(6)) {
      Helpers::overview_zoom_out_c(&camera.position, value, flags.test(1),
                                   camera.target.x);
    } else if (!flags.test(4) && !flags.test(5) && flags.test(6)) {
      Helpers::overview_orbit(&camera.position, value, flags.test(1),
                              camera.target.x);
    }
  }

  UpdateCamera(&camera);

  if (flags.test(7)) {
    qms.at(0).set_pos(RV3ToA3F(p1_pos));
    qms.at(1).set_pos(RV3ToA3F(p2_pos));
    flags.reset(7);
  }
  for (auto &obj : qms) {
    obj.update(dt);
  }

  if (IsMouseButtonPressed(0)) {
    if (GetTouchX() >= (triple_single_width - actual_width) / 2.0F &&
        GetTouchX() <=
            triple_single_width - (triple_single_width - actual_width) / 2.0F &&
        GetTouchY() >= GetScreenHeight() - triple_single_width +
                           (triple_single_width - actual_width) / 2.0F &&
        GetTouchY() <=
            GetScreenHeight() - (triple_single_width - actual_width) / 2.0F) {
      if (choices.at(0) == '?') {
        choices.at(0) = 'r';
      } else if (choices.at(1) == '?') {
        choices.at(1) = 'r';
      } else {
        choices.at(2) = 'r';
      }
    } else if (GetTouchX() >= triple_single_width +
                                  (triple_single_width - actual_width) / 2.0F &&
               GetTouchX() <= triple_single_width * 2.0F -
                                  (triple_single_width - actual_width) / 2.0F &&
               GetTouchY() >= GetScreenHeight() - triple_single_width +
                                  (triple_single_width - actual_width) / 2.0F &&
               GetTouchY() <= GetScreenHeight() -
                                  (triple_single_width - actual_width) / 2.0F) {
      if (choices.at(0) == '?') {
        choices.at(0) = 'p';
      } else if (choices.at(1) == '?') {
        choices.at(1) = 'p';
      } else {
        choices.at(2) = 'p';
      }
    } else if (GetTouchX() >= GetScreenWidth() - triple_single_width +
                                  (triple_single_width - actual_width) / 2.0F &&
               GetTouchX() <= GetScreenWidth() -
                                  (triple_single_width - actual_width) / 2.0F &&
               GetTouchY() >= GetScreenHeight() - triple_single_width +
                                  (triple_single_width - actual_width) / 2.0F &&
               GetTouchY() <= GetScreenHeight() -
                                  (triple_single_width - actual_width) / 2.0F) {
      if (choices.at(0) == '?') {
        choices.at(0) = 's';
      } else if (choices.at(1) == '?') {
        choices.at(1) = 's';
      } else {
        choices.at(2) = 's';
      }
    } else if (GetTouchX() >= (triple_single_width - actual_width2) / 2.0F &&
               GetTouchX() <=
                   triple_single_width -
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchY() >=
                   GetScreenHeight() - triple_single_width * 2.0F +
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchY() <=
                   GetScreenHeight() - triple_single_width -
                       (triple_single_width - actual_width2) / 2.0F) {
      choices.at(0) = '?';
    } else if (GetTouchX() >=
                   triple_single_width +
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchX() <=
                   triple_single_width * 2.0F -
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchY() >=
                   GetScreenHeight() - triple_single_width * 2.0F +
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchY() <=
                   GetScreenHeight() - triple_single_width -
                       (triple_single_width - actual_width2) / 2.0F) {
      choices.at(1) = '?';
    } else if (GetTouchX() >=
                   GetScreenWidth() - triple_single_width +
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchX() <=
                   GetScreenWidth() -
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchY() >=
                   GetScreenHeight() - triple_single_width * 2.0F +
                       (triple_single_width - actual_width2) / 2.0F &&
               GetTouchY() <=
                   GetScreenHeight() - triple_single_width -
                       (triple_single_width - actual_width2) / 2.0F) {
      choices.at(2) = '?';
    }
  }

  button_color_timer -= dt;
  if (button_color_timer <= 0.0F) {
    button_color_timer += BUTTON_COLOR_TIME;
  }
}

void Renderer3D::draw_impl() {
  BeginDrawing();
  ClearBackground(BLACK);
  BeginMode3D(camera);
  DrawModel(skybox_model, root_pos, 1.0F, WHITE);
  DrawModel(platform_model, root_pos, 1.0F, WHITE);
  for (auto &obj : qms) {
    obj.draw();
  }
  EndMode3D();

  if (!flags.test(3)) {
    const float triple_single_width = GetScreenWidth() / 3.0F;
    float actual_width = triple_single_width;
    if (actual_width > (float)ICON_MAX_WIDTH) {
      actual_width = ICON_MAX_WIDTH;
    }
    float actual_width2 = triple_single_width;
    if (actual_width2 > (float)ICON_MAX_WIDTH_2) {
      actual_width2 = ICON_MAX_WIDTH_2;
    }

    unsigned char color_value;
    const float button_color_value =
        button_color_timer * 2.0F / BUTTON_COLOR_TIME;
    if (button_color_value > 1.0F) {
      color_value = (1.0F - (button_color_value - 1.0F)) * BUTTON_COLOR_MIN +
                    (button_color_value - 1.0F) * BUTTON_COLOR_MAX;
    } else {
      color_value = button_color_value * BUTTON_COLOR_MIN +
                    (1.0F - button_color_value) * BUTTON_COLOR_MAX;
    }
    if (flags.test(2)) {
      if (choices.at(0) != '?' && choices.at(1) != '?' &&
          choices.at(2) != '?') {
        DrawRectangle(0, 0, GetScreenWidth(), triple_single_width,
                      {255, color_value, color_value, 255});
      }
      DrawRectangle(0, GetScreenHeight() - triple_single_width * 2.0F,
                    GetScreenWidth(), triple_single_width, {255, 80, 80, 255});
      DrawRectangle(0, GetScreenHeight() - triple_single_width,
                    GetScreenWidth(), triple_single_width,
                    {255, color_value, color_value, 255});
    } else {
      if (choices.at(0) != '?' && choices.at(1) != '?' &&
          choices.at(2) != '?') {
        DrawRectangle(0, 0, GetScreenWidth(), triple_single_width,
                      {color_value, color_value, 255, 255});
      }
      DrawRectangle(0, GetScreenHeight() - triple_single_width * 2.0F,
                    GetScreenWidth(), triple_single_width, {80, 80, 255, 255});
      DrawRectangle(0, GetScreenHeight() - triple_single_width,
                    GetScreenWidth(), triple_single_width,
                    {color_value, color_value, 255, 255});
    }
    if (choices.at(0) != '?' && choices.at(1) != '?' && choices.at(2) != '?') {
      DrawTexturePro(
          spriteSheet,
          {READY_DIMS[0], READY_DIMS[1], READY_DIMS[2], READY_DIMS[3]},
          {0, 0, GetScreenWidth() * 4.0F / 5.0F, triple_single_width},
          {0.0F, 0.0F}, 0.0F, WHITE);
      DrawTexturePro(spriteSheet,
                     {QUESTIONMARK_DIMS[0], QUESTIONMARK_DIMS[1],
                      QUESTIONMARK_DIMS[2], QUESTIONMARK_DIMS[3]},
                     {GetScreenWidth() * 4.0F / 5.0F, 0,
                      GetScreenWidth() / 5.0F, triple_single_width},
                     {0.0F, 0.0F}, 0.0F, WHITE);
    }

    DrawRectangleLines((triple_single_width - actual_width) / 2.0F,
                       GetScreenHeight() - triple_single_width +
                           (triple_single_width - actual_width) / 2.0F,
                       actual_width, actual_width, BLACK);
    DrawRectangleLines(
        triple_single_width + (triple_single_width - actual_width) / 2.0F,
        GetScreenHeight() - triple_single_width +
            (triple_single_width - actual_width) / 2.0F,
        actual_width, actual_width, BLACK);
    DrawRectangleLines(GetScreenWidth() - triple_single_width +
                           (triple_single_width - actual_width) / 2.0F,
                       GetScreenHeight() - triple_single_width +
                           (triple_single_width - actual_width) / 2.0F,
                       actual_width, actual_width, BLACK);

    DrawRectangleLines((triple_single_width - actual_width2) / 2.0F,
                       GetScreenHeight() - triple_single_width * 2.0F +
                           (triple_single_width - actual_width2) / 2.0F,
                       actual_width2, actual_width2, BLACK);
    DrawRectangleLines(
        triple_single_width + (triple_single_width - actual_width2) / 2.0F,
        GetScreenHeight() - triple_single_width * 2.0F +
            (triple_single_width - actual_width2) / 2.0F,
        actual_width2, actual_width2, BLACK);
    DrawRectangleLines(GetScreenWidth() - triple_single_width +
                           (triple_single_width - actual_width2) / 2.0F,
                       GetScreenHeight() - triple_single_width * 2.0F +
                           (triple_single_width - actual_width2) / 2.0F,
                       actual_width2, actual_width2, BLACK);

    DrawTexturePro(spriteSheet,
                   {ROCK_DIMS[0], ROCK_DIMS[1], ROCK_DIMS[2], ROCK_DIMS[3]},
                   {(triple_single_width - actual_width) / 2.0F,
                    GetScreenHeight() - triple_single_width +
                        (triple_single_width - actual_width) / 2.0F,
                    actual_width, actual_width},
                   {0.0F, 0.0F}, 0.0F, WHITE);
    DrawTexturePro(
        spriteSheet,
        {PAPER_DIMS[0], PAPER_DIMS[1], PAPER_DIMS[2], PAPER_DIMS[3]},
        {triple_single_width + (triple_single_width - actual_width) / 2.0F,
         GetScreenHeight() - triple_single_width +
             (triple_single_width - actual_width) / 2.0F,
         actual_width, actual_width},
        {0.0F, 0.0F}, 0.0F, WHITE);
    DrawTexturePro(spriteSheet,
                   {SCISSORS_DIMS[0], SCISSORS_DIMS[1], SCISSORS_DIMS[2],
                    SCISSORS_DIMS[3]},
                   {GetScreenWidth() - triple_single_width +
                        (triple_single_width - actual_width) / 2.0F,
                    GetScreenHeight() - triple_single_width +
                        (triple_single_width - actual_width) / 2.0F,
                    actual_width, actual_width},
                   {0.0F, 0.0F}, 0.0F, WHITE);

    for (unsigned int i = 0; i < choices.size(); ++i) {
      switch (choices[i]) {
        case 'r':
          DrawTexturePro(
              spriteSheet,
              {ROCK_DIMS[0], ROCK_DIMS[1], ROCK_DIMS[2], ROCK_DIMS[3]},
              {triple_single_width * (float)i +
                   (triple_single_width - actual_width2) / 2.0F,
               GetScreenHeight() - triple_single_width * 2.0F +
                   (triple_single_width - actual_width2) / 2.0F,
               actual_width2, actual_width2},
              {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case 'p':
          DrawTexturePro(
              spriteSheet,
              {PAPER_DIMS[0], PAPER_DIMS[1], PAPER_DIMS[2], PAPER_DIMS[3]},
              {triple_single_width * (float)i +
                   (triple_single_width - actual_width2) / 2.0F,
               GetScreenHeight() - triple_single_width * 2.0F +
                   (triple_single_width - actual_width2) / 2.0F,
               actual_width2, actual_width2},
              {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case 's':
          DrawTexturePro(spriteSheet,
                         {SCISSORS_DIMS[0], SCISSORS_DIMS[1], SCISSORS_DIMS[2],
                          SCISSORS_DIMS[3]},
                         {triple_single_width * (float)i +
                              (triple_single_width - actual_width2) / 2.0F,
                          GetScreenHeight() - triple_single_width * 2.0F +
                              (triple_single_width - actual_width2) / 2.0F,
                          actual_width2, actual_width2},
                         {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case '?':
        default:
          break;
      }
    }
  } else {
    DrawText("Spectating...", 0, 0, 20, RAYWHITE);
  }

  EndDrawing();
}
