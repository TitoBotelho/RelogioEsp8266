// PongGame.h

#ifndef PongGame_h
#define PongGame_h

#include <Wire.h>
#include <SH1106Wire.h>

#define UP_BUTTON 2
#define DOWN_BUTTON 0

class PongGame {
public:
  PongGame();

  void setup();
  void loop();

    bool up_state;
  bool down_state;

private:
  SH1106Wire display;
  uint8_t ball_x, ball_y;
  int8_t ball_dir_x, ball_dir_y;
  unsigned long ball_update;
  unsigned long paddle_update;
  const uint8_t CPU_X = 12;
  uint8_t cpu_y;
  const uint8_t PLAYER_X = 115;
  uint8_t player_y;

  bool screen_buffer[128][64];

  void updatePaddles();
  void updateBall();


  static const unsigned long BALL_RATE = 30;
  static const unsigned long PADDLE_RATE = 30;
  static const uint8_t PADDLE_HEIGHT = 16;
  static const uint8_t PADDLE = 32;
};

#endif
