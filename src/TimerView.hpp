#include <M5Core2.h>

#ifndef TIMER_VIEW_H
#define TIMER_VIEW_H

class TimerView {
private:
  class Timer{

  };

private:
  uint16_t mBackcolor, mBackcolor1, mBackcolor2;
  RTC_TimeTypeDef mTime;
  int mX, mY, mWidth, mHeight;
  TFT_eSprite mSplite;
  int16_t mRotateAngle;

public:
  TimerView();
  void setTime(RTC_TimeTypeDef time);
  void update();
  void setFlip(bool flip);
  void notice();

public:
  static void stopViblate();
};

#endif 