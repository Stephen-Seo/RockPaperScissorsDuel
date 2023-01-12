#include "3d_renderer.h"

#include <raylib.h>

Renderer3D::Renderer3D() {
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
                              bool gameover) {}

void Renderer3D::do_update() {
  update_impl();
  draw_impl();
}

void Renderer3D::screen_size_changed() {}

void Renderer3D::update_impl() { UpdateCamera(&camera); }

void Renderer3D::draw_impl() {
  BeginDrawing();
  BeginMode3D(camera);
  DrawModel(skybox_model, root_pos, 1.0F, WHITE);
  DrawModel(platform_model, root_pos, 1.0F, WHITE);
  DrawModel(qm_model, {0.0F, 1.0F, 0.0F}, 1.0F, WHITE);
  EndMode3D();
  EndDrawing();
}
