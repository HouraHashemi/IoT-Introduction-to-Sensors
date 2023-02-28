#include <Key.h>
#include <Keypad.h>

#include <LiquidCrystal.h>
#include <Servo.h>

#define PIR_A1 22
#define LED_A1 23

#define PIR_A2 24
#define LED_A2 25

#define PIR_A3 26
#define LED_A3 27
//----------------------

#define PIR_B1 28
#define LED_B1 29

#define PIR_B2 30
#define LED_B2 31

#define PIR_B3 32
#define LED_B3 33
//----------------------

#define PIR_C1 34
#define LED_C1 35

#define PIR_C2 36
#define LED_C2 37

#define PIR_C3 38
#define LED_C3 39
//----------------------

#define SERVO_PIN 53

Servo servo;

const int rs = 16, en = 17, d4 = 18, d5 = 19, d6 = 20, d7 = 21;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const byte ROWS = 4;  //four rows
const byte COLS = 3;  //three columns

char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte rowPins[ROWS] = { 43, 44, 45, 46 };
byte colPins[COLS] = { 42, 41, 40 };
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


String id = "1234";
String pass = "0000";
bool login = false;


void setup() {
//  pinMode(pirPin, INPUT);  
//  pinMode(ledPin, OUTPUT);
  servo.attach(SERVO_PIN);
  servo.write(90);
  lcd.clear();
  lcd.begin(16,4);
}


void loop() {

    if (login == true){
     printOnLcd(0, "--FREE SPACES--"); 

    //A --------------
    //A1
    int counter_A1 = isfree(PIR_A1, LED_A1);
    int counter_A2 = isfree(PIR_A2, LED_A3);
    int counter_A3 = isfree(PIR_A3, LED_A3);

    int counter_B1 = isfree(PIR_B1, LED_B1);
    int counter_B2 = isfree(PIR_B2, LED_B3);
    int counter_B3 = isfree(PIR_B3, LED_B3);

    int counter_C1 = isfree(PIR_C1, LED_C1);
    int counter_C2 = isfree(PIR_C2, LED_C3);
    int counter_C3 = isfree(PIR_C3, LED_C3);

    int counter_A = counter_A1 + counter_A2 + counter_A3;
    int counter_B = counter_B1 + counter_B2 + counter_B3;
    int counter_C = counter_C1 + counter_C2 + counter_C3;

    printOnLcd(1, "A: "+String(3-counter_A));
    printOnLcd(2, "B: "+String(3-counter_B));
    printOnLcd(3, "C: "+String(3-counter_C));
    delay(100);
  }
  else{
    lcd.clear();
    printOnLcd(1, "--- WELCOME ---");
    printOnLcd(2, " SMART PARKING ");
    delay(100);
    
    lcd.clear();
    printOnLcd(0, "CONF:[#] CLR:[*]");
    printOnLcd(3, "MSG:");
    
    // Check ID
    while(true){
      printOnLcd(1, "ID:----");
      String this_id = get_input(3,1);
      if(this_id == id){
        printOnLcd(3, "MSG: CORRECT");
        delay(50);
        printOnLcd(3, "MSG:        ");
        break;
      }else{
        printOnLcd(3, "MSG: WRONG");
        delay(100);
        printOnLcd(3, "MSG:      ");
      }
    }
    // Check PASSWORD
    while(true){
      printOnLcd(2, "PASSWORD:----");
      String this_pass = get_input(9,2);
      if(this_pass == pass){
        printOnLcd(3, "MSG: CORRECT");
        delay(50);
        printOnLcd(3, "MSG:        ");
        break;
      }else{
        printOnLcd(3, "MSG: WRONG");
        delay(100);
        printOnLcd(3, "MSG:      ");
      }
    }
    
    login = true;
    lcd.clear();
    printOnLcd(1, "  --- ENTER ---");
    opening_closing_door();
    lcd.clear();
  }
  
}//end

//----------------------------------------
void printOnLcd(int lineNumber, String message){
  lcd.setCursor(0, lineNumber);
  lcd.print(message);
}


int isfree(int PIR, int LED){
  if(digitalRead(PIR) == HIGH){
    delay(5);
    if(digitalRead(PIR) == HIGH){
      digitalWrite(LED, HIGH);
      return 1;
    }else{
      digitalWrite(LED, LOW);
      return 0;
    }
  }else{
      digitalWrite(LED, LOW);
      return 0;
    }
}


String get_input(int start_cursor,int line){
  char key = '-';
  String input;
  int counter = 0;
  //get password from user char by char
  while(key != '#'){
      key = keypad.getKey();
      if(key){
          // delete char just entered or enter new char
          if((key == '*') && (counter>0)){
              counter = counter - 1;
              lcd.setCursor(start_cursor+counter, line);
              lcd.print('-');
              input = input.substring(0, counter);
          }
          else if(input.length()<4 && (key!='#')){
              input = input + key;
              lcd.setCursor(start_cursor+counter,line);
              lcd.print(key);
              counter = counter + 1;
          }    
      }//end if
    }//end inside while
  return input;
}


void opening_closing_door() {
  servo.write(180);
  delay(100);
  servo.write(90);
}
