#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#define DROPLET_COUNT 7000
#define AVERAGE_FALL_SPEED 25
#define WINDOW_WIDTH 1300
#define WINDOW_HEIGHT 500
typedef struct {
  Vector2 position;
  float speed;
  Color color;
} Point;

int main(void) {
  srand(time(NULL));

  Point droplets[DROPLET_COUNT];
  for (int i = 0; i < DROPLET_COUNT; i++) {
    int r = rand();
    float speed = AVERAGE_FALL_SPEED * (r % 10 + 1) + 5;
    float x = r % WINDOW_WIDTH + 1;
    float y = r % WINDOW_HEIGHT + 1;
    float speed_to_color = AVERAGE_FALL_SPEED * 10;
    Color droplet_color =
        (Color){speed_to_color, speed_to_color, speed_to_color, 255};
    droplets[i] = (Point){(Vector2){x, y}, speed, droplet_color};
  }

  SetTargetFPS(60);
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rain");
  float timescale = 3;
  bool paused = false;
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(0, 0);
    DrawText(TextFormat("Iterations Per Frame: %d", DROPLET_COUNT), 0, 25, 20,
             LIME);
    DrawText("Directional arrows control the flow of time", 0, 50, 20, LIME);
    DrawText("Space pauses time", 0, 75, 20, LIME);
    DrawText(TextFormat("Timescale: %f", timescale), 1, 100, 20, LIME);
    if (paused) {
      DrawText("Paused", 0, 125, 20, RED);
    }

    if (IsKeyDown(KEY_DOWN)) {
      timescale -= 0.1;
    }

    if (IsKeyDown(KEY_UP)) {
      timescale += 0.1;
    }

    if (IsKeyPressed(KEY_SPACE)) {
      paused = !paused;
    }

    for (int i = 0; i < DROPLET_COUNT; i++) {
      DrawPixel(droplets[i].position.x, droplets[i].position.y,
                droplets[i].color);
      if (!paused) {
        droplets[i].position.y +=
            droplets[i].speed * GetFrameTime() * timescale;
        if (droplets[i].position.y > WINDOW_HEIGHT) {
          droplets[i].position.y = rand() % WINDOW_HEIGHT / 2.0;
        } else if (droplets[i].position.y < 0) {
          droplets[i].position.y = rand() % WINDOW_HEIGHT;
        }
      }
    }
    EndDrawing();
  }
  return 0;
}
