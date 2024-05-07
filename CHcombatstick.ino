/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/



#include <Keypad.h>
#include <Joystick.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {1,5,7},
  {2,6,8},
  {3,11,9},
  {4,12,10}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 9, 8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



const byte ROWS2 = 4; //four rows
const byte COLS2 = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys2[ROWS][COLS2] = {
  {'0'},
  {'1'},
  {'2'},
  {'3'}
};
byte rowPins2[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins2[COLS2] = {7}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypadHat = Keypad( makeKeymap(hexaKeys2), rowPins2, colPins2, ROWS, COLS2); 





//Initialise Joystick entity
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 10,
  1,
  false, false, false, false, false, false,
  false, false, false, false, false);

const bool initAutoSendState = true;



void setup(){
  Serial.begin(9600);
  Joystick.begin();
  for(int i=0;i<10;i++){
    Joystick.setButton(i,0);
  }

}

void loop() {
//  char customKey = customKeypad.getKey();    // Read pin values
  CheckAllButtons();
  CheckHatSwitch();

  delay(10);
}


void CheckAllButtons(void) {
  if (customKeypad.getKeys()) {
    for (int i = 0; i < 12; i++) {
      if (customKeypad.key[i].stateChanged) {
        

          //int buttonIndex = rowIndex * 3 + colIndex;
        Joystick.setButton(customKeypad.key[i].kchar-1, customKeypad.key[i].kstate == PRESSED || customKeypad.key[i].kstate == HOLD);
      }
    }
  }
}


void CheckHatSwitch() {
    static int hatPosition = -1; // Use a static variable to maintain state between function calls

    // Scan all keys and update hat position if there's any change
    if (keypadHat.getKeys()) {
        bool up = false, down = false, left = false, right = false;
        
        for (int i = 0; i < LIST_MAX; i++) {
            if (keypadHat.key[i].stateChanged) {
                int keyVal = keypadHat.key[i].kchar;
                bool pressed = (keypadHat.key[i].kstate == PRESSED || keypadHat.key[i].kstate == HOLD);
                
                switch (keyVal) {
                    case '0': up = pressed; break;
                    case '1': right = pressed; break;
                    case '2': down = pressed; break;
                    case '3': left = pressed; break;
                }
            }
        }

        // Update hat position based on key states
        if (up && right) hatPosition = 45;     // Up-Right
        else if (up && left) hatPosition = 315; // Up-Left
        else if (down && right) hatPosition = 135; // Down-Right
        else if (down && left) hatPosition = 225; // Down-Left
        else if (up) hatPosition = 0;         // Up
        else if (right) hatPosition = 90;     // Right
        else if (down) hatPosition = 180;     // Down
        else if (left) hatPosition = 270;     // Left
        else hatPosition = -1;               // Neutral
    }

    // Update the joystick hat switch, this will occur every loop iteration regardless of key change
    Joystick.setHatSwitch(0, hatPosition);
//    delay(50);
}
