//Library to use LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define col 16
#define lin 2
#define ende 0x27

LiquidCrystal_I2C lcd(ende, col, lin);

//Declaring variables
int ledRedPin = 11;
int ledYellowPin = 12;
int ledGreenPin = 13;
int buzzerPin = 10;
int pirPin = 9;
int contador = 0;
int delayMS = 3000;

void setup() {
  //Serial monitor 9600 bps
  Serial.begin(9600);

  //Pins configuration
  pinMode(ledRedPin, OUTPUT);
  pinMode(ledYellowPin, OUTPUT);
  pinMode(ledGreenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);

  //Settings of LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Contador de pessoas");

}

void loop() {
  byte movement = digitalRead(pirPin);

  //Everytime the sensor PIR catch a movement, he adds 1 to "contador"
  if(movement){
    contador ++;
  }

  movement = false;
  lcd.clear();

  //Case the shelter has more than 10 people
  if(contador >= 10){
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledRedPin, HIGH); // Lights up the red led
    tone(buzzerPin, 262); // Actived the buzzer

    lcd.setCursor(0, 0);
    lcd.print("Pes.: ");
    lcd.print(contador); // Show how many people are in the shelter
    lcd.setCursor(0, 1);
    lcd.print("Cheio.");
    delay(delayMS); //Delay of 3 seconds
    
  }
  //Case the shelter has more than 5 people
  else if(contador >= 5 ){
    digitalWrite(ledGreenPin, LOW);
    digitalWrite(ledYellowPin, HIGH);
    digitalWrite(ledRedPin, LOW);
    noTone(buzzerPin);

    lcd.setCursor(0, 0);
    lcd.print("Pes.: ");
    lcd.print(contador);
    lcd.setCursor(0, 1);
    lcd.print("Médio.");
    delay(delayMS);
  }
  //Case the shelter has less than 5 people
  else{
    digitalWrite(ledGreenPin, HIGH);
    digitalWrite(ledYellowPin, LOW);
    digitalWrite(ledRedPin, LOW);
    noTone(buzzerPin);

    lcd.setCursor(0, 0);
    lcd.print("Pes.: ");
    lcd.print(contador);
    lcd.setCursor(0, 1);
    lcd.print("Baixa.");
    delay(delayMS);
  }
}