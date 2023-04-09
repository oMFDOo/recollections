int digit_select_pin[] = {66, 67, 68, 69}; // 자릿수 선택 핀
// 7세그먼트 모듈 연결 핀(a, b, c, d, e, f, g, dp)
int segment_pin[] = {58, 59, 60, 61, 62, 63, 64, 65}; 
volatile int minutes = 0, seconds =0; // 시간 초기화
long previous_time; // 이전 시간
byte patterns[] { // 수 표현을 위한 패턴(a, b, c, d, e, f, g, dp)
    0xFC, 0x60, 0xDA, 0xF2, 0x66,
    0xB6, 0xBE, 0xE4, 0xFE, 0xE6 
};

void setup() {
    Serial.begin(9600);
    previous_time = millis();
    
    // 외부 인터럽트 0번, FALLING MODE 설정
    pinMode(19, INPUT_PULLUP);
    attachInterrupt(4, interrupt, CHANGE);
    
    // 자릿수 선택 핀을 출력으로 설정
    for (int i = 0; i < 4; i++)
        pinMode(digit_select_pin[i], OUTPUT);
        
    // 세그먼트 제어 핀을 출력으로 설정
    for (int i = 0; i < 8; i++)
        pinMode(segment_pin[i], OUTPUT);
}

void interrupt() { // 외부 인터럽트 분기 함수
  minutes = 0;
  seconds = 0;
}

void show_digit(int pos, int number){ // 위치, 출력할 숫자
    for(int i = 0; i < 4; i++) {
        if(i + 1 == pos) // 해당 자릿수의 선택 핀만 LOW로 설정
            digitalWrite(digit_select_pin[i], LOW);

        else // 나머지 자리는 HIGH로 설정
            digitalWrite(digit_select_pin[i], HIGH);
    }

    for(int i = 0; i < 8; i++){
      boolean on_off;
      
      if(pos == 2 && i == 7)
          on_off = true;
          
      else
          on_off = bitRead(patterns[number], 7 -i);  
        
      digitalWrite(segment_pin[i], on_off);
    }
}

void show_4_digit(int _number) { // 해당 자리에 숫자 하나를 표시하는 함수
    int number = _number;
    number = number % 10000;
    
    int thousands = number / 1000;
    number = number % 1000;
    
    int hundreads = number / 100;
    number = number % 100;
    
    int tens = number/10;
    
    int ones = number % 10;

    show_digit(1, thousands);
    delayMicroseconds(1000);

    show_digit(2, hundreads);
    delayMicroseconds(1000);
    
     show_digit(3, tens);
    delayMicroseconds(1000);

    show_digit(4, ones);
    delayMicroseconds(1000);
}

void loop() {
    long time_current = millis();
    
    if(time_current - previous_time >= 1000) { // 1초 경과 시(초 증가)
        previous_time  = time_current;
        seconds++;
        
        if(seconds == 60) { // 분 증가
            seconds = 0;
            minutes++;
        }
        if(minutes == 60) // 분 초기화
            minutes = 0;
    }
    show_4_digit(minutes * 100 + seconds); // 시간 표시를 위해 4자리 수로 변환
}