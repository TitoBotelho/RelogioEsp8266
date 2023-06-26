#include "PongGame.h"

PongGame::PongGame() : display(0x3c, 5, 4) {}

void PongGame::setup() {
  display.init();
  display.flipScreenVertically();

  ball_x = 64;
  ball_y = 32;
  ball_dir_x = -1;
  ball_dir_y = 1;
  paddle_update = cpu_y = player_y = up_state = down_state = 0;

  ball_update = paddle_update = millis(); // Tempo inicial ajustado

  display.clear();
  display.display();
}

void PongGame::loop() {
  unsigned long currentMillis = millis();

      up_state |= (digitalRead(UP_BUTTON) == LOW);
    down_state |= (digitalRead(DOWN_BUTTON) == LOW);

  if (currentMillis - ball_update >= BALL_RATE) {
    ball_update = currentMillis;
    updateBall();
  }

  if (currentMillis - paddle_update >= PADDLE_RATE) {
    paddle_update = currentMillis;
    updatePaddles();
  }


  display.display();
  delay(1);
}

void PongGame::updatePaddles() {
  static uint8_t prev_cpu_y = cpu_y;
  static uint8_t prev_player_y = player_y;

  // Erase previous paddle positions
  for (uint8_t y = prev_cpu_y; y < prev_cpu_y + PADDLE_HEIGHT; y++) {
    screen_buffer[CPU_X][y] = false;
  }

  for (uint8_t y = prev_player_y; y < prev_player_y + PADDLE_HEIGHT; y++) {
    screen_buffer[PLAYER_X][y] = false;
  }

  // CPU paddle
  const uint8_t half_paddle = PADDLE_HEIGHT >> 1;
  if (cpu_y + half_paddle > ball_y) {
    cpu_y -= 1;
  }
  if (cpu_y + half_paddle < ball_y) {
    cpu_y += 1;
  }
  if (cpu_y < 1) cpu_y = 1;
  if (cpu_y + PADDLE_HEIGHT > 63) cpu_y = 63 - PADDLE_HEIGHT;

  // Player paddle
  if (up_state) {
    player_y -= 1;
  }
  if (down_state) {
    player_y += 1;
  }
  up_state = down_state = false;
  if (player_y < 1) player_y = 1;
  if (player_y + PADDLE_HEIGHT > 63) player_y = 63 - PADDLE_HEIGHT;

  // Draw updated paddle positions
  for (uint8_t y = cpu_y; y < cpu_y + PADDLE_HEIGHT; y++) {
    screen_buffer[CPU_X][y] = true;
  }

  for (uint8_t y = player_y; y < player_y + PADDLE_HEIGHT; y++) {
    screen_buffer[PLAYER_X][y] = true;
  }

  prev_cpu_y = cpu_y;
  prev_player_y = player_y;
}

void PongGame::updateBall() {
  // Erase previous ball position
  screen_buffer[ball_x][ball_y] = false;

  uint8_t new_x = ball_x + ball_dir_x;
  uint8_t new_y = ball_y + ball_dir_y;

  // Check if we hit the vertical walls
  if (new_x == 0 || new_x == 127) {
    ball_dir_x = -ball_dir_x;
    new_x += ball_dir_x + ball_dir_x;
  }

  // Check if we hit the horizontal walls.
  if (new_y == 0 || new_y == 63) {
    ball_dir_y = -ball_dir_y;
    new_y += ball_dir_y + ball_dir_y;
  }

  // Check if we hit the CPU paddle
  if (new_x == CPU_X && new_y >= cpu_y && new_y <= cpu_y + PADDLE_HEIGHT) {
    ball_dir_x = -ball_dir_x;
    new_x += ball_dir_x + ball_dir_x;
  }

  // Check if we hit the player paddle
  if (new_x == PLAYER_X && new_y >= player_y && new_y <= player_y + PADDLE_HEIGHT) {
    ball_dir_x = -ball_dir_x;
    new_x += ball_dir_x + ball_dir_x;
  }

  ball_x = new_x;
  ball_y = new_y;

  // Draw updated ball position
  screen_buffer[ball_x][ball_y] = true;

  // Update display only for modified areas
  for (uint8_t x = 0; x < 128; x++) {
    for (uint8_t y = 0; y < 64; y++) {
      if (screen_buffer[x][y]) {
        display.setPixel(x, y);
      } else {
        display.clearPixel(x, y);
      }
    }
  }
}
