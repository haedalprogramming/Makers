# 아두이노 UNO로 시계 만들어보기


## 코드   
```
//DS1302 라이브러리 사용
#include <DS1302.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>

#define sclk 9
#define dat 8
#define rst 7
#define LCDpower 5

LiquidCrystal_I2C lcd(0x27, 16, 2);//LiquidCrystal_I2C 오브젝트 생성. 0x27은 주소
DS1302 rtc(rst, dat, sclk);//DS1302 오브젝트 생성


void setup() {
  digitalWrite(LCDpower, HIGH);
  pinMode(LCDpower, OUTPUT);
  
  lcd.init(); //lcd 초기화
  lcd.backlight();
  rtc.writeProtect(true);//쓰기금지모드 실행
  rtc.halt(false);//rtc timer 실행
  
/*
//아래 시간 설정은 처음 업로드 한 후 다시 주석처리하여 업로드 해야 시간이 리셋되지 않음
  rtc.writeProtect(false);// rtc데이터를 수정하기 위해 writeProtect를 해제
  rtc.halt(true);// 날짜와 시간을 수정하기 위해 rtc Timer을 정지시킴
  Time tm=rtc.time();
  tm.yr=2020;//연도
  tm.mon=10;//월
  tm.date=19;//일
  tm.day=2;//요일(1~7 -> 1:일, 2:월,...,7:토)
  tm.hr=14;//시간(24시 기준)
  tm.min=45;//분
  tm.sec=0;//초
 
  rtc.time(tm);//수정한 값을 rtc에 기록
  rtc.halt(false);//Timer 다시 가동(정지 해제)
  rtc.writeProtect(true);//쓰기금지모드 실행
//여기까지 시간 설정
  */
}

void loop() {
 Time tm=rtc.time();//rtc의 내부 시간을 읽으면서 Time 오브젝트 생성

 //날짜(연, 월, 일, 요일) 지정
 String str0=" "+String(tm.yr)+"-"+String(tm.mon)+"-"+String(tm.date)+"("+getWeek(tm.day)+")";
 lcd.setCursor(0,0);
 lcd.print(str0);//lcd화면에 날짜 출력

 //시간(시, 분, 초) 지정
 lcd.setCursor(3,1);
 String str1;
 if(tm.min<10){//분이나 초가 10 미만일 때도 두자리로 표현(00, 01 처럼)
  if(tm.sec<10){
    str1=" "+String(tm.hr)+":0"+String(tm.min)+":0"+String(tm.sec);
  }
  else {
    str1=" "+String(tm.hr)+":0"+String(tm.min)+":"+String(tm.sec);
  }
 }
 else{
  if(tm.sec<10){
    str1=" "+String(tm.hr)+":"+String(tm.min)+":0"+String(tm.sec);
  }
  else{
    str1=" "+String(tm.hr)+":"+String(tm.min)+":"+String(tm.sec);
  }
 }
 lcd.print(str1);//lcd화면에 시간 출력
 
 
 delay(1000);//1초에 한번씩 갱신하기 위해 딜레이 1초
 
 
}

//요일에 대한 문자열 생성
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
```


