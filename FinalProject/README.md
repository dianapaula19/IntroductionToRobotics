# CANDY CLAW MACHINE ARCADE GAME
#### For our final project in the "Introduction To Robotics" course, we decided to create a candy claw machine, because we considered it to be a pretty "sweet" idea.

## DEMO VIDEO
... to be inserted

## THE RESEARCH
We made a lot of research beforehand and watched a tons of youtube tutorials in order to create this machine. 

- the movement of the claw along the axes was inspired from the following tutorial: http://bit.do/clawMovementXYZ, however instead of cardboard we used hobbyglas and instead of the elastic band we used a nylon wire.

The improvement we brought to all of these tutorials was adding two nrf24l01 tranceivers that reduces substantially the number of wires. There's a transmitter at the base of the machine that sends data to the motors found on the top of the machine. 

## HARDWARE 
- 4 N20 dc motors
- 1 SG90 servo motor
- L293D driver shield for 4 motors
- 2 arduino Mega 2560
- 2 HC-SR04 Ultrasonics :radio_button: :radio_button: 
- 2 9 V batteries
- 2 joysticks 🕹️
- 1 pushbutton
- 1 16/2 lcd
- 2 nrf24l01 transceivers 
- **LOTS** of wires
- legos 🧱
- hobbyglas and transparent plexiglass
- plastic tubes
- nylon wire
- superglue
- ~~the blood of our enemies~~

Link to the BOM: http://bit.do/clawMachineBOM

## HOW TO PLAY

1. In order to start playing the game, you need to insert a coin. After the completion of this simple task, all you need to do is to switch to the console and press the start button.   
2. The claw is controlled by two joysticks. One of the them controls the movement on the X and Y axes, while the other one control the movement on the Z axis. Also, pressing the button of the latter joystick open and closes the claw, allowing you to grab that candy.
3. You have exactly three minutes to grab a prize, after that the game is over and you need to insert another coin to start again. 

We also made a pretty cool guide to this game: http://bit.do/clawMachineGuide


