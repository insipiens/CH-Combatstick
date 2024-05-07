# CH Combat Stick

## Introduction

* * *

This project is for the Arduino Pro Micro code to run a custom USN CH-CombatStick with board revision 5.00 

I wanted to add this stick to my Sidewinder FFB2 base, I initially referenced https://github.com/dlwalter/ch-joy version which helped me get started on this

&nbsp;

## Configuration

* * *

However the board in this combatstick had different coloured wires, the board has a silk screen reference: 509-074B / REV 5.00

![image](https://github.com/insipiens/CH-Combatstick/assets/68975498/14469eb4-7892-4166-8cf9-bcb159d8a47d)


&nbsp;

The board has two sets of wire terminals, the 8 way terminal is to the MCU in the joystick base. Note to self, clean flux from board before sealing 🤨 


![image](https://github.com/insipiens/CH-Combatstick/assets/68975498/41090bbc-6abc-475a-ba25-e13bc5c87872)


&nbsp;

It works as a keypad matrix

&nbsp;
&nbsp;

|     |     |     |     |     |     |
| :--- | :--- | :--- | :--- | :--- | :--- |
| Pins |     | 2   | 3   | 4   | 5   |
|     | Wire Colours | Orange | White | Grey | Purple |
| 6   | Green | 1   | 2   | 3   | 4   |
| 7   | Red | N   | E   | S   | W   |
| 8   | Brown | n   | e   | s   | w   |
| 9   | Blue | 5   | 6   |     |     |

&nbsp;


&nbsp;

- Numbers indicate buttons, 1 is trigger - 
Letters:
- uppercase is Hat switch 1 (with circular knurling),
- Lower Case is Hat switch 2 (NSWE knurling)
- connected to Pins on Arduino Pro Micro
&nbsp;


## Coding

I used the keypad library, however I couldn't get it to work until I realised that the matrix above is actually inverted. I haven't altered the matrix accordingly but you will note in the code that the pins are differently assigned.

So I ended with two keypad instances, the second to allow the Hat Switch 1 to be rendered as an 8 way hat just on pin 7.


```
const byte ROWS2 = 4; //four rows
const byte COLS2 = 1; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys2[ROWS][COLS2] = {
  {'0'}, //N
  {'1'}, //E
  {'2'}, //S
  {'3'}  //W
};
byte rowPins2[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins2[COLS2] = {7}; //connect to the column pinouts of the keypad
```
&nbsp;
