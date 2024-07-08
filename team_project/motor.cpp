// ���� ���� ����
int motorSpeedPin = 11; // 1�� ���� ȸ�� �ӵ� 
int motorDirectionPin = 13; // ���� ��������
String input = ""; // �Է��� ������ ����

// ���ܼ� ���� ����
int Obj_Sensor = A0;
int val;

void setup() {
    Serial.begin(9600);
    // ��������:
    pinMode(motorDirectionPin, OUTPUT);  // ������������ pinmode_OUTPUT���� ����
    pinMode(motorSpeedPin, OUTPUT); // ���� �ӵ� ���� ���� OUTPUT���� ����

    // ���ܼ� ����
    pinMode(Obj_Sensor, INPUT);
}

void loop() {
    val = analogRead(Obj_Sensor);

    if (Serial.available() > 0) {
        input = Serial.readString(); // �ø��� �Է��� ���ڿ��� ����
        input.trim(); // �ٹٲ� ���� ����

        if (input == "go") {
            motorForward();
            if (val > 300) { // ������ �����Ǿ����� ��� ���߾��ٰ� ����
                // ���� ���� �Լ� --> ���Ŀ� ������ �����ǰ� ����ī�� ��ȣ ������ �ڵ� �߰��ؾ���!!!!
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

void Detect_Forward() { // ���� ���� �Լ� --> ���Ŀ� ������ �����ǰ� ����ī�� ��ȣ ������ �ڵ� �߰��ؾ���!!!!
    Serial.println("������ �����Ǿ����ϴ�.");
    motorStop();
    delay(400);
    motorForward();
}

void Detect_Backward() {// ���� ���� �Լ� --> ���Ŀ� ������ �����ǰ� ����ī�� ��ȣ ������ �ڵ� �߰��ؾ���!!!!
    Serial.println("������ �����Ǿ����ϴ�.");
    motorStop();
    delay(400);
    motorBackward();
}



void motorForward() {
    digitalWrite(motorDirectionPin, HIGH);
    analogWrite(motorSpeedPin, 75); // ���� ���������� ȸ��
    Serial.println("���Ͱ� ���������� �����մϴ�.");
}

void motorBackward() {
    digitalWrite(motorDirectionPin, LOW);
    analogWrite(motorSpeedPin, 75); // ���� ���������� ȸ��
    Serial.println("���Ͱ� ���������� �����մϴ�.");
}

void motorStop() {
    digitalWrite(motorSpeedPin, LOW); // ���� ����
    Serial.println("���Ͱ� ������ϴ�.");
}
