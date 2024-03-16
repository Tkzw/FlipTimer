#include <M5Core2.h>

class TimerView {
private:
  uint16_t mBackcolor, mBackcolor1, mBackcolor2;
  RTC_TimeTypeDef mTime;
  int mX, mY, mWidth, mHeight;
  TFT_eSprite mSplite;
  int16_t mRotateAngle;

public:
  TimerView();
  void setTime(RTC_TimeTypeDef time);
  void show();
  void setFlip(bool flip);
};