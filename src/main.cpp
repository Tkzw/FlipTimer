#include <M5Core2.h>

#include "TimerView.hpp"
#include "TimerControl.hpp"

TimerView timerView;
TimerControl timerControl(&timerView);

void setup() {
  M5.begin();
  M5.IMU.Init();
}

void loop() {
  M5.update();

  timerControl.update();
  timerView.update();

  delay(100);
}
