/*
���ܼ� ���� ���� Ȯ�� analog digital ���� Ȯ��
*/
int sensor = A0;  // ���� ���� A0���� ����
int val;

void setup() {
    Serial.begin(9600);
    pinMode(sensor, INPUT);  // ���� ���� �Է����� ����
    Serial.println("Arduino starts");
}

void loop() {
    val = analogRead(sensor);  // ���� �� �о��
    Serial.print("Sensor value: ");
    Serial.println(val);       // ���� ���� �ø��� ����Ϳ� ���

    if (val < 300) {           // ������ �Ӱ谪 ���� (��: 300)
        Serial.println("Detected");
    }
    else {
        Serial.println("Not detected");
    }

    delay(300);  // 0.3�� ��� (�ʿ� �� ����)
}
