
#include <DS1302.h> //RTC모듈에 필요한 라이브러리
#include <LiquidCrystal_I2C.h> //LCD with I2C에 필요한 라이브러리

#define sclk 9 //RTC모듈의 SCLK 를 9번에 연결한다.
#define dat 8 //RTC모듈의 DAT 를 8번에 연결한다. 
#define rst 7 //RTC모듈의 RST 를 7번에 연결한다
#define power 5 //5번 핀을 5V 출력으로 사용할 것. 앞으로는 5 대신 power라고 사용할 것.

LiquidCrystal_I2C lcd(0x27, 16, 2); //LiquidCrystal_I2C 오브젝트 생성. 0x27은 주소
DS1302 rtc(rst, dat, sclk); //DS1302 오브젝트 생성


void setup() {
  digitalWrite(power, HIGH); //5번핀에 5V전압을 ON
  pinMode(power, OUTPUT); //핀을 출력모드로 설정한다. 
  
  lcd.init(); //LCD 초기화
  lcd.backlight(); //LCD 백라이트 켜기
  rtc.writeProtect(true); //쓰기금지모드 실행
  rtc.halt(false); //RTC timer 실행
  
/*
//날짜 및 시간 설정
  rtc.writeProtect(false); // rtc데이터를 수정하기 위해 쓰기금지모드를 해제
  rtc.halt(true); // 날짜와 시간을 수정하기 위해 RTC Timer을 정지시킴
  Time tm = rtc.time(); //RTC 내부 시간을 읽으면서 Time 오브젝트 생성
  tm.yr = 2020; //연도
  tm.mon = 10; //월
  tm.date = 19; //일
  tm.day = 2; //요일(1~7 -> 1:일, 2:월, 3: 화, 4: 수, 5: 목, 6: 금, 7:토)
  tm.hr = 14; //시간(24시 기준. 예)오후2시는 14로 표현)
  tm.min = 45; //분
  tm.sec = 0; //초
 
  rtc.time(tm); //수정한 값을 RTC에 기록
  rtc.halt(false); //Timer 다시 가동(정지 해제)
  rtc.writeProtect(true); //쓰기금지모드 실행
//여기까지 날짜 및 시간 설정부분
  */

}

void loop() {
 Time tm=rtc.time(); //rtc의 내부 시간을 읽으면서 Time 오브젝트 생성

 //날짜(연, 월, 일, 요일) 지정
 String str0 = " " + String(tm.yr) + "-" + String(tm.mon) + "-" + String(tm.date) + "(" + getWeek(tm.day) + ")";
 lcd.setCursor(0,0);
 lcd.print(str0); //LCD화면에 날짜 출력

 //시간(시, 분, 초) 지정
 lcd.setCursor(3,1);
 String str1;
 if(tm.min<10){ //분이나 초가 10 미만일 때도 두자리로 표현(00, 01 처럼)
  if(tm.sec<10){
    str1 = " " + String(tm.hr) + ":0" + String(tm.min) + ":0" + String(tm.sec);
  }
  else {
    str1 = " " + String(tm.hr) + ":0" + String(tm.min) + ":" + String(tm.sec);
  }
 }
 else{
  if(tm.sec<10){
    str1 = " " + String(tm.hr) + ":" + String(tm.min) + ":0" + String(tm.sec);
  }
  else{
    str1 = " " + String(tm.hr) + ":" + String(tm.min) + ":" + String(tm.sec);
  }
 }
 lcd.print(str1); //lcd화면에 시간 출력
 
 
 delay(1000); //1초에 한번씩 갱신하기 위해 딜레이 1초
 
 
}

//요일에 관한 문자열 생성
String getWeek(byte wk){
  switch(wk){
    case 1: return "Sun";
    case 2: return "Mon";
    case 3: return "Tue";
    case 4: return "Wed";
    case 5: return "Thu";
    case 6: return "Fri";
    case 7: return "Sat";
    default: return "Err";
  }
}