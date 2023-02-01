#include "3d_renderer.h"

// standard library includes
#include <cmath>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

// third party includes
#include <raylib.h>

// local includes
#include "3d/anim_concurrent.h"
#include "3d/anim_falling_2d.h"
#include "3d/anim_model_attack.h"
#include "3d/anim_model_grow.h"
#include "3d/anim_model_shrink.h"
#include "3d/anim_model_still.h"
#include "3d/arrays_conv.h"
#include "constants.h"
#include "ems.h"
#include "helpers.h"

Renderer3D::Renderer3D()
    : qms{},
      anims(nullptr),
      root_pos{0.0F, 0.0F, 0.0F},
      overview_timer(OVERVIEW_TIMER_MAX),
      button_color_timer(BUTTON_COLOR_TIME),
      screen_shake_factor(SCREEN_SHAKE_DEFAULT_FACTOR),
      screen_shake_timer(0.0F),
      received_pos(0),
      prev_pos(0),
      choices{'?', '?', '?'},
      opponent_choices{'?', '?', '?'} {
  qms.at(0).set_pos_x(-1.0F);
  qms.at(1).set_pos_x(1.0F);

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
  flags.set(19);

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
  if (renderTexture.has_value()) {
    UnloadRenderTexture(renderTexture.value());
  }

  UnloadTexture(spriteSheet);

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
                              bool second_ready, bool first_matchup_done,
                              bool second_matchup_done, int pos, int prev_pos,
                              bool gameover_called, bool matchup_started) {
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

  flags.set(9, first_ready);
  flags.set(10, second_ready);
  flags.set(13, matchup_started);
  flags.set(14, gameover_called);

  flags.set(12);

  // if (flags.test(3)) {
  //   std::cout << "got pos: " << pos << std::endl;
  //   std::cout << "camera.target.x: " << camera.target.x << std::endl;
  //   std::cout << "matchup started: " << (matchup_started ? "true" : "false")
  //             << std::endl;
  //   std::cout << "p1 is " << (first_ready ? "ready" : "NOT ready") << "\np2
  //   is "
  //             << (second_ready ? "ready" : "NOT ready") << std::endl;
  // }

  this->prev_pos = prev_pos;
  if (!flags.test(13) && anims.is_done()) {
    received_pos = pos;
  } else if (flags.test(3) && anims.is_done()) {
    received_pos = prev_pos;
  }

  if (second_first != '?') {
    if (flags.test(2)) {
      opponent_choices.at(0) = second_first;
      opponent_choices.at(1) = second_second;
      opponent_choices.at(2) = second_third;
    } else {
      opponent_choices.at(0) = first_first;
      opponent_choices.at(1) = first_second;
      opponent_choices.at(2) = first_third;
    }
  }

  if (flags.test(3)) {
    choices.at(0) = first_first;
    choices.at(1) = first_second;
    choices.at(2) = first_third;
    opponent_choices.at(0) = second_first;
    opponent_choices.at(1) = second_second;
    opponent_choices.at(2) = second_third;

    if (!matchup_started) {
      flags.reset(16);
      flags.reset(17);
    }
  }

  if (flags.test(11) && first_first == '?' && second_first == '?' &&
      flags.test(15) && !flags.test(13)) {
    reset_for_next();
  }

  if (flags.test(19)) {
    flags.reset(19);
    if (renderTexture.has_value()) {
      UnloadRenderTexture(renderTexture.value());
    }
    renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
  }

  // if (flags.test(3)) {
  //   std::cout << flags.to_string().substr(64 - 16) << std::endl;
  // }
}

void Renderer3D::do_update() {
  update_impl();
  draw_impl();
}

void Renderer3D::screen_size_changed() { flags.set(19); }

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
  const float height = actual_width;
  const float height2 = actual_width2;

  if (flags.test(0)) {
    camera.position = camera.target;
    camera.position.z += 10.0F;
    camera.position.y += 4.0F;
  } else {
    overview_timer -= dt;
    if (overview_timer <= 0.0F) {
      overview_timer += OVERVIEW_TIMER_MAX;
      set_random_overview();
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

  for (auto &obj : qms) {
    obj.update(dt);
  }

  if (IsMouseButtonPressed(0)) {
    if (!flags.test(8)) {
      if (GetTouchX() >= (triple_single_width - actual_width) / 2.0F &&
          GetTouchX() <= triple_single_width -
                             (triple_single_width - actual_width) / 2.0F &&
          GetTouchY() >= GetScreenHeight() - height &&
          GetTouchY() <= GetScreenHeight()) {
        if (choices.at(0) == '?') {
          choices.at(0) = 'r';
        } else if (choices.at(1) == '?') {
          choices.at(1) = 'r';
        } else {
          choices.at(2) = 'r';
        }
      } else if (GetTouchX() >=
                     triple_single_width +
                         (triple_single_width - actual_width) / 2.0F &&
                 GetTouchX() <=
                     triple_single_width * 2.0F -
                         (triple_single_width - actual_width) / 2.0F &&
                 GetTouchY() >= GetScreenHeight() - height &&
                 GetTouchY() <= GetScreenHeight()) {
        if (choices.at(0) == '?') {
          choices.at(0) = 'p';
        } else if (choices.at(1) == '?') {
          choices.at(1) = 'p';
        } else {
          choices.at(2) = 'p';
        }
      } else if (GetTouchX() >=
                     GetScreenWidth() - triple_single_width +
                         (triple_single_width - actual_width) / 2.0F &&
                 GetTouchX() <=
                     GetScreenWidth() -
                         (triple_single_width - actual_width) / 2.0F &&
                 GetTouchY() >= GetScreenHeight() - height &&
                 GetTouchY() <= GetScreenHeight()) {
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
                 GetTouchY() >= GetScreenHeight() - height - height2 &&
                 GetTouchY() <= GetScreenHeight() - height) {
        choices.at(0) = '?';
      } else if (GetTouchX() >=
                     triple_single_width +
                         (triple_single_width - actual_width2) / 2.0F &&
                 GetTouchX() <=
                     triple_single_width * 2.0F -
                         (triple_single_width - actual_width2) / 2.0F &&
                 GetTouchY() >= GetScreenHeight() - height - height2 &&
                 GetTouchY() <= GetScreenHeight() - height) {
        choices.at(1) = '?';
      } else if (GetTouchX() >=
                     GetScreenWidth() - triple_single_width +
                         (triple_single_width - actual_width2) / 2.0F &&
                 GetTouchX() <=
                     GetScreenWidth() -
                         (triple_single_width - actual_width2) / 2.0F &&
                 GetTouchY() >= GetScreenHeight() - height - height2 &&
                 GetTouchY() <= GetScreenHeight() - height) {
        choices.at(2) = '?';
      } else if (choices.at(0) != '?' && choices.at(1) != '?' &&
                 choices.at(2) != '?' && GetTouchX() >= 0 &&
                 GetTouchX() <= GetScreenWidth() && GetTouchY() >= 0 &&
                 GetTouchY() <= triple_single_width) {
        flags.set(8);
        if (!flags.test(14)) {
          call_js_set_ready();
        }
      }
    }
  }

  button_color_timer -= dt;
  if (button_color_timer <= 0.0F) {
    button_color_timer += BUTTON_COLOR_TIME;
  }

  if (flags.test(8) && flags.test(9) && flags.test(10) && !flags.test(11)) {
    char buf[6] = {(char)choices.at(0), 0, (char)choices.at(1), 0,
                   (char)choices.at(2), 0};
    flags.set(11);
    flags.set(0);
    if (!flags.test(14)) {
      call_js_set_choices(&buf[0], &buf[2], &buf[4]);
    }
  }

  if (flags.test(12)) {
    if ((flags.test(11) || (flags.test(3) && !flags.test(16))) &&
        !flags.test(7) && flags.test(13) && anims.is_done()) {
      flags.set(7);
      flags.set(15);

      int result = received_pos;
      for (unsigned int i = 0; i < 3; ++i) {
        result = setup_anims(i, result);
        if (result < -3 || result > 3) {
          break;
        }
      }

      if (flags.test(3)) {
        flags.set(16);
      }
    }
  }

  flags.reset(12);

  if (flags.test(8) && flags.test(11) && flags.test(7) && anims.is_done() &&
      !flags.test(14)) {
    call_js_set_matchup_done();
  }

  {
    float offset = received_pos * 2.0F - camera.target.x;
    camera.target.x += offset / 4.0F;
  }

  anims.do_update(dt);

  if (flags.test(3)) {
    if (flags.test(0)) {
      if (anims.is_done() && !flags.test(17)) {
        reset_for_next();
        received_pos = prev_pos;
        flags.set(17);
      }
    } else if (flags.test(13) && flags.test(16)) {
      flags.set(0);
    }
  }

  qms.at(0).set_pos_x(received_pos * 2.0F - 1.0F);
  qms.at(1).set_pos_x(received_pos * 2.0F + 1.0F);

  std::vector<int> to_delete;
  for (auto &iter : deferred_2d_draw_map) {
    if (iter.second.is_activated()) {
      iter.second.update(dt);
      if (iter.second.is_oob()) {
        to_delete.push_back(iter.first);
      }
    }
  }

  for (int id : to_delete) {
    deferred_2d_draw_map.erase(id);
  }

  if (!flags.test(18)) {
    load_sounds();
  }

  if (flags.test(21)) {
    screen_shake_timer -= dt;
    if (screen_shake_timer <= 0.0F) {
      flags.reset(20);
      flags.reset(21);
    }
  }
}

void Renderer3D::draw_impl() {
  if (flags.test(20) && renderTexture.has_value()) {
    BeginTextureMode(renderTexture.value());
  } else {
    BeginDrawing();
  }
  ClearBackground(BLACK);
  BeginMode3D(camera);
  DrawModel(skybox_model, root_pos, 1.0F, WHITE);
  DrawModel(platform_model, root_pos, 1.0F, WHITE);
  if (flags.test(0)) {
    anims.do_draw();
  }
  if (anims.is_done()) {
    for (auto &obj : qms) {
      obj.draw();
    }
  }
  EndMode3D();

  if (!flags.test(3) && !flags.test(8)) {
    const float triple_single_width = GetScreenWidth() / 3.0F;
    float actual_width = triple_single_width;
    if (actual_width > (float)ICON_MAX_WIDTH) {
      actual_width = ICON_MAX_WIDTH;
    }
    float actual_width2 = triple_single_width;
    if (actual_width2 > (float)ICON_MAX_WIDTH_2) {
      actual_width2 = ICON_MAX_WIDTH_2;
    }
    const float height = actual_width;
    const float height2 = actual_width2;

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
      DrawRectangle(0, GetScreenHeight() - height - height2, GetScreenWidth(),
                    height + height2, {255, 80, 80, 255});
      DrawRectangle(0, GetScreenHeight() - height, GetScreenWidth(), height,
                    {255, color_value, color_value, 255});
    } else {
      if (choices.at(0) != '?' && choices.at(1) != '?' &&
          choices.at(2) != '?') {
        DrawRectangle(0, 0, GetScreenWidth(), triple_single_width,
                      {color_value, color_value, 255, 255});
      }
      DrawRectangle(0, GetScreenHeight() - height - height2, GetScreenWidth(),
                    height + height2, {80, 80, 255, 255});
      DrawRectangle(0, GetScreenHeight() - height, GetScreenWidth(), height,
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
                       GetScreenHeight() - height, actual_width, height, BLACK);
    DrawRectangleLines(
        triple_single_width + (triple_single_width - actual_width) / 2.0F,
        GetScreenHeight() - height, actual_width, height, BLACK);
    DrawRectangleLines(GetScreenWidth() - triple_single_width +
                           (triple_single_width - actual_width) / 2.0F,
                       GetScreenHeight() - height, actual_width, height, BLACK);

    DrawRectangleLines((triple_single_width - actual_width2) / 2.0F,
                       GetScreenHeight() - height - height2, actual_width2,
                       height2, BLACK);
    DrawRectangleLines(
        triple_single_width + (triple_single_width - actual_width2) / 2.0F,
        GetScreenHeight() - height - height2, actual_width2, height2, BLACK);
    DrawRectangleLines(GetScreenWidth() - triple_single_width +
                           (triple_single_width - actual_width2) / 2.0F,
                       GetScreenHeight() - height - height2, actual_width2,
                       height2, BLACK);

    DrawTexturePro(spriteSheet,
                   {ROCK_DIMS[0], ROCK_DIMS[1], ROCK_DIMS[2], ROCK_DIMS[3]},
                   {(triple_single_width - actual_width) / 2.0F,
                    GetScreenHeight() - height, actual_width, height},
                   {0.0F, 0.0F}, 0.0F, WHITE);
    DrawTexturePro(
        spriteSheet,
        {PAPER_DIMS[0], PAPER_DIMS[1], PAPER_DIMS[2], PAPER_DIMS[3]},
        {triple_single_width + (triple_single_width - actual_width) / 2.0F,
         GetScreenHeight() - height, actual_width, height},
        {0.0F, 0.0F}, 0.0F, WHITE);
    DrawTexturePro(spriteSheet,
                   {SCISSORS_DIMS[0], SCISSORS_DIMS[1], SCISSORS_DIMS[2],
                    SCISSORS_DIMS[3]},
                   {GetScreenWidth() - triple_single_width +
                        (triple_single_width - actual_width) / 2.0F,
                    GetScreenHeight() - height, actual_width, height},
                   {0.0F, 0.0F}, 0.0F, WHITE);

    for (unsigned int i = 0; i < choices.size(); ++i) {
      switch (choices[i]) {
        case 'r':
          DrawTexturePro(
              spriteSheet,
              {ROCK_DIMS[0], ROCK_DIMS[1], ROCK_DIMS[2], ROCK_DIMS[3]},
              {triple_single_width * (float)i +
                   (triple_single_width - actual_width2) / 2.0F,
               GetScreenHeight() - height - height2, actual_width2, height2},
              {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case 'p':
          DrawTexturePro(
              spriteSheet,
              {PAPER_DIMS[0], PAPER_DIMS[1], PAPER_DIMS[2], PAPER_DIMS[3]},
              {triple_single_width * (float)i +
                   (triple_single_width - actual_width2) / 2.0F,
               GetScreenHeight() - height - height2, actual_width2, height2},
              {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case 's':
          DrawTexturePro(
              spriteSheet,
              {SCISSORS_DIMS[0], SCISSORS_DIMS[1], SCISSORS_DIMS[2],
               SCISSORS_DIMS[3]},
              {triple_single_width * (float)i +
                   (triple_single_width - actual_width2) / 2.0F,
               GetScreenHeight() - height - height2, actual_width2, height2},
              {0.0F, 0.0F}, 0.0F, WHITE);
          break;
        case '?':
        default:
          break;
      }
    }
  } else {
    DrawText("Waiting...", 0, 0, 20, RAYWHITE);
  }

  for (auto &iter : deferred_2d_draw_map) {
    if (iter.second.is_activated()) {
      iter.second.draw();
    }
  }

  if (flags.test(20) && renderTexture.has_value()) {
    EndTextureMode();

    float offset_x = 0;
    float offset_y = 0;

    if (flags.test(21)) {
      offset_x = screen_shake_factor * 2.0F * call_js_get_random() -
                 screen_shake_factor;
      offset_y = screen_shake_factor * 2.0F * call_js_get_random() -
                 screen_shake_factor;
    }

    BeginDrawing();
    DrawTextureRec(renderTexture.value().texture,
                   Rectangle{offset_x, offset_y,
                             (float)renderTexture.value().texture.width,
                             (float)-renderTexture.value().texture.height},
                   Vector2{0, 0}, WHITE);
    EndDrawing();
  } else {
    EndDrawing();
  }
}

void Renderer3D::set_random_overview() {
  const decltype(flags) prevFlags = flags;
  const auto is_same = [](const decltype(flags) &l, const decltype(flags) &r) {
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

int Renderer3D::setup_anims(int idx, int score) {
  anims.reset_is_done();

  auto newAnim = std::make_unique<AnimConcurrent>(nullptr);
  newAnim->push_anim(std::make_unique<AnimModelShrink>(
      &qm_model, A3F{score * 2.0F - 1.0F, 0.0F, 0.0F}, A4C{255, 0, 0, 255}));
  newAnim->push_anim(std::make_unique<AnimModelShrink>(
      &qm_model, A3F{score * 2.0F + 1.0F, 0.0F, 0.0F}, A4C{0, 0, 255, 255}));
  anims.push_anim(std::move(newAnim));

  newAnim = std::make_unique<AnimConcurrent>(nullptr);
  Model *p1_model = &qm_model;
  Model *p2_model = &qm_model;
  switch (choices.at(idx)) {
    case 'r':
      if (flags.test(2) || flags.test(3)) {
        p1_model = &rock_model;
      } else {
        p2_model = &rock_model;
      }
      break;
    case 'p':
      if (flags.test(2) || flags.test(3)) {
        p1_model = &paper_model;
      } else {
        p2_model = &paper_model;
      }
      break;
    case 's':
      if (flags.test(2) || flags.test(3)) {
        p1_model = &scissors_model;
      } else {
        p2_model = &scissors_model;
      }
      break;
  }
  switch (opponent_choices.at(idx)) {
    case 'r':
      if (flags.test(2) || flags.test(3)) {
        p2_model = &rock_model;
      } else {
        p1_model = &rock_model;
      }
      break;
    case 'p':
      if (flags.test(2) || flags.test(3)) {
        p2_model = &paper_model;
      } else {
        p1_model = &paper_model;
      }
      break;
    case 's':
      if (flags.test(2) || flags.test(3)) {
        p2_model = &scissors_model;
      } else {
        p1_model = &scissors_model;
      }
      break;
  }
  newAnim->push_anim(std::make_unique<AnimModelGrow>(
      p1_model, A3F{score * 2.0F - 1.0F, 0.0F, 0.0F}, A4C{255, 200, 200, 255}));
  newAnim->push_anim(std::make_unique<AnimModelGrow>(
      p2_model, A3F{score * 2.0F + 1.0F, 0.0F, 0.0F}, A4C{200, 200, 255, 255}));
  anims.push_anim(std::move(newAnim));

  newAnim = std::make_unique<AnimConcurrent>(nullptr);

  const int result = Helpers::a_vs_b(
      (flags.test(2) || flags.test(3)) ? choices.at(idx)
                                       : opponent_choices.at(idx),
      (flags.test(2) || flags.test(3)) ? opponent_choices.at(idx)
                                       : choices.at(idx));

  auto seqAnim = std::make_unique<AnimSequence>(nullptr);

  A4F p1_dims = (flags.test(2) || flags.test(3))
                    ? Helpers::get_sprite_dims(choices.at(idx))
                    : Helpers::get_sprite_dims(opponent_choices.at(idx));
  A4F p2_dims = (flags.test(2) || flags.test(3))
                    ? Helpers::get_sprite_dims(opponent_choices.at(idx))
                    : Helpers::get_sprite_dims(choices.at(idx));
  Vector3 oldPos = camera.position;
  camera.position = camera.target;
  camera.position.z += 10.0F;
  camera.position.y += 4.0F;
  Vector2 p1_pos =
      GetWorldToScreen({camera.target.x - 1.0F, 0.35F, 0.0F}, camera);
  Vector2 p2_pos =
      GetWorldToScreen({camera.target.x + 1.0F, 0.35F, 0.0F}, camera);
  camera.position = oldPos;

  // if (flags.test(2)) {
  //   std::cout << "p1_pos x is " << (score * 2.0F - 1.0F) << " or " <<
  //   p1_pos.x
  //             << std::endl;
  // }

  using CDataT = std::tuple<Sound *, decltype(flags) *, float *>;
  switch (result) {
    case -1: {
      auto anim_still = std::make_unique<AnimModelStill>(
          p1_model, A3F{score * 2.0F - 1.0F, 0.0F, 0.0F},
          A4C{255, 200, 200, 255}, MODEL_ATTACK_TIME_0 + MODEL_ATTACK_TIME_1);
      CDataT *ptr = new CDataT{(flags.test(2) || flags.test(3))
                                   ? type_to_sfx(opponent_choices.at(idx))
                                   : type_to_sfx(choices.at(idx)),
                               &flags, &screen_shake_timer};
      anim_still->set_end_callback(
          [](void *ud) {
            auto *ptr = (CDataT *)ud;
            if (std::get<0>(*ptr) != nullptr) {
              PlaySound(*std::get<0>(*ptr));
            }
            std::get<1>(*ptr)->set(20);
            std::get<1>(*ptr)->set(21);
            *std::get<2>(*ptr) = SCREEN_SHAKE_TIME;
            delete ptr;
          },
          ptr);
      seqAnim->push_anim(std::move(anim_still));
      seqAnim->push_anim(std::make_unique<AnimFalling2D>(
          A3F{p1_pos.x, p1_pos.y, 0.0F}, A4C{255, 200, 200, 255}, &spriteSheet,
          p1_dims, false, &deferred_2d_draw_map));
      newAnim->push_anim(std::make_unique<AnimModelAttack>(
          p2_model, A3F{score * 2.0F + 1.0F, 0.0F, 0.0F},
          A4C{200, 200, 255, 255}, false));
    } break;
    case 1: {
      newAnim->push_anim(std::make_unique<AnimModelAttack>(
          p1_model, A3F{score * 2.0F - 1.0F, 0.0F, 0.0F},
          A4C{255, 200, 200, 255}, true));
      auto anim_still = std::make_unique<AnimModelStill>(
          p2_model, A3F{score * 2.0F + 1.0F, 0.0F, 0.0F},
          A4C{200, 200, 255, 255}, MODEL_ATTACK_TIME_0 + MODEL_ATTACK_TIME_1);
      CDataT *ptr = new CDataT{(flags.test(2) || flags.test(3))
                                   ? type_to_sfx(choices.at(idx))
                                   : type_to_sfx(opponent_choices.at(idx)),
                               &flags, &screen_shake_timer};
      anim_still->set_end_callback(
          [](void *ud) {
            auto *ptr = (CDataT *)ud;
            if (std::get<0>(*ptr) != nullptr) {
              PlaySound(*std::get<0>(*ptr));
            }
            std::get<1>(*ptr)->set(20);
            std::get<1>(*ptr)->set(21);
            *std::get<2>(*ptr) = SCREEN_SHAKE_TIME;
            delete ptr;
          },
          ptr);
      seqAnim->push_anim(std::move(anim_still));
      seqAnim->push_anim(std::make_unique<AnimFalling2D>(
          A3F{p2_pos.x, p2_pos.y, 0.0F}, A4C{200, 200, 255, 255}, &spriteSheet,
          p2_dims, true, &deferred_2d_draw_map));
    } break;
    case 0:
    default:
      break;
  }

  if (result != 0) {
    newAnim->push_anim(std::move(seqAnim));
    anims.push_anim(std::move(newAnim));
  } else {
    newAnim->set_end_callback(
        [](void *ud) {
          auto *sfx = (Sound *)ud;
          PlaySound(*sfx);
        },
        get_random_draw_sfx());
    anims.push_anim(std::move(newAnim));
  }

  newAnim = std::make_unique<AnimConcurrent>(nullptr);
  if (result > 0) {
    newAnim->push_anim(std::make_unique<AnimModelShrink>(
        p1_model, A3F{score * 2.0F - 1.0F, 0.0F, 0.0F},
        A4C{255, 200, 200, 255}));
  } else if (result < 0) {
    newAnim->push_anim(std::make_unique<AnimModelShrink>(
        p2_model, A3F{score * 2.0F + 1.0F, 0.0F, 0.0F},
        A4C{200, 200, 255, 255}));
  } else {
    newAnim->push_anim(std::make_unique<AnimFalling2D>(
        A3F{p1_pos.x, p1_pos.y, 0.0F}, A4C{255, 200, 200, 255}, &spriteSheet,
        p1_dims, false, &deferred_2d_draw_map));
    newAnim->push_anim(std::make_unique<AnimFalling2D>(
        A3F{p2_pos.x, p2_pos.y, 0.0F}, A4C{200, 200, 255, 255}, &spriteSheet,
        p2_dims, true, &deferred_2d_draw_map));
    newAnim->push_anim(std::make_unique<AnimModelStill>(
        nullptr, A3F{0.0F, 0.0F, 0.0F}, A4C{255, 255, 255, 255},
        MODEL_STILL_FALLING_WAIT_TIME));
  }

  using DataT = std::tuple<int *, int>;
  DataT *data = new DataT{&received_pos, result};
  newAnim->set_end_callback(
      [](void *ud) {
        auto *d = (DataT *)(ud);
        *std::get<0>(*d) += std::get<1>(*d);
        delete d;
      },
      data);

  anims.push_anim(std::move(newAnim));

  newAnim = std::make_unique<AnimConcurrent>(nullptr);
  newAnim->push_anim(std::make_unique<AnimModelGrow>(
      &qm_model, A3F{(result + score) * 2.0F - 1.0F, 0.0F, 0.0F},
      A4C{255, 0, 0, 255}));
  newAnim->push_anim(std::make_unique<AnimModelGrow>(
      &qm_model, A3F{(result + score) * 2.0F + 1.0F, 0.0F, 0.0F},
      A4C{0, 0, 255, 255}));

  anims.push_anim(std::move(newAnim));

  return score + result;
}

void Renderer3D::reset_for_next() {
  choices.at(0) = '?';
  choices.at(1) = '?';
  choices.at(2) = '?';
  opponent_choices.at(0) = '?';
  opponent_choices.at(1) = '?';
  opponent_choices.at(2) = '?';
  flags.reset(11);
  flags.reset(8);
  flags.reset(0);
  flags.reset(15);
  flags.reset(7);
  overview_timer = OVERVIEW_TIMER_MAX;
  set_random_overview();
  camera.target.x = received_pos * 2.0F;

  // if (flags.test(3)) {
  //   std::cerr << "RESET STATE for next round" << std::endl;
  // }
}

void Renderer3D::load_sounds() {
  InitAudioDevice();
  if (IsAudioDeviceReady()) {
    flags.set(18);
    paper_sfx.at(0) = LoadSound("resources/sfx_paper0.ogg");
    paper_sfx.at(1) = LoadSound("resources/sfx_paper1.ogg");
    paper_sfx.at(2) = LoadSound("resources/sfx_paper2.ogg");
    paper_sfx.at(3) = LoadSound("resources/sfx_paper3.ogg");
    paper_sfx.at(4) = LoadSound("resources/sfx_paper4.ogg");

    scissors_sfx.at(0) = LoadSound("resources/sfx_scissors0.ogg");
    scissors_sfx.at(1) = LoadSound("resources/sfx_scissors1.ogg");
    scissors_sfx.at(2) = LoadSound("resources/sfx_scissors2.ogg");
    scissors_sfx.at(3) = LoadSound("resources/sfx_scissors3.ogg");
    scissors_sfx.at(4) = LoadSound("resources/sfx_scissors4.ogg");

    rock_sfx.at(0) = LoadSound("resources/sfx_rock0.ogg");
    rock_sfx.at(1) = LoadSound("resources/sfx_rock1.ogg");
    rock_sfx.at(2) = LoadSound("resources/sfx_rock2.ogg");
    rock_sfx.at(3) = LoadSound("resources/sfx_rock3.ogg");

    draw_sfx.at(0) = LoadSound("resources/sfx_draw0.ogg");
    draw_sfx.at(1) = LoadSound("resources/sfx_draw1.ogg");
    draw_sfx.at(2) = LoadSound("resources/sfx_draw2.ogg");
  }
}

Sound *Renderer3D::get_random_rock_sfx() {
#ifdef __EMSCRIPTEN__
  return &rock_sfx.at(call_js_get_random() * rock_sfx.size());
#else
  return &rock_sfx.at(GetRandomValue(0, rock_sfx.size() - 1));
#endif
}

Sound *Renderer3D::get_random_paper_sfx() {
#ifdef __EMSCRIPTEN__
  return &paper_sfx.at(call_js_get_random() * paper_sfx.size());
#else
  return &paper_sfx.at(GetRandomValue(0, paper_sfx.size() - 1));
#endif
}

Sound *Renderer3D::get_random_scissors_sfx() {
#ifdef __EMSCRIPTEN__
  return &scissors_sfx.at(call_js_get_random() * scissors_sfx.size());
#else
  return &scissors_sfx.at(GetRandomValue(0, scissors_sfx.size() - 1));
#endif
}

Sound *Renderer3D::get_random_draw_sfx() {
#ifdef __EMSCRIPTEN__
  return &draw_sfx.at(call_js_get_random() * draw_sfx.size());
#else
  return &draw_sfx.at(GetRandomValue(0, draw_sfx.size() - 1));
#endif
}

Sound *Renderer3D::type_to_sfx(char type) {
  switch (type) {
    case 'r':
      return get_random_rock_sfx();
    case 'p':
      return get_random_paper_sfx();
    case 's':
      return get_random_scissors_sfx();
    default:
      break;
  }
  return nullptr;
}
