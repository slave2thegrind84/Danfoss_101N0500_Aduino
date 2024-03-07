# Danfoss_101N0500_Aduino
An Arduino replacement for Evakool Koolmate IB40 camping fridge with Danfoss 101N0500 module and compressor.

# Introduction
I found an dumped 12v camping fridge on the side of the road. It worked for a short while, but the started freezing its contents. After investigation I concluded the thermister was broken. Pulling it apart confirmed the probe had expanded and cracked. A quick check for a replacement part only offered expensive options, even if they had any stock. I had some old electronics projects laying around so started to canibalise them for a new controller for this fridge

**WARNING: Im not an expert in electronics. The schematics and code provided here should not be trusted for safety or even if they work! You have been warned!**

# The Fridge
At the heart of the fridge is a Danfoss 101N500 module and compressor. This itself has a [pin out](./images/danfos_motor_interface.jpeg) and provides various programming options. You can also find a schematic for the module [here](https://www.keoghsmarine.com.au/image/catalog/101N0510_Diagram.jpg).

The Danfoss module and compressor has some neat features built into it. For example it will work on 240v or 12v. The Evakool model comes with a battery saver feature and fuse. These will come in handy later. I love the fact that I can take 12v directly from the module for use on my new mainboard with a stepdown in voltage. 

There is a mainboard to control the module and compressor and also interfaces with the user temperature control with LCD, the lid light and the fan. 

The user control has 4 buttons, 2 LED's and a display. It connects to the mainboard using a wiring harness of 6 wires. On this PCB is a chip and other basic components.

# Investigation
First of all, I have no idea how to reprogram the user control LCD and chip so need to replace the screen. I could re-use the harness to provide positive and negative and 4 data wires. 

Second, I threw away the mainboard. I would use in its place an arduino.

But how do I control the motor? I thought it would be as simple as providing power and using a relay from my arduino to turn on and off. Unfortunaly, the danfos unit has some smarts to it. I could get it to turn on if I placed a resistor between the C and T plugs on the danfoss module. This tricks the module into thinking the temperature is high and needs to turn on. On an open circuit it turns off. I could use a combination of resistor and relay to control the compressor. Great!

# Building a replacement

I had various components kicking around and put together a list of things I would need:

- Arduino board (currently Uno)
- 2 x 5v arduino relay modules
- DC DC Buck converter step down module - LM2526
- DS18B20 temperature sensor probe
- 128X32 LCD LED Display 0.91 (Replacing the original screen)

This would serve my needs and "hacking" the user control board meant a nicer finish.

# User Control board
I wasnt interested in re-using the circuitry on the board*. De-soldered, cut off, most of the components had to go. I only wanted the buttons and LEDs. I also wanted to keep the harness connector in place.

**I tried a few adhoc circuits but the existing board circuitry (and IC) would power up and I got voltages where I wasnt expected.*

The wiring harness was to stay intact but the color coding was change to suit my hacked mini circuit on the user control board. 

- Red = GND 	(yes, its backwards CAREFUL!)
- Black = +5v
- Yellow = button array
- White =  LCD SCL (TBC)
- Blue = LCD SDA (TBC)
- Brown = Green LED

I built a resister ladder for the 4 buttons. This means I only needed a single analog input to handle input from 4 different buttons. It was terminated to the yellow harness wire. The LED was wired to the brown harness wire and the screen was terminated on the blue and white harness wires.

![User_Control_Schematic](./images/UserControlSchematic.png?raw=true "schematic")

The end result was pretty rough but it let me continue with the main board design.



![UserControl Front](./images/UserControlFront.jpeg?raw=true "front")
![UserControl Back](./images/UserControlBack.jpeg?raw=true "back")



## Images


# Main Board
Here are the mainboard schematics. 

![MainBoard_Schematic](./images/MainBoardSchematic.png?raw=true "stepdown")
![MainBoard_Stepdown](./images/MainBoardStepdown.png?raw=true "stepdown")

# References

![Danfoss electrical interface](./images/danfos_motor_interface.jpeg?raw=true "interface")

Danfoss Diagram can be found here: https://www.keoghsmarine.com.au/image/catalog/101N0510_Diagram.jpg

