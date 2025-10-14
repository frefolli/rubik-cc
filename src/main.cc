#include <cstdint>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <string>

struct Block {
  Model model;
  Vector3 position;

  static Block Load(const std::string& filepath, Vector3 position) {
    Model model = LoadModel(filepath.c_str());
    model.transform = MatrixTranslate(position.x, position.y, position.z);
    return Block {.model = model, .position = position};
  }

  void reset() {
    model.transform = MatrixTranslate(position.x, position.y, position.z);
  }
};

struct Face {
  // affected blocks
  std::vector<uintmax_t> blocks;
  std::vector<uintmax_t> original_blocks;
  // center of movement
  uintmax_t center;
  // axis of rotation
  Vector3 axis;

  static Face Load(std::vector<uintmax_t> blocks, uintmax_t center, Vector3 axis) {
    return Face {
      .blocks = blocks,
      .original_blocks = blocks,
      .center = center,
      .axis = axis
    };
  }

  void reset() {
    blocks = original_blocks;
  }
};

struct Rubik {
  std::vector<Block> blocks;
  std::vector<Face> faces;

  struct Rotating {
    uintmax_t face_idx = -1;
    float angle = 0.0f;
    const float angle_delta = 3.0f;
    bool direction = 1.0f;
  } rotating;

  static Rubik Load() {
    std::vector<Block> blocks = {
      Block::Load("./assets/0.obj", {.x = -1.025f, .y =  1.025f, .z = -1.025f}),
      Block::Load("./assets/1.obj", {.x = -1.025f, .y =  1.025f, .z =    0.0f}),
      Block::Load("./assets/2.obj", {.x = -1.025f, .y =  1.025f, .z =  1.025f}),
      Block::Load("./assets/3.obj", {.x =    0.0f, .y =  1.025f, .z = -1.025f}),
      Block::Load("./assets/4.obj", {.x =    0.0f, .y =  1.025f, .z =    0.0f}),
      Block::Load("./assets/5.obj", {.x =    0.0f, .y =  1.025f, .z =  1.025f}),
      Block::Load("./assets/6.obj", {.x =  1.025f, .y =  1.025f, .z = -1.025f}),
      Block::Load("./assets/7.obj", {.x =  1.025f, .y =  1.025f, .z =    0.0f}),
      Block::Load("./assets/8.obj", {.x =  1.025f, .y =  1.025f, .z =  1.025f}),

      Block::Load("./assets/9.obj", {.x = -1.025f, .y =    0.0f, .z = -1.025f}),
      Block::Load("./assets/10.obj", {.x = -1.025f, .y =    0.0f, .z =    0.0f}),
      Block::Load("./assets/11.obj", {.x = -1.025f, .y =    0.0f, .z =  1.025f}),
      Block::Load("./assets/12.obj", {.x =    0.0f, .y =    0.0f, .z = -1.025f}),
      Block::Load("./assets/13.obj", {.x =    0.0f, .y =    0.0f, .z =    0.0f}),
      Block::Load("./assets/14.obj", {.x =    0.0f, .y =    0.0f, .z =  1.025f}),
      Block::Load("./assets/15.obj", {.x =  1.025f, .y =    0.0f, .z = -1.025f}),
      Block::Load("./assets/16.obj", {.x =  1.025f, .y =    0.0f, .z =    0.0f}),
      Block::Load("./assets/17.obj", {.x =  1.025f, .y =    0.0f, .z =  1.025f}),

      Block::Load("./assets/18.obj", {.x = -1.025f, .y = -1.025f, .z = -1.025f}),
      Block::Load("./assets/19.obj", {.x = -1.025f, .y = -1.025f, .z =    0.0f}),
      Block::Load("./assets/20.obj", {.x = -1.025f, .y = -1.025f, .z =  1.025f}),
      Block::Load("./assets/21.obj", {.x =    0.0f, .y = -1.025f, .z = -1.025f}),
      Block::Load("./assets/22.obj", {.x =    0.0f, .y = -1.025f, .z =    0.0f}),
      Block::Load("./assets/23.obj", {.x =    0.0f, .y = -1.025f, .z =  1.025f}),
      Block::Load("./assets/24.obj", {.x =  1.025f, .y = -1.025f, .z = -1.025f}),
      Block::Load("./assets/25.obj", {.x =  1.025f, .y = -1.025f, .z =    0.0f}),
      Block::Load("./assets/26.obj", {.x =  1.025f, .y = -1.025f, .z =  1.025f})
    };

    std::vector<Face> faces = {
      Face::Load({ 0,  1,  2,  5,  8,  7,  6,  3},  4, {.x = 0.0f, .y = 1.0f, .z = 0.0f}),
      Face::Load({ 9, 10, 11, 14, 17, 16, 15, 12}, 13, {.x = 0.0f, .y = 1.0f, .z = 0.0f}),
      Face::Load({18, 19, 20, 23, 26, 25, 24, 21}, 22, {.x = 0.0f, .y = 1.0f, .z = 0.0f}),
      Face::Load({ 8,  5,  2, 11, 20, 23, 26, 17}, 14, {.x = 0.0f, .y = 0.0f, .z = 1.0f}),
      Face::Load({ 7,  4,  1, 10, 19, 22, 25, 16}, 13, {.x = 0.0f, .y = 0.0f, .z = 1.0f}),
      Face::Load({ 6,  3,  0,  9, 18, 21, 24, 15}, 12, {.x = 0.0f, .y = 0.0f, .z = 1.0f}),
      Face::Load({24, 25, 26, 17,  8,  7,  6, 15}, 16, {.x = 1.0f, .y = 0.0f, .z = 0.0f}),
      Face::Load({21, 22, 23, 14,  5,  4,  3, 12}, 13, {.x = 1.0f, .y = 0.0f, .z = 0.0f}),
      Face::Load({18, 19, 20, 11,  2,  1,  0,  9}, 10, {.x = 1.0f, .y = 0.0f, .z = 0.0f}),
    };

    return Rubik {
      .blocks = blocks,
      .faces = faces,
      .rotating = Rotating {}
    };
  }

  void end_rotation() {
    switch (rotating.face_idx) {
      case 0: {
        if (rotating.direction) {
          faces[0].blocks = {faces[0].blocks[2], faces[0].blocks[3], faces[0].blocks[4], faces[0].blocks[5], faces[0].blocks[6], faces[0].blocks[7], faces[0].blocks[0], faces[0].blocks[1]};
        } else {
          faces[0].blocks = {faces[0].blocks[6], faces[0].blocks[7], faces[0].blocks[0], faces[0].blocks[1], faces[0].blocks[2], faces[0].blocks[3], faces[0].blocks[4], faces[0].blocks[5]};
        }
        faces[3].blocks[2] = faces[0].blocks[2];
        faces[3].blocks[1] = faces[0].blocks[3];
        faces[3].blocks[0] = faces[0].blocks[4];
        faces[4].blocks[2] = faces[0].blocks[1];
        faces[4].blocks[0] = faces[0].blocks[5];
        faces[5].blocks[2] = faces[0].blocks[0];
        faces[5].blocks[0] = faces[0].blocks[6];
        faces[5].blocks[1] = faces[0].blocks[7];
        faces[6].blocks[4] = faces[0].blocks[4];
        faces[6].blocks[5] = faces[0].blocks[5];
        faces[6].blocks[6] = faces[0].blocks[6];
        faces[7].blocks[4] = faces[0].blocks[3];
        faces[7].blocks[6] = faces[0].blocks[7];
        faces[8].blocks[6] = faces[0].blocks[0];
        faces[8].blocks[5] = faces[0].blocks[1];
        faces[8].blocks[4] = faces[0].blocks[2];
      }; break;
      case 1: {
        if (rotating.direction) {
          faces[1].blocks = {faces[1].blocks[2], faces[1].blocks[3], faces[1].blocks[4], faces[1].blocks[5], faces[1].blocks[6], faces[1].blocks[7], faces[1].blocks[0], faces[1].blocks[1]};
        } else {
          faces[1].blocks = {faces[1].blocks[6], faces[1].blocks[7], faces[1].blocks[0], faces[1].blocks[1], faces[1].blocks[2], faces[1].blocks[3], faces[1].blocks[4], faces[1].blocks[5]};
        }
        faces[3].blocks[3] = faces[1].blocks[2];
        faces[3].blocks[7] = faces[1].blocks[4];
        faces[4].blocks[3] = faces[1].blocks[1];
        faces[4].blocks[7] = faces[1].blocks[5];
        faces[5].blocks[3] = faces[1].blocks[0];
        faces[5].blocks[7] = faces[1].blocks[6];
        faces[6].blocks[3] = faces[1].blocks[4];
        faces[6].blocks[7] = faces[1].blocks[6];
        faces[7].blocks[3] = faces[1].blocks[3];
        faces[7].blocks[7] = faces[1].blocks[7];
        faces[8].blocks[7] = faces[1].blocks[0];
        faces[8].blocks[3] = faces[1].blocks[2];
      }; break;
      case 2: {
        if (rotating.direction) {
          faces[2].blocks = {faces[2].blocks[2], faces[2].blocks[3], faces[2].blocks[4], faces[2].blocks[5], faces[2].blocks[6], faces[2].blocks[7], faces[2].blocks[0], faces[2].blocks[1]};
        } else {
          faces[2].blocks = {faces[2].blocks[6], faces[2].blocks[7], faces[2].blocks[0], faces[2].blocks[1], faces[2].blocks[2], faces[2].blocks[3], faces[2].blocks[4], faces[2].blocks[5]};
        }
        faces[3].blocks[4] = faces[2].blocks[2];
        faces[3].blocks[5] = faces[2].blocks[3];
        faces[3].blocks[6] = faces[2].blocks[4];
        faces[4].blocks[4] = faces[2].blocks[1];
        faces[4].blocks[6] = faces[2].blocks[5];
        faces[5].blocks[4] = faces[2].blocks[0];
        faces[5].blocks[6] = faces[2].blocks[6];
        faces[5].blocks[5] = faces[2].blocks[7];
        faces[6].blocks[2] = faces[2].blocks[4];
        faces[6].blocks[1] = faces[2].blocks[5];
        faces[6].blocks[0] = faces[2].blocks[6];
        faces[7].blocks[2] = faces[2].blocks[3];
        faces[7].blocks[0] = faces[2].blocks[7];
        faces[8].blocks[0] = faces[2].blocks[0];
        faces[8].blocks[1] = faces[2].blocks[1];
        faces[8].blocks[2] = faces[2].blocks[2];
      }; break;
      case 3: {
        if (rotating.direction) {
          faces[3].blocks = {faces[3].blocks[2], faces[3].blocks[3], faces[3].blocks[4], faces[3].blocks[5], faces[3].blocks[6], faces[3].blocks[7], faces[3].blocks[0], faces[3].blocks[1]};
        } else {
          faces[3].blocks = {faces[3].blocks[6], faces[3].blocks[7], faces[3].blocks[0], faces[3].blocks[1], faces[3].blocks[2], faces[3].blocks[3], faces[3].blocks[4], faces[3].blocks[5]};
        }
        faces[0].blocks[2] = faces[3].blocks[2];
        faces[0].blocks[3] = faces[3].blocks[1];
        faces[0].blocks[4] = faces[3].blocks[0];
        faces[1].blocks[2] = faces[3].blocks[3];
        faces[1].blocks[4] = faces[3].blocks[7];
        faces[2].blocks[2] = faces[3].blocks[4];
        faces[2].blocks[3] = faces[3].blocks[5];
        faces[2].blocks[4] = faces[3].blocks[6];
        faces[6].blocks[4] = faces[3].blocks[0];
        faces[6].blocks[2] = faces[3].blocks[6];
        faces[6].blocks[3] = faces[3].blocks[7];
        faces[7].blocks[4] = faces[3].blocks[1];
        faces[7].blocks[2] = faces[3].blocks[5];
        faces[8].blocks[4] = faces[3].blocks[2];
        faces[8].blocks[3] = faces[3].blocks[3];
        faces[8].blocks[2] = faces[3].blocks[4];
      }; break;
      case 4: {
        if (rotating.direction) {
          faces[4].blocks = {faces[4].blocks[2], faces[4].blocks[3], faces[4].blocks[4], faces[4].blocks[5], faces[4].blocks[6], faces[4].blocks[7], faces[4].blocks[0], faces[4].blocks[1]};
        } else {
          faces[4].blocks = {faces[4].blocks[6], faces[4].blocks[7], faces[4].blocks[0], faces[4].blocks[1], faces[4].blocks[2], faces[4].blocks[3], faces[4].blocks[4], faces[4].blocks[5]};
        }
        faces[0].blocks[1] = faces[4].blocks[2];
        faces[0].blocks[5] = faces[4].blocks[0];
        faces[1].blocks[1] = faces[4].blocks[3];
        faces[1].blocks[5] = faces[4].blocks[7];
        faces[2].blocks[1] = faces[4].blocks[4];
        faces[2].blocks[5] = faces[4].blocks[6];
        faces[6].blocks[5] = faces[4].blocks[0];
        faces[6].blocks[1] = faces[4].blocks[6];
        faces[7].blocks[5] = faces[4].blocks[1];
        faces[7].blocks[1] = faces[4].blocks[5];
        faces[8].blocks[5] = faces[4].blocks[2];
        faces[8].blocks[1] = faces[4].blocks[4];
      }; break;
      case 5: {
        if (rotating.direction) {
          faces[5].blocks = {faces[5].blocks[2], faces[5].blocks[3], faces[5].blocks[4], faces[5].blocks[5], faces[5].blocks[6], faces[5].blocks[7], faces[5].blocks[0], faces[5].blocks[1]};
        } else {
          faces[5].blocks = {faces[5].blocks[6], faces[5].blocks[7], faces[5].blocks[0], faces[5].blocks[1], faces[5].blocks[2], faces[5].blocks[3], faces[5].blocks[4], faces[5].blocks[5]};
        }
        faces[0].blocks[0] = faces[5].blocks[2];
        faces[0].blocks[6] = faces[5].blocks[0];
        faces[0].blocks[7] = faces[5].blocks[1];
        faces[1].blocks[0] = faces[5].blocks[3];
        faces[1].blocks[6] = faces[5].blocks[7];
        faces[2].blocks[0] = faces[5].blocks[4];
        faces[2].blocks[6] = faces[5].blocks[6];
        faces[2].blocks[7] = faces[5].blocks[5];
        faces[6].blocks[6] = faces[5].blocks[0];
        faces[6].blocks[0] = faces[5].blocks[6];
        faces[6].blocks[7] = faces[5].blocks[7];
        faces[7].blocks[6] = faces[5].blocks[1];
        faces[7].blocks[0] = faces[5].blocks[5];
        faces[8].blocks[6] = faces[5].blocks[2];
        faces[8].blocks[7] = faces[5].blocks[3];
        faces[8].blocks[0] = faces[5].blocks[4];
      }; break;
      case 6: {
        if (rotating.direction) {
          faces[6].blocks = {faces[6].blocks[2], faces[6].blocks[3], faces[6].blocks[4], faces[6].blocks[5], faces[6].blocks[6], faces[6].blocks[7], faces[6].blocks[0], faces[6].blocks[1]};
        } else {
          faces[6].blocks = {faces[6].blocks[6], faces[6].blocks[7], faces[6].blocks[0], faces[6].blocks[1], faces[6].blocks[2], faces[6].blocks[3], faces[6].blocks[4], faces[6].blocks[5]};
        }
        faces[0].blocks[4] = faces[6].blocks[4];
        faces[0].blocks[5] = faces[6].blocks[5];
        faces[0].blocks[6] = faces[6].blocks[6];
        faces[1].blocks[4] = faces[6].blocks[3];
        faces[1].blocks[6] = faces[6].blocks[7];
        faces[2].blocks[4] = faces[6].blocks[2];
        faces[2].blocks[5] = faces[6].blocks[1];
        faces[2].blocks[6] = faces[6].blocks[0];
        faces[3].blocks[0] = faces[6].blocks[4];
        faces[3].blocks[6] = faces[6].blocks[2];
        faces[3].blocks[7] = faces[6].blocks[3];
        faces[4].blocks[0] = faces[6].blocks[5];
        faces[4].blocks[6] = faces[6].blocks[1];
        faces[5].blocks[0] = faces[6].blocks[6];
        faces[5].blocks[6] = faces[6].blocks[0];
        faces[5].blocks[7] = faces[6].blocks[7];
      }; break;
      case 7: {
        if (rotating.direction) {
          faces[7].blocks = {faces[7].blocks[2], faces[7].blocks[3], faces[7].blocks[4], faces[7].blocks[5], faces[7].blocks[6], faces[7].blocks[7], faces[7].blocks[0], faces[7].blocks[1]};
        } else {
          faces[7].blocks = {faces[7].blocks[6], faces[7].blocks[7], faces[7].blocks[0], faces[7].blocks[1], faces[7].blocks[2], faces[7].blocks[3], faces[7].blocks[4], faces[7].blocks[5]};
        }
        faces[0].blocks[3] = faces[7].blocks[4];
        faces[0].blocks[7] = faces[7].blocks[6];
        faces[1].blocks[3] = faces[7].blocks[3];
        faces[1].blocks[7] = faces[7].blocks[7];
        faces[2].blocks[3] = faces[7].blocks[2];
        faces[2].blocks[7] = faces[7].blocks[0];
        faces[3].blocks[1] = faces[7].blocks[4];
        faces[3].blocks[5] = faces[7].blocks[2];
        faces[4].blocks[1] = faces[7].blocks[5];
        faces[4].blocks[5] = faces[7].blocks[1];
        faces[5].blocks[1] = faces[7].blocks[6];
        faces[5].blocks[5] = faces[7].blocks[0];
      }; break;
      case 8: {
        if (rotating.direction) {
          faces[8].blocks = {faces[8].blocks[2], faces[8].blocks[3], faces[8].blocks[4], faces[8].blocks[5], faces[8].blocks[6], faces[8].blocks[7], faces[8].blocks[0], faces[8].blocks[1]};
        } else {
          faces[8].blocks = {faces[8].blocks[6], faces[8].blocks[7], faces[8].blocks[0], faces[8].blocks[1], faces[8].blocks[2], faces[8].blocks[3], faces[8].blocks[4], faces[8].blocks[5]};
        }
        faces[0].blocks[0] = faces[8].blocks[6];
        faces[0].blocks[1] = faces[8].blocks[5];
        faces[0].blocks[2] = faces[8].blocks[4];
        faces[1].blocks[0] = faces[8].blocks[7];
        faces[1].blocks[2] = faces[8].blocks[3];
        faces[2].blocks[0] = faces[8].blocks[0];
        faces[2].blocks[1] = faces[8].blocks[1];
        faces[2].blocks[2] = faces[8].blocks[2];
        faces[3].blocks[2] = faces[8].blocks[4];
        faces[3].blocks[3] = faces[8].blocks[3];
        faces[3].blocks[4] = faces[8].blocks[2];
        faces[4].blocks[2] = faces[8].blocks[5];
        faces[4].blocks[4] = faces[8].blocks[1];
        faces[5].blocks[2] = faces[8].blocks[6];
        faces[5].blocks[3] = faces[8].blocks[7];
        faces[5].blocks[4] = faces[8].blocks[0];
      }; break;
    }

    rotating.face_idx = faces.size();
    rotating.angle = 0.0f;
  }

  void rotate(uintmax_t face_idx, bool direction = false) {
    rotating.face_idx = face_idx;
    rotating.direction = direction;
    rotating.angle = 0.0f;
  }

  void update() {
    float delta = ((rotating.direction) ? -1.0f : 1.0f) * DEG2RAD * rotating.angle_delta;
    if (rotating.face_idx < faces.size()) {
      for (auto block_idx : faces[rotating.face_idx].blocks) {
        blocks[block_idx].model.transform = MatrixMultiply(blocks[block_idx].model.transform, MatrixRotate(faces[rotating.face_idx].axis, delta));
      }
      blocks[faces[rotating.face_idx].center].model.transform = MatrixMultiply(blocks[faces[rotating.face_idx].center].model.transform, MatrixRotate(faces[rotating.face_idx].axis, delta));
      rotating.angle += rotating.angle_delta;
      if (rotating.angle >= 90.0f) {
        end_rotation();
      }
    }
  }

  void reset() {
    for (Block& block : blocks) {
      block.reset();
    }
    for (Face& face : faces) {
      face.reset();
    }
  }
};

int main() {
  const int screenWidth = 1024;
  const int screenHeight = 768;
  const int fps = 60;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera first person");
  SetTargetFPS(fps);
  ShowCursor();

  Camera camera = {
    .position = Vector3 {.x =  -2.0f, .y = 2.0f, .z = -2.0f },
    .target = Vector3 {.x =  0.0f, .y = 0.0f, .z = 0.0f },
    .up = Vector3 {.x =  0.0f, .y = 1.0f, .z = 0.0f },
    .fovy = 90.0f,
    .projection = CAMERA_PERSPECTIVE
  };
  int cameraMode = CAMERA_CUSTOM;

  Rubik rubik = Rubik::Load();

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    if (rubik.rotating.face_idx >= rubik.faces.size()) {
      if (IsKeyPressed(KEY_R)) {
        rubik.reset();
      } else if (IsKeyPressed(KEY_ONE)) {
        rubik.rotate(0, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_TWO)) {
        rubik.rotate(1, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_THREE)) {
        rubik.rotate(2, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_FOUR)) {
        rubik.rotate(3, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_FIVE)) {
        rubik.rotate(4, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_SIX)) {
        rubik.rotate(5, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_SEVEN)) {
        rubik.rotate(6, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_EIGHT)) {
        rubik.rotate(7, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyPressed(KEY_NINE)) {
        rubik.rotate(8, IsKeyDown(KEY_RIGHT_SHIFT));
      }
    }

    rubik.update();

    UpdateCamera(&camera, cameraMode);
    BeginDrawing();
      ClearBackground(WHITE);
      BeginMode3D(camera);
        for (auto block : rubik.blocks) {
          DrawModel(block.model, {0,0,0}, 1.0f, WHITE);
        }
        DrawGrid(100.0f, 0.5f);
      EndMode3D();
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
