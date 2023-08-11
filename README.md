# Keyboard by KBB

## Summary
We are making this keyboard for self improvement and fun. The 65% mechanical keyboard has it's original PCB design, case and plate model.

## To open the shematics and PCB design
The PCB design was created in KiCad, so you can open it in the `keyboard/` folder.

## To run the code
You only need to upload the code once using Arduino IDE.

Keep in mind, that first the Atmega32u4 will need a bootloader, witch is programmed trough the bootloader pins. We had to program it with an Esp32-C3-mini, witches Arduino ISA codes I will upload here under the folder `Esp32-ISA`.

## Dependencies
Place the dependencies into the lib folder.
Desktop Utility:
--> simple_serial_port https://github.com/dmicha16/simple_serial_port/tree/master

## Layout
![image](https://github.com/Asapgiri/kbb-keyboard/assets/102363485/fa3d3703-e9a0-4804-9f38-b8b7b074fe35)

# Function keys
## Supported
| Combination | Meaning  |
| ---         | ---      |
| FN + 1      | F1       |
| FN + 2      | F2       |
| FN + 3      | F3       |
| FN + 4      | F4       |
| FN + 5      | F5       |
| FN + 6      | F6       |
| FN + 7      | F7       |
| FN + 8      | F8       |
| FN + 9      | F9       |
| FN + 0      | F10      |
| FN + -      | F11      |
| FN + =      | F12      |
| FN + INS    | PRT SCR  |
| FN + WIN    | WIN LOCK |
| FN + ->     | FN LOCK  |
| FN + ALT    | MENU     |

## Under develpement
These keys are yet not supported due to the incompatibility of `Keyboard.h`.
| Combination | Meaning     |
| FN + ;      | PREV MUSIC  |
| FN + \      | NEXT  MUSIC |
| FN + ,      | VOLUME DOWN |
| FN + .      | VOLUME UP   |
| FN + /      | PLAY        |
| FN + END    | SLEEP       |
