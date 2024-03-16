#include <M5Core2.h>

#include "TimerView.hpp"

// ボタン
ButtonColors cl_on = {CYAN, WHITE, WHITE};      // タップした時の色 (背景, 文字列, ボーダー)
ButtonColors cl_off = {DARKCYAN, WHITE, WHITE}; // 指を離した時の色 (背景, 文字列, ボーダー)

// ボタン定義名( X軸, Y軸, 横幅, 高さ, 回転, ボタンのラベル, 指を離した時の色指定, タッチした時の色指定）
Button btn_start(90, 210, 140, 30, false, "Start", cl_off, cl_on);
// TFT_eSPI_Button btn_start;



class TimerControl {
private:
  bool oldIsFlipped;
  bool isFirstTime;
  TimerView tView;
  RTC_TimeTypeDef startTime;

  RTC_TimeTypeDef timerLimmit1;
  RTC_TimeTypeDef timerLimmit2;
  RTC_TimeTypeDef currentTimerLimmit;

public:
  TimerControl(): 
  oldIsFlipped(false),
  isFirstTime(true),
  tView()
  {
    setupTime();

    timerLimmit1 = initRTC_TimeTypeDef(0,25,0);
    timerLimmit2 = initRTC_TimeTypeDef(0,5,0);
  }
  
  void flushTime() {
    RTC_TimeTypeDef currentTime;

    M5.Rtc.GetTime(&currentTime); 
    bool currentFlip = isFlipped();

    if ((oldIsFlipped != currentFlip) || (isFirstTime)) {
      startTime = currentTime;
      currentTimerLimmit = (currentFlip) ? timerLimmit1 : timerLimmit2;
      isFirstTime = false;
    }

    tView.setFlip(currentFlip);
    
    tView.setTime(diffTime(currentTimerLimmit, diffTime(currentTime, startTime)));
    tView.show();

    oldIsFlipped = currentFlip;
  }

private:
  void setupTime() {
    RTC_TimeTypeDef RTCtime;

    RTCtime.Hours = 0; 
    RTCtime.Minutes = 0;
    RTCtime.Seconds = 0;
    if (!M5.Rtc.SetTime(&RTCtime)) Serial.println("wrong time set!");
  }

  RTC_TimeTypeDef diffTime (RTC_TimeTypeDef a, RTC_TimeTypeDef b) {
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

  RTC_TimeTypeDef initRTC_TimeTypeDef(int8_t h, int8_t m, int8_t s) {
    RTC_TimeTypeDef ret;
    ret.Hours = h;
    ret.Minutes = m;
    ret.Seconds = s;
    return ret;
  }
  
  bool isFlipped() {
    float accX,accY,accZ;

    M5.IMU.getAccelData(&accX, &accY, &accZ); 

    return  0.0f > accY;
  }

};

TimerControl timerControl;

void event_btn_start(Event &e)
{
  //isTimerStart = true;
}


void setup() {
  M5.begin();  // Init M5Core2.  初始化 M5Core2
  M5.IMU.Init();                     // Init IMU sensor. 
  
  // M5.Buttons.setFont(FSSB12);
  // btn_start.setFont(FSSB12);
  // btn_start.addHandler(event_btn_start, E_RELEASE);
  // M5.Buttons.draw();
}

void loop() {
  M5.update();

  timerControl.flushTime();

  delay(100);
}
