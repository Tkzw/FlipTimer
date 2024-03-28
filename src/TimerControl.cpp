#include "TimerControl.hpp"
#include "TimerView.hpp"

TimerControl::TimerControl(TimerView* tv): 
  oldIsFlipped(false),
  isFirstTime(true),
  isNoticed(false),
  tView()
  {
    setupTime();

    timerLimmit1 = initRTC_TimeTypeDef(0,25,0); // 25min
    timerLimmit2 = initRTC_TimeTypeDef(0,5,0);  // 5min
    tView = tv;
  }
  
  void TimerControl::update() {
    RTC_TimeTypeDef currentTime;

    M5.Rtc.GetTime(&currentTime); 
    bool currentFlip = isFlipped();

    if ((oldIsFlipped != currentFlip) || (isFirstTime)) {
      startTime = currentTime;
      currentTimerLimmit = (currentFlip) ? timerLimmit1 : timerLimmit2;
      isNoticed = false;

      isFirstTime = false;
    }

    tView->setFlip(currentFlip);

    RTC_TimeTypeDef cdTime = diffTime(currentTimerLimmit, diffTime(currentTime, startTime));
    tView->setTime(cdTime);

    if ((!isNoticed) && (cdTime.Hours == 0) && (cdTime.Minutes == 0) && cdTime.Seconds == 0) {
      tView->notice();
      isNoticed = true;
    }

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

    int32_t aInSec = a.Hours * 3600 + a.Minutes * 60 + a.Seconds;
    int32_t bInSec = b.Hours * 3600 + b.Minutes * 60 + b.Seconds;

    int32_t diff = (aInSec - bInSec > 0) ? aInSec - bInSec : 0; 

    ret.Hours = diff / 3600;
    diff %= 3600;
    ret.Minutes = diff / 60;
    diff %= 60;
    ret.Seconds = diff; 

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