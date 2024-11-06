#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int functionButtonPin = 10;
int playerButtonPin = 9;
int cardButtonPin = 8;
int functionButtonState = 0;
int playerButtonState = 0;
int cardButtonState = 0;
int numPlayers = 0;
int numCards = 0;
int dealStepPin = 6;
int dealDirPin = 5;
int rotStepPin = 4;
int rotDirPin = 3;
int motorPin1 = 11;
int motorPin2 = 12;
int enablePin = 13;

const int stepsPerRevolution = 200; 
int numRevolutions = 0; 
int currentSteps = 0;
int stepsPerStop = stepsPerRevolution / numPlayers;

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	pinMode(playerButtonPin, INPUT_PULLUP);
  pinMode(cardButtonPin, INPUT_PULLUP);
  lcd.backlight();
	lcd.print("DUEN");

  pinMode(dealStepPin, OUTPUT);
  pinMode(rotStepPin, OUTPUT);
  pinMode(dealDirPin, OUTPUT);
  pinMode(rotDirPin, OUTPUT);
  
  digitalWrite(dealStepPin, LOW);
  digitalWrite(dealDirPin, LOW);
  digitalWrite(rotStepPin, LOW);
  digitalWrite(dealDirPin, LOW);
  

}

void loop()
{
	// Do nothing here...
  playerButtonState = digitalRead(playerButtonPin);
  cardButtonState = digitalRead(cardButtonPin);
  if (playerButtonState == LOW) {
  lcd.clear();
  lcd.print("# of players: "); 
  lcd.setCursor(0,1);
  lcd.print(numPlayers);
  delay(500);
  numPlayers += 1;
  if (numPlayers > 6) {
    numPlayers = 1;
    }
  }
  if (cardButtonState == LOW) {
  lcd.clear();
  lcd.print("# of cards: "); 
  lcd.setCursor(0,1);
  lcd.print(numCards);
  delay(500);
  numCards += 1;
    if (numCards > 7) {
    numCards = 1;
    }
  }
  /*if (functionButtonState == LOW) {
  lcd.clear();
  lcd.print("Shuffling..."); 
  lcd.setCursor(0,1);
  delay(500);
  //shuffle();
  lcd.clear();
  lcd.print("Dealing..."); 
  lcd.setCursor(0,1);
  delay(500);
  //deal();
  } */
}
void deal() 
{
  numRevolutions = 0;
  while (numRevolutions < numCards) { 
   if(currentSteps < stepsPerRevolution) {
    digitalWrite(rotStepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(rotStepPin, LOW);
    delayMicroseconds(500);
    currentSteps++; 
      if (currentSteps % stepsPerStop == 0) {
        delay(1000);
        digitalWrite(dealStepPin, HIGH);
        delayMicroseconds(200);
        digitalWrite(dealStepPin, LOW);
      }
   }
   numRevolutions++;

  }
}
