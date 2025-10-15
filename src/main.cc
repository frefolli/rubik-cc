#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <string>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
  out << "{ ";
  for (auto el : vec) {
    out << el << " ";
  }
  out << "}";
  return out;
}

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
  std::vector<std::pair<uintmax_t, bool>> history;

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
      #include "faces.cc"
    };

    return Rubik {
      .blocks = blocks,
      .faces = faces,
      .history = {},
      .rotating = Rotating {},
    };
  }

  void end_rotation() {
    #include "transition.cc"
    rotating.face_idx = faces.size();
    rotating.angle = 0.0f;
  }

  void rotate(uintmax_t face_idx, bool direction = false) {
    rotating.face_idx = face_idx;
    rotating.direction = direction;
    rotating.angle = 0.0f;

    history.push_back({rotating.face_idx, rotating.direction});
  }

  void update() {
    float delta = ((rotating.direction) ? -1.0f : 1.0f) * DEG2RAD * rotating.angle_delta;
    if (rotating.face_idx < faces.size()) {
      for (auto block_idx : faces[rotating.face_idx].blocks) {
        blocks[block_idx].model.transform = MatrixMultiply(blocks[block_idx].model.transform, MatrixRotate(faces[rotating.face_idx].axis, delta));
      }
      rotating.angle += rotating.angle_delta;
      if (rotating.angle >= 90.0f) {
        end_rotation();
      }
    }
  }

  void revert() {
    if (!history.empty()) {
      rotate(history.back().first, !history.back().second);
      history.pop_back();
      history.pop_back();
    }
  }

  void reset() {
    for (Block& block : blocks) {
      block.reset();
    }
    for (Face& face : faces) {
      face.reset();
    }
    history.clear();
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
    .position = Vector3 {.x =  -2.0f, .y = 2.0f, .z = 2.0f },
    .target = Vector3 {.x =  0.0f, .y = 0.0f, .z = 0.0f },
    .up = Vector3 {.x =  0.0f, .y = 1.0f, .z = 0.0f },
    .fovy = 90.0f,
    .projection = CAMERA_PERSPECTIVE
  };
  int cameraMode = CAMERA_CUSTOM;

  bool engage_random = false;
  bool engage_revert = false;

  Rubik rubik = Rubik::Load();

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    if (rubik.rotating.face_idx >= rubik.faces.size()) {
      if (IsKeyDown(KEY_Q)) {
          rubik.reset();
      } else if (IsKeyPressed(KEY_W)) {
          engage_random = !engage_random;
      } else if (IsKeyPressed(KEY_E)) {
          engage_revert = !engage_revert;
      } else if (IsKeyDown(KEY_ONE)) {
        rubik.rotate(0, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_TWO)) {
        rubik.rotate(1, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_THREE)) {
        rubik.rotate(2, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_FOUR)) {
        rubik.rotate(3, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_FIVE)) {
        rubik.rotate(4, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_SIX)) {
        rubik.rotate(5, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_SEVEN)) {
        rubik.rotate(6, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_EIGHT)) {
        rubik.rotate(7, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (IsKeyDown(KEY_NINE)) {
        rubik.rotate(8, IsKeyDown(KEY_RIGHT_SHIFT));
      } else if (engage_revert) {
          rubik.revert();
      } else if (engage_random) {
        rubik.rotate(std::rand() % 9, std::rand() % 2);
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
