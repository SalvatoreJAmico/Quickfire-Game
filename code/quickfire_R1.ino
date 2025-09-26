// Quickfire Game
// Author: Salvatore Amico (samic2@uic.edu)
// CS 362, UIC
//
// Description: A 2–4 player Arduino reaction game using multiple Arduinos
// for lights, sound, and LCD display. This cleaned version removes other
// students' names/UINs and retains only the technical content.

// C++ code
// This reciver will control the main LED lights. 


// **********Reciver_1**********

#define LED_RED 7
#define LED_BLUE 8
#define LED_YELLOW 6
#define LED_GREEN 9

// Arduino Reciver 1 components.
#define RED_LED_ON '1'
#define RED_LED_OFF '2'
#define GREEN_LED_ON '3'
#define GREEN_LED_OFF '4'
#define YELLOW_LED_ON '5'
#define YELLOW_LED_OFF '6'
#define BLUE_LED_ON '7'
#define BLUE_LED_OFF '8'
#define LED_BLINK 'F'

unsigned long previousMillis = 0;



void setup()
{
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // Listen for on/off comands
  if (Serial.available() > 0) {
        char command = Serial.read();
        
    // turn on/off differnt colors.
    	if (command == RED_LED_ON) {
            digitalWrite(LED_RED, HIGH);
        }else if (command == RED_LED_OFF) {
            digitalWrite(LED_RED, LOW);
        }else if (command == GREEN_LED_ON) {
            digitalWrite(LED_GREEN, HIGH);
        }else if (command == GREEN_LED_OFF) {
            digitalWrite(LED_GREEN, LOW);
        }else if (command == YELLOW_LED_ON) {
            digitalWrite(LED_YELLOW, HIGH);
        }else if (command == YELLOW_LED_OFF) {
            digitalWrite(LED_YELLOW, LOW);
        }else if (command == BLUE_LED_ON) {
            digitalWrite(LED_BLUE, HIGH);
        }else if (command == BLUE_LED_OFF) {
            digitalWrite(LED_BLUE, LOW);
        }else if (command == LED_BLINK) {
            halfSecondBlink();
        }
    }
  
}

//In sequince blink

void halfSecondBlink()
{
  digitalWrite(LED_RED, HIGH);
  delayHelper(1000);
  digitalWrite(LED_RED, LOW);
  
  digitalWrite(LED_GREEN, HIGH);
  delayHelper(1000);
  digitalWrite(LED_GREEN, LOW);
 
  digitalWrite(LED_YELLOW, HIGH);
  delayHelper(1000);
  digitalWrite(LED_YELLOW, LOW);
  
  digitalWrite(LED_BLUE, HIGH);
  delayHelper(1000);
  digitalWrite(LED_BLUE, LOW);
  
}

void delayHelper(unsigned long delayTime) 
{
  unsigned long currentMillis = millis();
  
  while (millis() - currentMillis < delayTime) {
    // Wait until enough time has passed
  }

}
