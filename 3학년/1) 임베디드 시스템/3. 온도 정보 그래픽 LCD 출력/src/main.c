#include <RTClib.h>
#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal.h>
#include <openGLCD.h>

LiquidCrystal lcd (44, 45, 46, 47, 48, 49);
RTC_DS1307 RTC;

int reading = analogRead(55);

void setup() {
   Serial.begin(9600);

   if (! RTC.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(2021, 4, 27, 0, 0, 0));
  }
   GLCD.Init();
   GLCD.SelectFont(System5x7);
}

void loop(){
   GLCD.DrawRect(0, 0, 128, 64);	// 테두리 사각형 출력
   DateTime timeSet = RTC.now();	// RTC를 이용한 현재 시간 받아오기

   delay(1000);

   GLCD.CursorTo(12, 6);		// 온도 값 출력 위치 설정
   int reading = analogRead(55);
   float temperatureC = (reading * 5.0 / 1024.0) * 100;	// 측정된 온도 변환
   GLCD.print(temperatureC, 2);		// GLCD에 온도 값 출력
   GLCD.print(" C");				// GLCD에 섭씨 표시 기호 출력

   String numStr;
   GLCD.CursorTo(7, 3);				// 시간 값 출력 위치 설정
   if(timeSet.hour() < 10) numStr += '0';
   numStr += (String)timeSet.hour();         	// 이전 문자에 hour추가
   numStr += ":";
   if(timeSet.minute() < 10) numStr += '0';
   numStr += (String)timeSet.minute();         // 이전 문자에 miutes추가
   numStr += ":";
   if(timeSet.second() < 10) numStr += '0';
   numStr += (String)timeSet.second();         // 이전 문자에 seconds추가

   GLCD.print(numStr);      	// numStr변수에 담긴 시간 정보(hh:mm:ss) 출력
   
   String date;
   GLCD.CursorTo(2, 6); 			// 시간 값 출력 위치 설정

   if(timeSet.day() < 10) numStr += '0';
   date += (String)timeSet.day();	 	    // 이전 문자에 day추가
   date += "/";
   if(timeSet.month() < 10) numStr += '0';
   date += (String)timeSet.month();         // 이전 문자에 month추가
   date += "/";
   int year = timeSet.year()%100;
   date += (String)year;      		   // 이전 문자에 year추가
    
   GLCD.print(date);     	 // numStr변수에 담긴 시간 정보(mm/dd/yy) 출력
}