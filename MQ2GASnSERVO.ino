#include <Servo.h>

Servo servo;

const int sensorPin = A0;

int sensorVal = 0;

void setup() {
  servo.attach(9);
  Serial.begin(9600);
}

void loop() {
  servo.write(90);
  sensorVal = analogRead(sensorPin);
  if (sensorVal >= 300) {
    servo.write(120);
    Serial.println("ur gonna die lol");
  } else {
    servo.write(90);
    Serial.println(sensorVal);
  }
  delay(200);
}
