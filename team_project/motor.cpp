// 모터 제어 변수
int motorSpeedPin = 11; // 1번 모터 회전 속도 
int motorDirectionPin = 13; // 모터 방향제어
String input = ""; // 입력을 저장할 변수

// 적외선 센서 변수
int Obj_Sensor = A0;
int val;

void setup() {
    Serial.begin(9600);
    // 모터제어:
    pinMode(motorDirectionPin, OUTPUT);  // 방향제어핀을 pinmode_OUTPUT으로 지정
    pinMode(motorSpeedPin, OUTPUT); // 모터 속도 제어 핀을 OUTPUT으로 설정

    // 적외선 센서
    pinMode(Obj_Sensor, INPUT);
}

void loop() {
    val = analogRead(Obj_Sensor);

    if (Serial.available() > 0) {
        input = Serial.readString(); // 시리얼 입력을 문자열로 읽음
        input.trim(); // 줄바꿈 문자 제거

        if (input == "go") {
            motorForward();
            if (val > 300) { // 물건이 감지되었을때 잠시 멈추었다가 실행
                // 물건 감지 함수 --> 차후에 물건이 감지되고 위즈카에 신호 보내는 코드 추가해야함!!!!
                Detect_Forward();
            }
        }
        else if (input == "back") {
            motorBackward();
            if (val > 300) {
                Detect_Backward();
            }
        }
        else if (input == "stop") {
            motorStop();
        }
    }
}

void Detect_Forward() { // 물건 감지 함수 --> 차후에 물건이 감지되고 위즈카에 신호 보내는 코드 추가해야함!!!!
    Serial.println("물건이 감지되었습니다.");
    motorStop();
    delay(400);
    motorForward();
}

void Detect_Backward() {// 물건 감지 함수 --> 차후에 물건이 감지되고 위즈카에 신호 보내는 코드 추가해야함!!!!
    Serial.println("물건이 감지되었습니다.");
    motorStop();
    delay(400);
    motorBackward();
}



void motorForward() {
    digitalWrite(motorDirectionPin, HIGH);
    analogWrite(motorSpeedPin, 75); // 모터 정방향으로 회전
    Serial.println("모터가 정방향으로 동작합니다.");
}

void motorBackward() {
    digitalWrite(motorDirectionPin, LOW);
    analogWrite(motorSpeedPin, 75); // 모터 역방향으로 회전
    Serial.println("모터가 역방향으로 동작합니다.");
}

void motorStop() {
    digitalWrite(motorSpeedPin, LOW); // 모터 멈춤
    Serial.println("모터가 멈췄습니다.");
}
