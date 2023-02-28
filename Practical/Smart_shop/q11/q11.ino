#include <Servo.h>

#define WINDOW_SERVO 22
#define BUZZER 24
#define WATER_SERVO 26


#define FLAME_SENSOR 53
#define GAS_SENSOR 50
//#define FLAME_SENSOR A8
//#define GAS_SENSOR A12

Servo WindowServo;
Servo WaterServo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(WINDOW_SERVO, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(WATER_SERVO, OUTPUT);

  pinMode(FLAME_SENSOR, INPUT);
  pinMode(GAS_SENSOR, INPUT);

  WindowServo.attach(WINDOW_SERVO);
  WaterServo.attach(WATER_SERVO);

  Serial.println("EVEY THING IS FINE.");
  Serial.println("=========================");

}

void loop() {
  if (digitalRead(FLAME_SENSOR)==HIGH){
    digitalWrite(BUZZER, HIGH);
//    tone(10, 1000);
    Serial.println("FLAME DETECTED!");
    WaterServo.write(180);
    while(digitalRead(FLAME_SENSOR)==HIGH);
//    noTone(10);
    Serial.println("NO FLAME ANYMORE");
    WaterServo.write(0);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    Serial.println("-------------------------");
  }
  delay(500);
  
    if (digitalRead(GAS_SENSOR)==HIGH){
    digitalWrite(BUZZER, HIGH);
//    tone(10, 1000);
    Serial.println("GAS DETECTED!");
    WindowServo.write(180);
    while(digitalRead(GAS_SENSOR)==HIGH);
//    noTone(10);
    Serial.println("NO GAS ANYMORE");
    WindowServo.write(0);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    Serial.println("-------------------------");
  }  
  delay(500);
}



////  This function returns the analog data to calling function
//int readAnalogGasSensor() {
//  unsigned int sensorValue = analogRead(GAS_SENSOR);  // Read the analog value from sensor
//  unsigned int outputValue = map(sensorValue, 0, 1023, 0, 255); // map the 10-bit data to 8-bit data
//  if (outputValue > 65)
//    digitalWrite(GAS_SENSOR, HIGH); // 
//  else
//    digitalWrite(GAS_SENSOR, LOW);
//  return outputValue;             // Return analog moisture value
//}
