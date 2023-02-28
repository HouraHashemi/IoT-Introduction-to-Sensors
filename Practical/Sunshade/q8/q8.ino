#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(7);
  myservo.write(90);

  pinMode(A5, INPUT);
  pinMode(A0, INPUT);
}

void loop() {
  int lightSensor = analogRead(A0);
  int rainSensor = analogRead(A5);
  Serial.print("LIGHT: ");
  Serial.println(lightSensor);
  Serial.print("RAIN: ");
  Serial.println(rainSensor);
  if (rainSensor > 30 || lightSensor > 500) {
    Serial.println("Sunshade is Opening!");
    myservo.write(180);
  } else {
    Serial.println("Sunshade is Closeing!");
    myservo.write(0);
  }
   delay(1000);
}
