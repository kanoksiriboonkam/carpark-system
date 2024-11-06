#include <ESP32Servo.h>  // ไลบรารีสำหรับควบคุมเซอร์โวมอเตอร์บน ESP32

// กำหนดขา GPIO สำหรับเซ็นเซอร์ IR Line Tracking Module บนบอร์ด ESP32
const int irSensor1 = 5;    // เซ็นเซอร์ IR ตัวที่ 1 ที่ขา GPIO 5
const int irSensor2 = 18;   // เซ็นเซอร์ IR ตัวที่ 2 ที่ขา GPIO 18
const int irSensor3 = 22;   // เซ็นเซอร์ IR ตัวที่ 3 ที่ขา GPIO 22
const int servoPin = 21;    // ขา PWM สำหรับควบคุมเซอร์โวมอเตอร์

Servo myServo;  // สร้างอ็อบเจ็กต์ Servo
int objectCount = 0;        // ตัวแปรนับจำนวนวัตถุที่เซ็นเซอร์ IR ที่ขา 5 ตรวจจับได้
unsigned long lastDetectionTime = 0;  // เก็บเวลาที่ตรวจจับได้ครั้งล่าสุด
bool objectDetected = false;  // สถานะการตรวจจับวัตถุ

void setup() {
  Serial.begin(115200);  // เริ่มต้นการสื่อสารแบบ Serial ที่ความเร็ว 115200
  
  // ตั้งค่าขา IR เป็นขาอินพุต
  pinMode(irSensor1, INPUT);
  pinMode(irSensor2, INPUT);
  pinMode(irSensor3, INPUT);
  
  // เริ่มต้นการควบคุมเซอร์โวมอเตอร์ที่ขา PWM ที่กำหนดไว้
  myServo.attach(servoPin);
  myServo.write(0);  // ตั้งเซอร์โวให้เริ่มต้นที่ 0 องศา
}

void loop() {
  // อ่านค่าจาก D0 ของเซ็นเซอร์ IR แต่ละตัว
  int value1 = digitalRead(irSensor1);
  int value2 = digitalRead(irSensor2);
  int value3 = digitalRead(irSensor3);

  // แสดงผลค่าจากเซ็นเซอร์แต่ละตัว
  Serial.print("IR Sensor 1 (GPIO 5): ");
  Serial.print(value1);
  Serial.print("\t IR Sensor 2 (GPIO 18): ");
  Serial.print(value2);
  Serial.print("\t IR Sensor 3 (GPIO 22): ");
  Serial.println(value3);

  // ตรวจสอบสถานะของเซ็นเซอร์ IR ที่ขา 5
  if (value1 == 0) {  // ตรวจจับวัตถุได้
    if (!objectDetected) {
      objectCount++;  // เพิ่มจำนวนวัตถุที่ตรวจจับได้
      Serial.print("Object Count: ");
      Serial.println(objectCount);
      objectDetected = true;  // เปลี่ยนสถานะเป็นตรวจจับวัตถุ
    }

    // ตั้งเซอร์โวมอเตอร์ไปที่ 90 องศา
    myServo.write(90);
    lastDetectionTime = millis();  // บันทึกเวลาที่ตรวจจับล่าสุด
  } else {  // ตรวจจับวัตถุไม่ได้
    objectDetected = false;
    if (millis() - lastDetectionTime >= 3000) {  // ตรวจสอบว่าไม่มีวัตถุเป็นเวลา 3 วินาที
      myServo.write(0);  // หมุนกลับไปที่ 0 องศา
    }
  }

  delay(500);  // หน่วงเวลา 500 มิลลิวินาทีระหว่างการอ่าน
}
