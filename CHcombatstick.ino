#include <Keypad.h>
#include <Joystick.h>


const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'0','4','6'},    // B1,B5,n
  {'1','5','7'},    // B2,B6,e
  {'2','11','8'},   // B3,,s   (11 & 12 are unused locations so just stick high values there)
  {'3','12','9'}   //B4, ,w
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 9, 8}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



const byte ROWS2 = 4; //four rows
const byte COLS2 = 1; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys2[ROWS][COLS2] = {
  {'0'},   //N
  {'1'},   //E
  {'2'},   //S
  {'3'}    //W
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
  customKeypad.setDebounceTime(20);
  customKeypad.setHoldTime(200);
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
    for (int i = 0; i < 10; i++) {
      if (customKeypad.key[i].stateChanged ){ //&& (customKeypad.key[i].kstate == PRESSED || customKeypad.key[i].kstate == HOLD)) {
        


                switch (customKeypad.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    Joystick.setButton(customKeypad.key[i].kchar- '0', 1);
                break;
                    case HOLD:
                    Joystick.setButton(customKeypad.key[i].kchar- '0', 1);
                break;
                    case RELEASED:
                    Joystick.setButton(customKeypad.key[i].kchar- '0', 0);
                break;
//                    case IDLE:
//                    int c = 0;   Joystick.setButton(customKeypad.key[i].kchar- '0', 0);
                }


          //int buttonIndex = rowIndex * 3 + colIndex;
//        Joystick.setButton(customKeypad.key[i].kchar- '0', customKeypad.key[i].kstate == PRESSED  || customKeypad.key[i].kstate == HOLD);
//        Serial.print(customKeypad.key[i].kstate);
//        Serial.print(" > ");
//        Serial.println(customKeypad.key[i].kchar);
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



