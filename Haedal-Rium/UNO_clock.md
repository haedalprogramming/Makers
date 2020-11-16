# 아두이노 UNO로 시계 만들어보기

- 아두이노 우노
- LCD(16x2)+I2C 모듈: 80mmx36mmx18mm
- RTC모듈(DS1302)
- 전원(9V)
- 9V 전용 배럴잭 어댑터
- 케이블(암-수)


## 목적

- 아두이노를 이용하여 현재시각을 알려주는 시계를 만들어보고 그것을 대구근대역사관 건물의 특징을 살린 케이스와 결합하는 것.



## 참여대상

- 초-중등 학생 35명 내외   

### ※ 주요 교육대상이 초등이기 때문에 최대한 상세하고 알기 쉽게!!



## 준비물

- 아두이노 UNO  - 1개
- LCD with I2C 모듈 - 1개
- RTC모듈(DS1302) - 1개
- 전원(9V) - 1개
- 9V 전용 배럴잭 어댑터 - 1개
- 케이블(암-수) - 15개


### 아두이노 UNO

전원이랑 USB 연결포트를 왼쪽으로 두었을 때 위쪽에는 0번부터 13번까지 적혀있는 핀 및 GND, AREF 핀이 있고, 아래쪽에는 A0부터 A5까지 적힌 핀과 Vin, GND, 5V, 3.3V 등의 핀들이 있습니다. 


### LCD with I2C

16x2  LCD에 I2C모듈이 결합된 모듈입니다. 

우리는 이 LCD화면에 원하는 문구나 시간을 표시하게 됩니다. 


### RTC 모듈(DS1302)

시간에 대한 처리를 하는 시계 모듈입니다.



![clock_circuit](./img/uno_clock_bb.png)



# 코드 작성 가이드

1. 아두이노 IDE 설치 및 사용법 소개
2. 각 코드구간별로 소개
3. 시간 설정 방법 상세설명
4. (추가)LCD화면에 원하는 문구 띄우는법 소개



## 아두이노 통합개발환경(IDE) 설치하기

우선, 아두이노에 코드를 업로드 하기 위해서는 아두이노 통합개발환경(IDE)을 설치하여야 합니다. 다음 링크로 들어가서 본인의 PC 운영체제에 맞는 설치파일을 다운받고 설치를 진행합니다.


[통합개발환경(IDE) 설치파일 다운로드 링크](https://www.arduino.cc/en/software)



## 아두이노와 PC 연결하기

설치가 완료되었다면 아두이노를 PC에 연결합시다. 불이 깜빡거리죠? 이렇게 되면 정상적으로 연결된 겁니다. 

그 다음으로는 통합개발환경을 켜서 '툴' 탭에 들어가서 '보드' 부분과 '포트' 부분을 설정해줍니다. 우리는 아두이노 UNO를 사용하니 Arduino UNO라고 적힌 보드를 선택하면 되겠죠? 그 다음엔 포트를 연결해주어야 하는데, 'COM숫자(Arduino UNO)' 형식으로 나타날 겁니다. 이것을 선택해 주세요.    
여러분이 앞으로 아두이노를 연결할 때 줄곧 하나의 USB 포트에만 연결을 하면 상관없겠지만 다른 USB 포트에 연결하거나 하는 경우 포트설정을 다시 해주어야 해요. 아두이노를 연결하더라도 포트가 연결되어 있지 않으면 코드를 업로드할 수가 없습니다. 항상 주의해주세요!


### ※ 장치 연결 확인하기!   
→ 제어판-장치관리자 로 들어가서 포트 부분을 확인합니다.


## 코드 업로드하기   
다음 주어진 코드를 그대로 IDE에 입력합니다. (깃헙링크로 제공할지?)


**시간설정을 할 때 주의할 점.**

주석처리된 부분(/* */로 감싸진 부분)의 주석을 해제하고 먼저 날짜와 시간을 업로드한 후, 다시 해제했던 구간을 주석처리하여 한번 더 업로드합니다. 

→ 전원을 분리했다가 다시 연결하여도 시간이 계속 그대로 흐르도록 하기 위함.


※ 만약, 날짜와 시간 말고 추가적으로 다른 메시지를 띄우고 싶다면 직접 설정할 수 있음!


## 코드   

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



