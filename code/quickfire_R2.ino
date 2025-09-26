// Quickfire Game
// Author: Salvatore Amico (samic2@uic.edu)
// CS 362, UIC
//
// Description: A 2–4 player Arduino reaction game using multiple Arduinos
// for lights, sound, and LCD display. This cleaned version removes other
// students' names/UINs and retains only the technical content.

// C++ code

// This reciver activates the buzzer and the go lights. 

// **********Reciver_2**********
// Arduino Reciver 2 components.
#define PIZO_BUZZER_ON '9'
#define PIZO_BUZZER_OFF 'A'
#define ACTION_LIGHTS_ON 'B'
#define ACTION_LIGHTS_OFF 'C'

//Pin locations 
#define BUZZER 4
#define GOLIGHTS 2

void setup()
{
  Serial.begin(9600);
  pinMode(BUZZER,OUTPUT);
  pinMode(GOLIGHTS, OUTPUT);
  //digitalWrite(GOLIGHTS, HIGH);
}
void loop()
{
 // Listen for on/off commands
  if (Serial.available() > 0) 
  {
    char command = Serial.read();
	
    if (command == 'B')
    {
      goLightFlashing();
    }
  }
}

void goLightFlashing()
{
  for(int i = 0; i < 10;i++)
  {
  digitalWrite(BUZZER, HIGH);  
  digitalWrite(GOLIGHTS, HIGH);
  delayHelper(50);
  digitalWrite(BUZZER, LOW); 
  digitalWrite(GOLIGHTS, LOW);
  delayHelper(50);
    i++;
  }
  
}

// Delay that will not inerrupt program
void delayHelper(unsigned long delayTime) 
{
  unsigned long currentMillis = millis();
  
  while (millis() - currentMillis < delayTime) {
    // Wait until enough time has passed
  }
}
