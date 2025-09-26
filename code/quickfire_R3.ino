// Quickfire Game
// Author: Salvatore Amico (samic2@uic.edu)
// CS 362, UIC
//
// Description: A 2–4 player Arduino reaction game using multiple Arduinos
// for lights, sound, and LCD display. This cleaned version removes other
// students' names/UINs and retains only the technical content.

// C++ code
//

// This reciver just turns on the power light.


// **********Reciver_3**********
// Arduino Reciver 3 components.
#define POWER_BUTTON_ON 'D'
#define POWER_BUTTON_OFF 'E'
#define LED_RED 2


void setup()
{
 pinMode(LED_RED, OUTPUT);
 Serial.begin(9600);
}

void loop()
{
  // Listen for on/off commands
  if (Serial.available() > 0) 
  {
    char command = Serial.read();

    // turn on/off differnt colors.
    if (command == POWER_BUTTON_ON) 
    {
      digitalWrite(LED_RED, HIGH);
    }
    else if (command == POWER_BUTTON_OFF) 
    {
      digitalWrite(LED_RED, LOW);

    }
  }
}
