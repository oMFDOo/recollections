/****************************************************************
 * File Name:   Final.ino
 *
 * Description: 마지막 공학 설계 RC제어 코드
 * Created: 6/18/2020 11:31:41 AM
 * Author:  Jeong MinGyu
 *
 * Extern File
 * Name                             Description
 * ================================ ============================
 * boarddefs.h                      IR 센서 사용
 * ir_Lego_PF_BitStreamEncoder.h    IR 센서 사용
 * IRremoteInt.h                    IR 센서 사용
 * IRremote.h                       IR 센서 사용
 * Servo.h                          서보 모터(바퀴) 구동
 *
 * Extern Variables
 * Name         Type        Description
 * ============ =========== ====================================
 * None
 *
 * Global Variables
 * Name         Type        Description
 * ============ =========== ====================================
 * Dir          enum        주행 방향
 * leftStandard int         좌측 바퀴 정지 위치
 * rightStandard int        우측 바퀴 정지 위치
 * mode         int         주행 모드(1-조작주행 0-자율주행)
 ****************************************************************/

#include <ir_Lego_PF_BitStreamEncoder.h>        
#include <IRremoteInt.h>                        
#include <IRremote.h>                           
#include <boarddefs.h>                          

#include <Servo.h>                              

// 모터구동 핀
#define MOTORL_PIN 5
#define MOTORR_PIN 9

// 초음파 센서
#define TRIG_PIN 3
#define ECHO_PIN 4

// QTI센서
#define qtiL 11
#define qtiR 12

// 리모컨 제어
#define FRONT 0xFF02FD
#define BACK 0xFF9867
#define RIGHT 0xFF906F
#define LEFT 0xFFE01F
#define STOP 0xFFA857
#define MODE 0xFF22DD

// 서보 모터
Servo LServo;
Servo RServo;

// IR센서
IRrecv irrecv(2);
decode_results results;

// 방향
enum Dir
{
    forward = 0,
    backward = 1,
    left = 2,
    right = 3
};

int leftStandard = 90;      // 좌측 바퀴 정지 값
int rightStandard = 90;     // 우측 바퀴 정지 값
int mode = 1;               // 조작 모드 (1-조작주행 0-자율주행)

/****************************************************************
* Function Name: setup
* Description:     
* the setup function runs once when you press reset or power the board
*
* @return: void
* @param: void
* Name         Type        Description
* ============ =========== ====================================
*
* Author:       Jeong MinGyu
* Creat Date:   2020.06.18.
* Last Edit:    2020.06.18.
*
* Global Variables
* Name         Type        Description
* ============ =========== ====================================
* None
*
* Algorithm :
***************************************************************/
void setup() {
    Serial.begin(9600);

    // QTI 센서
    pinMode(qtiL, INPUT);
    pinMode(qtiR, INPUT);

    // IR 센서
    Serial.println("Enabling IRin");
    irrecv.enableIRIn();
    Serial.println("Enabled IRin");

    // 초음파 센서
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // 모터 설정
    LServo.attach(MOTORL_PIN);
    RServo.attach(MOTORR_PIN);
}

/****************************************************************
* Function Name: SonarDistance
* Description:
* 벽과의 거리를 초음파 센서를 통해 측정한다.
*
* @return:  int (벽과의 거리)
* @param:   void
* Name         Type        Description
* ============ =========== ====================================
*
* Author:       Jeong MinGyu
* Creat Date:   2020.06.18.
* Last Edit:    2020.06.18.
*
* Global Variables
* Name         Type        Description
* ============ =========== ====================================
* None
*
* Algorithm :
***************************************************************/
int SonarDistance() {
    int sonarPwn;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    sonarPwn = pulseIn(ECHO_PIN, 1, 18500L);

    return sonarPwn / 60;
}

/****************************************************************
* Function Name: Move
* Description:
* 자체가 이동하도록 바퀴를 동작합니다.
*
* @return:  void
* @param:   int
* Name         Type        Description
* ============ =========== ====================================
* speed        int          값이 클수록 이동(전환) 속도 빠름
* mode         Dir          이동 방향을 지정합니다
*
* Author:       Jeong MinGyu
* Creat Date:   2020.06.18.
* Last Edit:    2020.06.18.
*
* Global Variables
* Name         Type        Description
* ============ =========== ====================================
* leftStandard  int         좌측 바퀴가 멈추는 값
* rightStandard int         우측 바퀴가 정지하는 값
*
* Algorithm :
* num   dir 좌 우  %3   %2
* 0     전 + -   0    0
* 1     후 - +   1    1
* 2     좌 - -   2    0
* 3     우 + +   0    1
***************************************************************/
void Move(int speed, Dir mode) {
    int LSpeed = mode % 3 ? -speed : speed;
    int RSpeed = mode % 2 ? speed : -speed;

    LServo.write(leftStandard - speed);     // +is Front -is Back
    RServo.write(rightStandard - speed);    // -is Front  +is Back
}

/****************************************************************
* Function Name: loop
* Description:
* the loop function runs over and over again until power down or reset
*
* @return:  void
* @param:   void
* Name         Type        Description
* ============ =========== ====================================
*
* Author:       Jeong MinGyu
* Creat Date:   2020.06.18.
* Last Edit:    2020.06.18.
*
* Global Variables
* Name         Type        Description
* ============ =========== ====================================
* mode         int         주행 모드(1-조작주행 0-자율주행): 1이 기본값
*
* Algorithm :
***************************************************************/
void loop() {
    // 조작시 기본 속도
    int speed = 15;

    // 블루투스 조작
    if (Serial.available()) {
        char value = Serial.read();
        Serial.println(value);

        switch (value)
        {
        //회전시 조작이 편하도록 속도를 절반으로
        case '1':
            Move(0.5 * speed, left); break;
        case '2':
            Move(speed, forward); break;
        case '3':
            Move(0.5 * speed, right); break;
        case '4':
            Move(speed, backward); break;
        case '5':
            Move(0, forward); break;
        
        // 모드 변경 토글
        case '6':
            mode = mode ? 0 : 1; break;
        default:
            break;
        }
    }
    // IR 센서 제어
    if (irrecv.decode(&results)) {
        int count = results.rawlen;

        switch (results.value)
        {
        case FRONT: Move(speed, forward); delay(30); break;
        case BACK: Move(speed, backward); delay(30); break;
        case RIGHT: Move(0.5 * speed, right); delay(30); break;
        case LEFT: Move(0.5 * speed, left); delay(30); break; 
        case STOP: Move(0, forward); delay(30); break;
        // 모드 변경 토글
        case MODE: mode = mode ? 0 : 1; break;
                
        default:
            break;
        }

        irrecv.resume();
    }

    // QTI센서를 이용한 자율 주행
    if (mode==0) {
        int LeftQti = digitalRead(qtiL);    // black 1 else 0
        int RightQti = digitalRead(qtiR);
        
        Serial.println(LeftQti);
        Serial.println(RightQti);

        // 벽 피하는 기능 추가시 사용 속도를 위해 비활성화
        // int distance = SonarDistance();
        // Serial.print("distance : ");
        // Serial.println(distance);

        // 좌측이 검은색이면 좌측 방향으로 이동
        if (LeftQti) {
            Move(speed-5, left);
            delay(3);
        }
        // 우측이 검은색이면 우측방향으로 이동
        else if (RightQti) {
            Move(speed-5, right);
            delay(3);
        }
        // 이외는 전진 주행
        else
        {
            Move(speed, forward);
        }
    }
}
