/*
적외선 센서 동작 확인 analog digital 차이 확인
*/
int sensor = A0;  // 센서 핀은 A0번에 연결
int val;

void setup() {
    Serial.begin(9600);
    pinMode(sensor, INPUT);  // 센서 값을 입력으로 설정
    Serial.println("Arduino starts");
}

void loop() {
    val = analogRead(sensor);  // 센서 값 읽어옴
    Serial.print("Sensor value: ");
    Serial.println(val);       // 센서 값을 시리얼 모니터에 출력

    if (val < 300) {           // 적절한 임계값 설정 (예: 300)
        Serial.println("Detected");
    }
    else {
        Serial.println("Not detected");
    }

    delay(300);  // 0.3초 대기 (필요 시 조정)
}
