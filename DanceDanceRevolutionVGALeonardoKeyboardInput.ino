#include "Keyboard.h"


#include <stdint.h>

typedef struct 
{
  int buttonPin;
  int previousButtonState;
  uint8_t inputCharacterP1;
  uint8_t inputCharacterP2;
}Pad;

const int SWITCH_PIN = 6;
const int P1_LED_PIN = 7;
const int P2_LED_PIN = 8;

//declaring button pins
Pad pads[] = {
  {2, HIGH, KEY_LEFT_ARROW, 'a'},
  {3, HIGH, KEY_DOWN_ARROW, 's'},
  {4, HIGH, KEY_RIGHT_ARROW, 'd'},
  {5, HIGH, KEY_UP_ARROW, 'w'}
};

const int padLength = sizeof(pads) / sizeof(pads[0]);



void setup() {
  
  //declare the buttons as input_pullup
  for(int i = 0;i<padLength;i++)
  {
    pinMode(pads[i].buttonPin, INPUT_PULLUP);
  }

  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(P1_LED_PIN, OUTPUT);
  pinMode(P2_LED_PIN, OUTPUT);

  Keyboard.begin();
}

int previousSwitchState = HIGH;

void loop() {
  int currentSwitchState = digitalRead(SWITCH_PIN);

  // If the switch state changed, release all currently held keys
  if (currentSwitchState != previousSwitchState) {
    Keyboard.releaseAll();
    previousSwitchState = currentSwitchState;
  }

  bool isPlayer1 = (currentSwitchState == HIGH);

  if (isPlayer1) {
    digitalWrite(P1_LED_PIN, HIGH);
    digitalWrite(P2_LED_PIN, LOW);
  } else {
    digitalWrite(P1_LED_PIN, LOW);
    digitalWrite(P2_LED_PIN, HIGH);
  }

  for(int i =0;i<padLength; i++)
  {
    //checking the state of the button
    int buttonState = digitalRead(pads[i].buttonPin);
    uint8_t activeCharacter = isPlayer1 ? pads[i].inputCharacterP1 : pads[i].inputCharacterP2;

    if (buttonState == LOW && pads[i].previousButtonState == HIGH) { //currently pressed
      Keyboard.press(activeCharacter);
    }

    if (buttonState == HIGH && pads[i].previousButtonState == LOW) { //not currently pressed
      // and it's currently released:
      Keyboard.release(activeCharacter);
    }

    pads[i].previousButtonState = buttonState;
  }
 

}