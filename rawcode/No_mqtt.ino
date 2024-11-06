#include <ESP32Servo.h>  // ไลบรารีสำหรับควบคุมเซอร์โวมอเตอร์บน ESP32

// กำหนดขา GPIO สำหรับเซ็นเซอร์ IR Line Tracking Module บนบอร์ด ESP32
const int irSensor1 = 5;    // เซ็นเซอร์ IR ตัวที่ 1 ที่ขา GPIO 5
const int irSensor2 = 0;    // เซ็นเซอร์ IR ตัวที่ 2 ที่ขา GPIO 18
const int irSensor3 = 22;   // เซ็นเซอร์ IR ตัวที่ 3 ที่ขา GPIO 22
const int servoPin = 21;    // ขา PWM สำหรับควบคุมเซอร์โวมอเตอร์

Servo myServo;  // สร้างอ็อบเจ็กต์ Servo
int objectCount = 0;  // ตัวแปรนับจำนวนวัตถุที่เซ็นเซอร์ IR ที่ขา 5 ตรวจจับได้

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

  // เช็คเงื่อนไขการทำงานของเซอร์โวมอเตอร์
  if (value1 == 0) {
    // ถ้าเซ็นเซอร์ IR ที่ขา 5 ตรวจจับค่าเป็น 0
    objectCount++;  // เพิ่มจำนวนครั้งที่ตรวจจับวัตถุ
    Serial.print("Object Count: ");
    Serial.println(objectCount);

    // หมุนเซอร์โวมอเตอร์ไปที่ 90 องศา ค้างไว้ 3 วินาที จากนั้นกลับมาที่ 0 องศา
    myServo.write(90);
    delay(3000);  // ค้างไว้ 3 วินาที
    myServo.write(0);  // หมุนกลับไปที่ 0 องศา
  } else {
    // ถ้าเซ็นเซอร์ IR ที่ขา 5 ไม่ตรวจจับวัตถุ ให้เซอร์โวมอเตอร์อยู่ที่ตำแหน่ง 0 องศา
    myServo.write(0);
  }

  delay(500);  // หน่วงเวลา 500 มิลลิวินาทีระหว่างการอ่าน
}
