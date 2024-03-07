# Danfoss_101N0500_Aduino
Replacement controller for Danfoss 101N0500 12volt fridge using an Aduino.

# Introduction
Create your own Danfoss controller with this project. I found this 12v camping fridge on the side of the road. The original thermister had broken. I beleive the thermister was a 1k NTC. Instead of buying a replacement part im spending many hours and double(?) the money making my own controller! I cant resist a challenge. 

WARNING: Im not an expert in electronics, just a novice tinkerer. The schematics and code provided here should not be trusted. You have been warned!

# Components
- Arduino board (currently Uno)
- 10k 
- 2 x 5v arduino relay modules (Check AliExpress)
- DC DC Buck converter step down module - LM2526
- DS18B20 temperature sensor probe.
- 128X32 LCD LED Display 0.91 (Replacing the original screen)
- Existing temperature control buttons

# Control board

## Preparation
I re-used the input control board and its wiring harness. I de-soldered the display and replaced it with the new LCD screen. Re-using the wiring harness and connector powered the original board and microcontroller, resulting in active circuits. I just desoldered all the original components. I might replace this board later with a custom built one.


## Wiring Harness
- Red = GND 	(yes, its backwards)
- Black = +5v
- Yellow = button array
- White =  LCD (SCL?)
- Blue = LCD (SDA?)
- Brown = Green LED


## Buttons
I built a resister ladder for the 4 buttons. This means I only needed a single analog input to handle input from 4 different buttons.

## Images
![User_Control_Schematic](./images/UserControlSchematic.png?raw=true "schematic")
![UserControl Front](./images/UserControlFront.jpeg?raw=true "front")
![UserControl Back](./images/UserControlBack.jpeg?raw=true "back")



# References

![Danfoss electrical interface](./images/danfos_motor_interface.jpeg?raw=true "interface")

Danfoss Diagram can be found here: https://www.keoghsmarine.com.au/image/catalog/101N0510_Diagram.jpg

