#include <M5Core2.h>

class TimerView;

class TimerControl {
private:
  bool oldIsFlipped;
  bool isFirstTime;
  TimerView *tView;
  RTC_TimeTypeDef startTime;

  RTC_TimeTypeDef timerLimmit1;
  RTC_TimeTypeDef timerLimmit2;
  RTC_TimeTypeDef currentTimerLimmit;

public:
  TimerControl(TimerView* tv);
  void update();

private:
  void setupTime();
  RTC_TimeTypeDef diffTime (RTC_TimeTypeDef a, RTC_TimeTypeDef b);
  RTC_TimeTypeDef initRTC_TimeTypeDef(int8_t h, int8_t m, int8_t s);
  bool isFlipped();
};