#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address, 16x2 LCD
Servo myservo; // 서보 모터 객체 생성

int servoPin = 12; // 서보 모터가 연결된 핀 번호
int angle = 0; // 현재 서보 모터 각도
int previousAngle = -1; // 이전 서보 모터 각도
int buttonPin = 2; // 버튼 스위치 모듈 KY-004가 연결된 핀 번호
int buttonState = LOW; // 버튼 상태를 저장하는 변수, 초기값은 LOW
int lastButtonState = LOW; // 이전 버튼 상태를 저장하는 변수, 초기값은 LOW
unsigned long lastDebounceTime = 0; // 버튼 입력의 바운스(튕김) 효과를 제어하기 위한 변수
unsigned long debounceDelay = 50; // 버튼 입력의 바운스(튕김) 효과를 방지하기 위한 딜레이
bool servoDirection = false; // 서보 모터의 회전 방향을 나타내는 변수, 초기값은 false

void setup() {
  lcd.init(); // LCD 초기화
  lcd.backlight(); // LCD 배경 조명 활성화
  lcd.print("Servo Angle:"); // 초기 메시지 출력
  Serial.begin(9600); // 시리얼 통신 초기화
  myservo.attach(servoPin); // 서보 모터 핀 초기화
  pinMode(buttonPin, INPUT); // 버튼 핀을 입력 모드로 설정
}

void loop() {
  int reading = digitalRead(buttonPin); // 현재 버튼 상태 읽기

  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // 버튼 상태가 변했을 때의 타임스탬프 저장
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // 버튼 입력의 바운스(튕김) 효과가 지났을 때
    if (reading != buttonState) {
      buttonState = reading; // 버튼 상태 업데이트
      if (buttonState == HIGH) {
        if (servoDirection) {
          angle = 0; // 버튼이 눌리면 각도를 0도로 변경
        } else {
          angle = 180; // 버튼이 눌리면 각도를 180도로 변경
        }
        servoDirection = !servoDirection; // 방향을 토글
        myservo.write(angle); // 서보 모터 각도 변경
        updateLCD(angle); // LCD 디스플레이 업데이트
      }
    }
  }

  lastButtonState = reading;
}

void updateLCD(int angle) {
  lcd.clear(); // 디스플레이 내용 지우기
  lcd.setCursor(0, 0); // 첫 번째 줄, 첫 번째 열로 커서 이동
  lcd.print("Post-it Size:"); // 메시지 출력
  lcd.setCursor(0, 1); // 두 번째 줄, 첫 번째 열로 커서 이동

  if (angle == 0) {
    lcd.print("70 X 70");
  } else if (angle == 180) {
    lcd.print("70 X 53");
  }
}
