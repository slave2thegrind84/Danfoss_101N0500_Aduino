# Danfoss_101N0500_Aduino
Replacement controller for Danfoss 101N0500 12volt fridge using an Aduino.

Create your own Danfoss controller with this project. I found this 12v camping fridge on the side of the road. The original thermister had broken. I beleive the thermister was a 1k NTC. Instead of buying a replacement part im spending many hours and double(?) the money making my own controller! I cant resist a challenge. 

WARNING: Im not an expert in electronics, just a novice tinkerer. The schematics and code provided here should not be trusted. You have been warned!

Components used:
- Arduino board (currently Uno)
- 10k 
- 2 x 5v arduino relay modules (Check AliExpress)
- DC DC Buck converter step down module - LM2526
- DS18B20 temperature sensor probe.
- 128X32 LCD LED Display 0.91 (Replacing the original screen)
- Existing temperature control buttons

![Danfoss electrical interface](./danfos_motor_interface.jpeg?raw=true "interface")

Danfoss Diagram can be found here: https://www.keoghsmarine.com.au/image/catalog/101N0510_Diagram.jpg
