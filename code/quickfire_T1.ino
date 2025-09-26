// Quickfire Game
// Author: Salvatore Amico (samic2@uic.edu)
// CS 362, UIC
//
// Description: A 2–4 player Arduino reaction game using multiple Arduinos
// for lights, sound, and LCD display. This cleaned version removes other
// students' names/UINs and retains only the technical content.

// ******HEADER******
//Group Number: 42
//Quickfire Game



//Salvatore Amico, samic2@uic.edu, 
//Quickfire Game (Abstract):
//The "Quickfire Game" is a 2-4 player game built around an Arduino board, ideal for group enjoyment and skill enhancement. 
//It challenges players to swiftly react to a light and sound cue, with their reaction times sparking friendly rivalry. 
//It features multiplayer and single-player modes and is perfect for gatherings and solo play. 
//The construction includes assembling LEDs, buttons, resistors, and an LCD into a case, offering a hands-on experience in electronics. 
//The "Quickfire Game" is a great choice for family and friends, combining entertainment with educational value.




// ********Transmitter************


// Arduino includes
#include <LiquidCrystal.h>





         
// Lcd pin setup
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);



// LED pin assignments
#define LED_BUTTON_YELLOW 6 
#define LED_BUTTON_RED 7
#define LED_BUTTON_BLUE 8
#define LED_BUTTON_GREEN 9 
#define POWER_BUTTON 10 

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

// Arduino Reciver 2 components.
#define PIZO_BUZZER_ON '9'
#define PIZO_BUZZER_OFF 'A'
#define ACTION_LIGHTS_ON 'B'
#define ACTION_LIGHTS_OFF 'C'

// Arduino Reciver 3 components.
#define POWER_BUTTON_ON 'D'
#define POWER_BUTTON_OFF 'E'

// LCD disply 16 x 2.
const int SCREENWIDTH = 16;
const int SCREENHIGHT = 2;
const int LINE1 = 0;
const int LINE2 = 1;

int stringStart = 0;
int stringEnd = 0;
int scrollCursor = 16; 



// **********LCD Print messages**********
// 16 or less per line please.

// Welcome screen
String welcomeLine_1 = "Welcome to";
String welcomeLine_2 = "Quick Fire!";
String welcomeLine_3 = "Press red";
String welcomeLine_4 = "for the rules!";

// Rules
String ruelsLine_1 = "Quick to press!";
String ruelsLine_2 = "First buzz wins";
String ruelsLine_3 = "Buzzer ends race";
String ruelsLine_4 = "Ready, set, go!";
String ruelsLine_5 = "Press Green";
String ruelsLine_6 = "to play!";// the last line
// Stats
String gameStatsLine_1 = "Best Time Ever: ";
String gameStatsLine_2 = "New Best: ";
// Playing screen
String gamePlayingLine_1 = "Playing!";
String gamePlayingLine_2 = "Wait for it ...";
String gamePlayingLine_3 = "Go ! ! !";
// Quiting
String quitingLine_1 = "Quiting...";
String quitingLine_2 = "Game Over";
//**********END MESSAGES**********//


// Game stats
//double playerRedTime;
//double playerYellowTime;
//double playerBlueTime;
//double playerGreenTime;
String winner;
//String highWinner;


// Game states of play
bool playing;
bool gameOFF;
bool goIndicator;
bool displayed;
bool playerWin;

//set delay timer for debounce
unsigned long prevButtonChangeTime = millis();
unsigned long durationDebounce = 50;

// Player timers 
  unsigned long yellow_start_time;
  unsigned long yellow_end_time;
  unsigned long yellow_duration;
  unsigned long red_start_time;
  unsigned long red_end_time;
  unsigned long red_duration; 
  unsigned long blue_start_time;
  unsigned long blue_end_time;
  unsigned long blue_duration; 
  unsigned long green_start_time;
  unsigned long green_end_time;
  unsigned long green_duration; 

  byte yellowButtonStatus;
  byte redButtonStatus;
  byte blueButtonStatus;
  byte greenButtonStatus;
  byte powerButtoStatus;


void setup()
{
  // start serial communication
  Serial.begin(9600);
  // Assign pin modes
  pinMode(POWER_BUTTON, INPUT_PULLUP);
  pinMode(LED_BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(LED_BUTTON_RED, INPUT_PULLUP);
  pinMode(LED_BUTTON_BLUE, INPUT_PULLUP);
  pinMode(LED_BUTTON_GREEN, INPUT_PULLUP);
  
  // Test lights and buzzer.
  Serial.write(LED_BLINK);
   delayHelper(1000);
  Serial.write(ACTION_LIGHTS_ON);
   
  
  // Display initial welcome message.
  lcd.begin(SCREENWIDTH,SCREENHIGHT);
  lcd.setCursor(0, LINE1);
  lcd.print(welcomeLine_1);
  lcd.setCursor(0, LINE2);
  lcd.print(welcomeLine_2);
  delayHelper(1000);
  lcd.clear();
  gameOFF =false;
  
}

void loop()
{
  
  
  Serial.write(POWER_BUTTON_ON);
  
  
  // when the game is turned off.
  while (gameOFF)
  {
    Serial.write(POWER_BUTTON_OFF);
    powerButtoStatus = digitalRead(POWER_BUTTON);
    
    if (powerButtoStatus == LOW)
    {
      
      Serial.write(POWER_BUTTON_ON);
      gameOFF = false;
      delayHelper(50);
    }
  }
  
    // While the game is not in play mode. 
    //********************************************//
    while (!playing )
    {
      //Listening for button presses
      redButtonStatus = digitalRead(LED_BUTTON_RED);
      powerButtoStatus = digitalRead(POWER_BUTTON);

      lcd.setCursor(0, LINE1);
      lcd.print(welcomeLine_3);
      lcd.setCursor(0, LINE2);
      lcd.print(welcomeLine_4);
      // turnoff the game
      if (powerButtoStatus == LOW)
      {
      
        quit();
        lcd.clear();
      }

      if (redButtonStatus == LOW)
      {
        
        lcd.clear();
        Serial.write(RED_LED_ON);
        delayHelper(500);
        Serial.write(RED_LED_OFF);
        displayRules();

      }

    }// End while(!playing)
  	//********************************************//
 
  
  	// ********************GAME PLAY LOOP********************//
    while(playing && !gameOFF )
    {
      if (!displayed)
      {
      lcd.clear(); 
      displayStats();
      delayHelper(500);
      
      displayed = true;
      lcd.clear();
      }
      
      if ( !goIndicator)
      {

        lcd.setCursor(0, LINE1);
        lcd.print(gamePlayingLine_1);
        lcd.setCursor(0, LINE2);
        lcd.print(gamePlayingLine_2);
        delayHelper(randomNum());
        lcd.clear();          
        lcd.print(gamePlayingLine_3);
        goIndicator = true;
        Serial.write(ACTION_LIGHTS_ON);
        }
      
      
      
      // ********WE ARE WORKING HERE!**********//
      
      // TODO: the power button is not working
      // 	   at all pioints in the game.
      
      // TODO: The game loop is still buggy
      
      // TODO: The rule menue is displayed every cycle of the game loop.
      
      // TODO: finish random number generator line 324
      
      // TODO: no debounceing was done.
      
      
      
      
     while (!playerWin)
     {
       
      //Listening for button presses
      powerButtoStatus = digitalRead(POWER_BUTTON);
      blueButtonStatus = digitalRead(LED_BUTTON_BLUE);
      yellowButtonStatus = digitalRead(LED_BUTTON_YELLOW);
      redButtonStatus = digitalRead(LED_BUTTON_RED);
      greenButtonStatus = digitalRead(LED_BUTTON_GREEN);
     
      
      
      // turnoff the game
      if (powerButtoStatus == LOW)
      {
        quit();
        lcd.clear();
      }

      if (redButtonStatus == LOW)
      {
        Serial.write(RED_LED_ON);
        delayHelper(500);
        Serial.write(RED_LED_OFF);
        playerWin =true;
         winner ="Red";
      }
      if (yellowButtonStatus == LOW)
      {
        Serial.write(YELLOW_LED_ON);
        delayHelper(500);
        Serial.write(YELLOW_LED_OFF);
        playerWin =true;
         winner ="Yellow";
      }
      if (greenButtonStatus == LOW)
      {
        Serial.write(GREEN_LED_ON);
        delayHelper(500);
        Serial.write(GREEN_LED_OFF);
        playerWin =true;
         winner ="Green";
      }
      if (blueButtonStatus == LOW)
      {
        Serial.write(BLUE_LED_ON);
        delayHelper(500);
        Serial.write(BLUE_LED_OFF);
        playerWin =true;
        winner ="Blue";
      }
   	}//End while (playerWin)
       
      
      displayStats();
      delayHelper(2000);
      lcd.clear();
      playing = false;
      displayed = false;
      goIndicator = false;
      playerWin = false;

       
     
  	}// End while(playing)
  
 
  
}// End loop()




// ********************Game methods**********************
// TODO:Gennerate random numbers from 50 to 1000
// 		and return the number as an int..
int randomNum()
{
  return 500;
}
  
//***GOOD***
void displayStats()
{
  
  lcd.setCursor(0, LINE1);
  lcd.print(gameStatsLine_2 + winner);
  
  
}
        
// ***GOOD***        
void displayRules()
{
  
  bool buttonPressed = false;
  
  while (!buttonPressed)
  {
    
    lcd.setCursor(0, LINE1);
    lcd.print(ruelsLine_1);
    lcd.setCursor(0, LINE2);
    lcd.print(ruelsLine_2);
    delayHelper(2000);
    lcd.clear();
    lcd.setCursor(0, LINE1);
    lcd.print(ruelsLine_3);
    lcd.setCursor(0, LINE2);
    lcd.print(ruelsLine_4);
    delayHelper(2000);
    lcd.clear();
    lcd.setCursor(0, LINE1);
    lcd.print(ruelsLine_5);
    lcd.setCursor(0, LINE2);
    lcd.print(ruelsLine_6);
    delayHelper(2000);
    
    
    
    while (!buttonPressed)
    {
      
    //Listening for button presses
    greenButtonStatus = digitalRead(LED_BUTTON_GREEN);
    yellowButtonStatus = digitalRead(LED_BUTTON_YELLOW);
    
    
    if (greenButtonStatus == LOW)
    {
      Serial.write(GREEN_LED_ON);
      delayHelper(500);
      Serial.write(GREEN_LED_OFF);
      playing = true;
      buttonPressed = true;
      break;
    }
      
    }// End while (!buttonPressed)
  }  
}

//***GOOD***  
void quit()
{
  gameOFF = true;
  lcd.clear();
  lcd.setCursor(1, LINE2);
  lcd.print(quitingLine_1);
  delayHelper(500);
  
  
}

// Delay that will not inerrupt program
void delayHelper(unsigned long delayTime) 
{
  unsigned long currentMillis = millis();
  
  while (millis() - currentMillis < delayTime) {
    // Wait until enough time has passed
  }
}
      
// ******************End Game methods********************
