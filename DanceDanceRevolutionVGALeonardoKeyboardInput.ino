#include "Keyboard.h"


typedef struct 
{
  int buttonPin;
  int previousButtonState;
  char inputCharacter;
}Pad;

const int padLength = 4;
//declaring button pins
Pad pads[] = {{2,HIGH,'a'},{3,HIGH,'s'},{4,HIGH,'d'},{5,HIGH,'w'}};



void setup() {
  
  //declare the buttons as input_pullup
  for(int i = 0;i<padLength;i++)
  {
    pinMode(pads[i].buttonPin, INPUT_PULLUP);
  }

  Keyboard.begin();
}

void loop() {
  for(int i =0;i<padLength; i++)
  {
    //checking the state of the button
    int buttonState = digitalRead(pads[i].buttonPin);
    if (buttonState == LOW && pads[i].previousButtonState == HIGH) { //currently pressed
      Keyboard.press(pads[i].inputCharacter);
    }

    if (buttonState == HIGH && pads[i].previousButtonState == LOW) { //not currently pressed
      // and it's currently released:
      Keyboard.release(pads[i].inputCharacter);
    }

    pads[i].previousButtonState = buttonState;
  }
 

}