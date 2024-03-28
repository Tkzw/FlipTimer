#include "TimerControl.hpp"
#include "TimerView.hpp"

TimerControl::TimerControl(TimerView* tv): 
  oldIsFlipped(false),
  isFirstTime(true),
  tView()
  {
    setupTime();

    timerLimmit1 = initRTC_TimeTypeDef(0,25,0);
    timerLimmit2 = initRTC_TimeTypeDef(0,5,0);
    tView = tv;
  }
  
  void TimerControl::update() {
    RTC_TimeTypeDef currentTime;

    M5.Rtc.GetTime(&currentTime); 
    bool currentFlip = isFlipped();

    if ((oldIsFlipped != currentFlip) || (isFirstTime)) {
      startTime = currentTime;
      currentTimerLimmit = (currentFlip) ? timerLimmit1 : timerLimmit2;
      isFirstTime = false;
    }

    tView->setFlip(currentFlip);
    
    tView->setTime(diffTime(currentTimerLimmit, diffTime(currentTime, startTime)));

    oldIsFlipped = currentFlip;
  }

  void TimerControl::setupTime() {
    RTC_TimeTypeDef RTCtime;

    RTCtime.Hours = 0; 
    RTCtime.Minutes = 0;
    RTCtime.Seconds = 0;
    if (!M5.Rtc.SetTime(&RTCtime)) Serial.println("wrong time set!");
  }

  RTC_TimeTypeDef TimerControl::diffTime (RTC_TimeTypeDef a, RTC_TimeTypeDef b) {
    RTC_TimeTypeDef ret = {0,0,0};

    ret.Seconds = a.Seconds - b.Seconds;
    ret.Minutes = a.Minutes - b.Minutes;
    ret.Hours = a.Hours - b.Hours;
    
    if (ret.Minutes < 0) {
      ret.Minutes += 60;
      ret.Hours -= 1;
    }

    if (ret.Seconds < 0) {
      ret.Seconds += 60;
      ret.Minutes -= 1;
    }

    return ret;
  }

  RTC_TimeTypeDef TimerControl::initRTC_TimeTypeDef(int8_t h, int8_t m, int8_t s) {
    RTC_TimeTypeDef ret;
    ret.Hours = h;
    ret.Minutes = m;
    ret.Seconds = s;
    return ret;
  }
  
  bool TimerControl::isFlipped() {
    float accX,accY,accZ;

    M5.IMU.getAccelData(&accX, &accY, &accZ); 

    return  0.0f > accY;
  }