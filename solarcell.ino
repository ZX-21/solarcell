#include <Servo.h>

// กำหนดพินที่ใช้เชื่อมต่อกับ LDR และเซอร์โว
#define LDR1 A0
#define LDR2 A1
#define LDR3 A2
#define LDR4 A3

int SpointX = 90;  // เริ่มต้นมุม X
int SpointY = 90;  // เริ่มต้นมุม Y
int threshold = 500;  // ค่ากลางที่ใช้ในการตัดสินใจ

Servo servoX;  // เซอร์โวแกน X
Servo servoY;  // เซอร์โวแกน Y

void setup() {
  servoX.attach(9);  // เชื่อมต่อเซอร์โว X กับพิน 9
  servoY.attach(10); // เชื่อมต่อเซอร์โว Y กับพิน 10
  servoX.write(SpointX); // กำหนดมุมเริ่มต้นของเซอร์โว X
  servoY.write(SpointY); // กำหนดมุมเริ่มต้นของเซอร์โว Y
  delay(1000);
  Serial.begin(9600); // เริ่มต้นการสื่อสารกับ Serial Monitor
}

void loop() {
  // อ่านค่าจาก LDR
  int ldr1 = analogRead(LDR1);
  int ldr2 = analogRead(LDR2);
  int ldr3 = analogRead(LDR3);
  int ldr4 = analogRead(LDR4);

  // แสดงค่าที่อ่านจากเซ็นเซอร์ใน Serial Monitor
  Serial.print("LDR1: ");
  Serial.print(ldr1);
  Serial.print(" LDR2: ");
  Serial.print(ldr2);
  Serial.print(" LDR3: ");
  Serial.print(ldr3);
  Serial.print(" LDR4: ");
  Serial.println(ldr4);

  // แก้ไขมุมแกน X (Servo X)
  if (ldr1 > threshold && ldr3 > threshold) {
    // หมุนเซอร์โวไปทางซ้าย
    SpointX = SpointX - 5;
  } else if (ldr2 > threshold && ldr4 > threshold) {
    // หมุนเซอร์โวไปทางขวา
    SpointX = SpointX + 5;
  }

  // แก้ไขมุมแกน Y (Servo Y)
  if (ldr1 > threshold && ldr2 > threshold) {
    // หมุนเซอร์โวขึ้น
    SpointY = SpointY - 5;
  } else if (ldr3 > threshold && ldr4 > threshold) {
    // หมุนเซอร์โวลง
    SpointY = SpointY + 5;
  }

  // จำกัดมุมให้เซอร์โวไม่เกิน 0-180 องศา
  SpointX = constrain(SpointX, 0, 180);
  SpointY = constrain(SpointY, 0, 180);

  // กำหนดมุมเซอร์โว
  servoX.write(SpointX); delay(100);

  delay(100);
  servoY.write(SpointY);delay(100);

  delay(100); // หน่วงเวลาเพื่อให้การเคลื่อนที่ราบรื่น
}
