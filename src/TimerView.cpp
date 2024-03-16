#include "TimerView.hpp"

TimerView::TimerView() : mSplite(&M5.Lcd) {
    mBackcolor1 = M5.Lcd.color565(167, 255, 255);
    mBackcolor2 = M5.Lcd.color565(210, 159, 255);
    mBackcolor = mBackcolor1;
    mTime.Hours = 0;
    mTime.Minutes = 0;
    mTime.Seconds = 0;
    mX = 10;
    mY = 60;
    mWidth = 300;
    mHeight = 120;
    mRotateAngle = 0;

    mSplite.setColorDepth(8);
    mSplite.createSprite(mWidth, mHeight);
}

void TimerView::setTime(RTC_TimeTypeDef time) {
    mTime = time;
}

void TimerView::show() {
    static char timeStrbuff[64];

    mSplite.fillRect(0, 0, mWidth, mHeight, mBackcolor);

    sprintf(timeStrbuff, "%02d:%02d", mTime.Minutes, mTime.Seconds);

    mSplite.setCursor(5, 5);
    mSplite.setTextColor(BLACK);
    mSplite.setTextSize(7);
    mSplite.println(timeStrbuff);
    
    M5.Lcd.setPivot(M5.Lcd.width()/2, M5.Lcd.height()/2);
    mSplite.setPivot(mWidth/2, mHeight/2);
    mSplite.pushRotated(mRotateAngle);
}

void TimerView::setFlip(bool flip) {
    mRotateAngle = (flip) ? 180 : 0;
    mBackcolor = (flip) ? mBackcolor1 : mBackcolor2;
}