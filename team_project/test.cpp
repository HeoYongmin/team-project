// RGB 센서, LED센서, 서브모터 구동
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TCS34725.h>
#include <Servo.h>
#include <Wire.h>

#define SERVO_PIN 9            // 서보모터와 연결된 보드의 핀 정의
#define PIN_LED 5              // LED 연결 핀
#define NUMPIXELS 3            // LED 개수

Servo servo;                   // 서보모터 객체 생성
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  // 컬러 센서 객체 생성
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_LED, NEO_GRB + NEO_KHZ800);  // LED 스트립 객체 생성

// 감지할 색상 범위 (R, G, B의 최소 및 최대 값)
#define RED_MIN 0 //200
#define RED_MAX 500 //700
#define GREEN_MIN 0
#define GREEN_MAX 500
#define BLUE_MIN 0
#define BLUE_MAX 500

void setup() {
    Serial.begin(9600);  // 시리얼 통신 시작

    // 서보모터 초기화
    servo.attach(SERVO_PIN);
    servo.write(90);  // 서보모터 기본 위치 90도로 설정

    // LED 스트립 초기화
    pixels.begin();
    pixels.setBrightness(50);
    pixels.show(); // Initialize all pixels to 'off'

    // 컬러 센서 초기화
    if (tcs.begin()) {
        Serial.println("TCS34725 found");
    }
    else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1);
    }
}

void loop() {
    uint16_t clear, red, green, blue;  // 컬러 센서 데이터 변수

    delay(1000);  // 1초마다 측정하고 출력
    tcs.getRawData(&red, &green, &blue, &clear);  // 색상 감지 센서에서 측정 값 받아오기

    // 색상 감지 결과를 출력
    Serial.print("R: ");
    Serial.print(red);  // 시리얼 모니터에 빨간색 값 출력
    Serial.print(" G: ");
    Serial.print(green);  // 시리얼 모니터에 초록색 값 출력
    Serial.print(" B: ");
    Serial.println(blue);  // 시리얼 모니터에 파란색 값 출력

    // 색상 판단 및 LED와 서보모터 제어
    if (red >= RED_MIN && red <= RED_MAX && green >= GREEN_MIN && green <= GREEN_MAX && blue >= BLUE_MIN && blue <= BLUE_MAX) {
        if (red > green && red > blue && red > 200 && red < 700) {
            Serial.println("빨간색 감지");
            setLEDColor(255, 0, 0);  // 빨간색 LED
            servo.write(90);  // 서보모터를 90도 위치로 이동
        }
        else if (green > red && green > blue) {
            Serial.println("초록색 감지");
            setLEDColor(0, 255, 0);  // 초록색 LED
            servo.write(180);  // 서보모터를 180도 위치로 이동
        }
        else if (blue > red && blue > green) {
            Serial.println("파란색 감지");
            setLEDColor(0, 0, 255);  // 파란색 LED
            servo.write(145);  // 서보모터를 145도 위치로 이동
        }
        else {
            Serial.println("알 수 없는 색상");
            setLEDColor(0, 0, 0);  // LED 끄기
        }
    }
    else {
        Serial.println("아무것도 감지되지 않음");
        setLEDColor(0, 0, 0);  // LED 끄기
    }
}

void setLEDColor(int r, int g, int b) {
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(r, g, b));  // RGB 값으로 LED 색상 설정
    }
    pixels.show();  // LED 색상 변경
}
