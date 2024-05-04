# CH Combat Stick

## Introduction

* * *

This project is for the Arduino Pro Micro code to run a custom USN CH-CombatStick with board revision 5.00 

I wanted to add this stick to my Sidewinder FFB2 base, I initially referenced https://github.com/dlwalter/ch-joy version which helped me get started on this

&nbsp;

## Configuration

* * *

However the board in this combatstick had different coloured wires, the board has a silk screen reference: 509-074B / REV 5.00

![d23757f6ccf81ce8c94d027b9806b28b.png](file:///home/john/.config/joplin-desktop/resources/13c7114536ac4501b77cbb0dcd5ceab4.png)

&nbsp;

The board has two sets of wire terminals, the 8 way terminal is to the MCU in the joystick base. Note to self, clean flux from board before sealing :o

![5fbe903517a6a83406366a9daadebe6e.png](file:///home/john/.config/joplin-desktop/resources/97585b338ae6485986f462c9bc826f3a.png)

&nbsp;

It works as a keypad matrix

&nbsp;

|     |     |     |     |     |
| :--- | :--- | :--- | :--- | :--- |
|     | Orange | White | Grey | Purple |
| Green | 1   | 2   | 3   | 4   |
| Red | N   | E   | S   | W   |
| Brown | n   | e   | s   | w   |
| Blue | 5   | 6   |     |     |

&nbsp;

- Numbers indicate buttons, 1 is trigger - 
- Letters: uppercase is Hat switch 1 (with circular knurling), Lower Case Hat switch 2 (NSWE knurling)

&nbsp;

&nbsp;

&nbsp;
