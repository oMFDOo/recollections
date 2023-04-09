#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (44, 45, 46, 47, 48, 49);
RTC_DS1307 RTC;

void setup () {
   lcd.begin(16, 2);                    // LCD 초기화 
   lcd.clear();

  Serial.begin(9600);
  if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(2021, 4, 27, 0, 0, 0));
  }
}

void loop () {
    DateTime timeSet = RTC.now();

    lcd.setCursor(0, 0);
    lcd.write("Time:"); 
    lcd.setCursor(0, 1);    
    lcd.write("Date:");
   
    // 시간(hh:mm:ss)을 출력
    String numStr;

    if(timeSet.hour() < 10) numStr += '0';
    numStr += (String)timeSet.hour();         // 이전 문자에 hour추가
    numStr += ":";
    if(timeSet.minute() < 10) numStr += '0';
    numStr += (String)timeSet.minute();         // 이전 문자에 miutes추가
    numStr += ":";
    if(timeSet.second() < 10) numStr += '0';
    numStr += (String)timeSet.second();         // 이전 문자에 seconds추가
    lcd.setCursor(7, 0);
    lcd.print(numStr);      // numStr변수에 담긴 시간 정보(hh:mm:ss) 출력
        
    String date;
    date += (String)timeSet.year();         // 이전 문자에 year추가
    date += "/";
    if(timeSet.month() < 10) numStr += '0';
    date += (String)timeSet.month();         // 이전 문자에 month추가
    date += "/";
    if(timeSet.day() < 10) numStr += '0';
    date += (String)timeSet.day();         // 이전 문자에 day추가
    lcd.setCursor(6, 1);
    lcd.print(date);      // numStr변수에 담긴 시간 정보(yyyy:mm:dd) 출력

    delay(1000);
}