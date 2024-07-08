// RGB ����, LED����, ������� ����
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TCS34725.h>
#include <Servo.h>
#include <Wire.h>

#define SERVO_PIN 9            // �������Ϳ� ����� ������ �� ����
#define PIN_LED 5              // LED ���� ��
#define NUMPIXELS 3            // LED ����

Servo servo;                   // �������� ��ü ����
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  // �÷� ���� ��ü ����
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_LED, NEO_GRB + NEO_KHZ800);  // LED ��Ʈ�� ��ü ����

// ������ ���� ���� (R, G, B�� �ּ� �� �ִ� ��)
#define RED_MIN 0 //200
#define RED_MAX 500 //700
#define GREEN_MIN 0
#define GREEN_MAX 500
#define BLUE_MIN 0
#define BLUE_MAX 500

void setup() {
    Serial.begin(9600);  // �ø��� ��� ����

    // �������� �ʱ�ȭ
    servo.attach(SERVO_PIN);
    servo.write(90);  // �������� �⺻ ��ġ 90���� ����

    // LED ��Ʈ�� �ʱ�ȭ
    pixels.begin();
    pixels.setBrightness(50);
    pixels.show(); // Initialize all pixels to 'off'

    // �÷� ���� �ʱ�ȭ
    if (tcs.begin()) {
        Serial.println("TCS34725 found");
    }
    else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1);
    }
}

void loop() {
    uint16_t clear, red, green, blue;  // �÷� ���� ������ ����

    delay(1000);  // 1�ʸ��� �����ϰ� ���
    tcs.getRawData(&red, &green, &blue, &clear);  // ���� ���� �������� ���� �� �޾ƿ���

    // ���� ���� ����� ���
    Serial.print("R: ");
    Serial.print(red);  // �ø��� ����Ϳ� ������ �� ���
    Serial.print(" G: ");
    Serial.print(green);  // �ø��� ����Ϳ� �ʷϻ� �� ���
    Serial.print(" B: ");
    Serial.println(blue);  // �ø��� ����Ϳ� �Ķ��� �� ���

    // ���� �Ǵ� �� LED�� �������� ����
    if (red >= RED_MIN && red <= RED_MAX && green >= GREEN_MIN && green <= GREEN_MAX && blue >= BLUE_MIN && blue <= BLUE_MAX) {
        if (red > green && red > blue && red > 200 && red < 700) {
            Serial.println("������ ����");
            setLEDColor(255, 0, 0);  // ������ LED
            servo.write(90);  // �������͸� 90�� ��ġ�� �̵�
        }
        else if (green > red && green > blue) {
            Serial.println("�ʷϻ� ����");
            setLEDColor(0, 255, 0);  // �ʷϻ� LED
            servo.write(180);  // �������͸� 180�� ��ġ�� �̵�
        }
        else if (blue > red && blue > green) {
            Serial.println("�Ķ��� ����");
            setLEDColor(0, 0, 255);  // �Ķ��� LED
            servo.write(145);  // �������͸� 145�� ��ġ�� �̵�
        }
        else {
            Serial.println("�� �� ���� ����");
            setLEDColor(0, 0, 0);  // LED ����
        }
    }
    else {
        Serial.println("�ƹ��͵� �������� ����");
        setLEDColor(0, 0, 0);  // LED ����
    }
}

void setLEDColor(int r, int g, int b) {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(r, g, b));  // RGB ������ LED ���� ����
    }
    pixels.show();  // LED ���� ����
}
