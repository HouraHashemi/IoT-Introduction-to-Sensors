

const int ledPin = 22; //pin at which LED is connected
const int ldrPin = A0; //pin at which LDR is connected
int threshold = 600;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); //Make LED pin as output
  pinMode(ldrPin, INPUT); //Make LDR pin as input
}

void loop(){
  //saving the analog values received from LDR
  int ldrStatus = analogRead(ldrPin); 
  //set the threshold value below at which the LED will turn on
  //you can check in the serial monior to get approprite value for your LDR
  if (ldrStatus <= threshold){
    digitalWrite(ledPin, HIGH);  //Turing LED ON
    Serial.print("Its DARK, Turn on the LED : "); 
    Serial.println(ldrStatus);
  }
  else{
    digitalWrite(ledPin, LOW); //Turing OFF the LED
    Serial.print("Its BRIGHT, Turn off the LED : ");
    Serial.println(ldrStatus);
  }
  delay(1000);
}
