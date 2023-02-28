#include <Servo.h>
#include "HX711.h"


Servo myservo;
HX711 scale;

#define GREEN_LED_PIN 44
#define RED_LED_PIN 45
#define BUZZER 47
#define SERVO_PIN 7

bool empty = false;
int threshold = 30;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  myservo.attach(SERVO_PIN);
  myservo.write(0);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {

  if (empty == false){
    Serial.println("============================");
    int counter = 3; //(60*60)*3;
    // Wait for 3 hour
    for (int i=0; i<counter; i++){
      delay(1000);
      timer(counter - i);
    }
       
    if (analogRead(A0) >= threshold) {
      Serial.println("Food exist! Opening The Door!");
      myservo.write(180);
      digitalWrite(GREEN_LED_PIN, HIGH);
      counter = 3; //60*5;
      for (int i=0; i<counter; i++){
        delay(1000);
        timer(counter - i);
      }
      myservo.write(0);
      digitalWrite(GREEN_LED_PIN, LOW);
      Serial.println("Closing The Door!");
    } 
    else {
      Serial.println("Food not exist!");
      empty = true;
    }
  }
  //checking recharge
  else{
    Serial.println("============================");
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(500);
    Serial.println("Recharge food!");
    while(analogRead(A0) <= threshold){
      delay(500);
    };
    Serial.println("Food is recharged!");
    digitalWrite(BUZZER, LOW);
    digitalWrite(RED_LED_PIN, LOW);
    empty = false;
  }
}

void timer(int sec){
  int second = sec%60;
  int minute = sec/60;
  int hour = minute/60;
  minute = minute%60;
  //hour ---------------------
  if(hour <10){
    Serial.print("0");
    Serial.print(hour);
  }else{
    Serial.print(hour);
  }
  Serial.print(":");
  //minute ---------------------
  if(minute <10){
    Serial.print("0");
    Serial.print(minute);
  }else{
    Serial.print(minute);
  }
  Serial.print(":");
  //second ---------------------
  if(second <10){
    Serial.print("0");
    Serial.print(second);
  }else{
    Serial.print(second);
  }
  Serial.println();
}
