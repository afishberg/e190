## Lab 01: Build a Gamepad Controller

### Introduction
In this lab I built the hardware for a fully functional video game controller with the materials found within 
the E190U starter kit.
Next week, for Lab 02, I will write the software needed to use this device to play games on the computer.
I have also gone back and added attional extra features to my controller after getting several extra pieces of hardware
in the mail.

Pictures corresponding with this lab report can be found [here](https://github.com/afishberg/e190/tree/master/lab01_pictures)!

### Design Methodology
My controller uses equipment found within the E190U starter kit and external additional hardware.
A complete updated list of hardware as of 3/13/2015 is listed below.

#### Starter Kit Hardware

*   Arduino Micro
*   Tactile Switches (x6)
*   Joystick Potentiometer with Breakout Board (x2)
*   Switch
*   Arduino Mini-breadboard (x2)

##### Additional Extra Hardware

*   25,000 Ohm Potentiometer (x2)
*   Nintendo DS Touch Screen (x2)
*   Nintendo DS Breakout Board (x2)
*   SHARP Memory Display

#### Additional Materials
*   Electrical Tape
*   3M Scotch Heavy Duty Mounting Tape
*   Wood Screws (x4)
*   Sandpaper (grits used 40, 180, 240, 400)

#### Original Steps

1. Think of a design and draw it  -- in this case I sketched it (poorly) on a piece of printer paper (the two extra 
potentiometers and two breadboards are not shown in this drawing since they are on the back of the controller).
2. Obtain parts needed for design -- in this case, in addition to the E190U starter kit, I needed:
   - 25,000 Ohm Potentiometer (x2) -- obtained from the stock room
   - Nintendo DS Touch Screen ($9.95 x2) -- obtained from SparkFun, [link](https://www.sparkfun.com/products/8977)
   - Nintendo DS Breakout Board ($3.95 x2) -- obtained from SparkFun, [link](https://www.sparkfun.com/products/9170)
   - SHARP Memory Display ($39.95 x1) -- obtained from Adafruit, [link](http://www.adafruit.com/products/1393?gclid=CLOcmcWSxcMCFZKFaQodazIAxw)
   - Electrial Tape (Green) -- obtained from the stock room
   - 3M Scotch Heavy Duty Mounting Tape -- obtained from Target, however Amazon has it cheaper here, [link] (http://www.amazon.com/Scotch-Heavy-Duty-Mounting-Clear/dp/B00004Z4BU/ref=sr_1_5?ie=UTF8&qid=1422945238&sr=8-5&keywords=scotch+tape+outdoor+mounting)
   - Wood Screws -- obtained from the stock room
   - Sandpaper -- obtained from the stock room
3. Reshape the given controller stock -- the default controller stock included in the E190U starter kit was rough, unfinished,
and in an uncomfortable non-ergonomic shape. The following improvements were made to the stock:
   - Rough cut areas were initial smoothed down with the belt sander -- the belt sander could not safely sand the area between the two grips
   - Back side was rounded in several spots to fit in the hand better. These spots include:
      - Sides -- to fit better in the palm
      - Grips -- to allow fingers to wrap around easier
      - Corner -- the area between the grip and the body was rounded so the middle finger can sit snugly in position
4. Drill starter holes (with hand drill) for screwing in the joysticks
5. Sand the wood down by hand to give smooth comfortable feel -- final finish was given with 400 grit sandpaper
6. Screw in joysticks -- due to the position of the joysticks, screws can only be put in the two uppermost holes on the 
joystick (the other two actually hang below the wood)
7. Solder wires to the buttons
   - I color coded my wires using the following system:
      - Red: Power (5V)
      - Black: Ground
      - White: Button (connecting to input pin with a pull up resistor)
      - Green: Potentiometer -- if attached to joystick it is the x-axis
      - Blue: Potentiometer -- if attached to joystick it is the y-axis
8. Attach buttons and potentiometers via mounting tape -- the tape is strong enough to allow comfortable reliable gameplay
but is also removable. I used this tape intentionally (rather than the epoxy suggested by the lab) since I wanted to be
adjust the positions of buttons after testing and recieving the missing hardware.
9. Wire everything up -- I attached the following devices to the following pins:
   - Analog Pins
      - Pin A0: Left Joystick (x-axis)
      - Pin A1: Left Joystick (y-axis)
      - Pin A2: Right Joystick (x-axis)
      - Pin A3: Right Joystick (y-axis)
      - Pin A4: Left Potentiometer (when looked at from back)
      - Pin A5: Right Potentiometer (when looked at from back)
   - Digital Pins
      - Pin D2: Left Joystick (push)
      - Pin D3: Right Joystick (push)
      - Pin D4: Left Button (upper)
      - Pin D5: Left Button (lower)
      - Pin D6: Right Button (upper)
      - Pin D7: Right Button (lower)
      - Pin D8: Left Button (bumper)
      - Pin D9: Right Button (bumper)
      - Pin D10: Switch
   - Note: All buttons are designed to be at 5V until the are pressed and shorted to ground -- this is because the Arduino
   pins can be set to pull high in software without extra wiring
   
10. Test wiring -- all wiring was tested using the "buzz connectivity" feature on the Microprocessor Lab's multimeters
11. Make improvements when remaining parts come in (see extra steps).

#### Extra Steps

I have since received my extra parts and have further augmented my controller design. The additional augmentations include:
   - Nintendo DS Touchscreen
   - Nintendo DS Breakout Board (x2)
   - SHARP Memory Display

##### Nintendo DS Touchscreens
1. Solder pins onto the Nintendo DS Breakout Boards.
2. Attach the Nintendo DS Touchscreens to their Breakout Boards.
3. Use a second Arduino Micro (that I obtained elsewhere) to test how the Nintendo DS Touchscreens need to be wired. 
Specifically found the following Sparkfun Datapage very helpful,
[link](https://www.sparkfun.com/datasheets/LCD/HOW%20DOES%20IT%20WORK.pdf).
4. After comfortable with the hardware, wire into controller.
 
##### SHARP Memory Display
1. Solder pins onto the board (it came with breakout board-like holes).
2. Use a second Arduino Micro (that I obtained elsewhere) to test how the SHARP Memory Display needs to be wired.
3. After comfortable with the hardware, wire into controller.

### Testing Methodology
The device was tested several ways:

1. All connections were tested were tested using a multimeter -- specifically the "buzz connectivity" feature
2. All potentiometers had their resistance checked using a multimeter -- specifically the resitance measurement feature
3. All joysticks were tested to see if when pressed if they shorted to + or G (they shorted to G) using a multimeter -- specifically the "buzz connectivity" feature
4. All buttons and potentiometer had their positions tested for comfort -- specifically, since I used the Scotch Heavy Duty Mounting Tape,
I was able to move the buttons around to find the ideal location/distance (at least for my hands)

Further testing will be conducted next week when I begin to write software -- if I missed a bug somehow, it will be very obvious then!

The extra devices were tested with an extra Arduino Micro and Breakout board using seperate programs (sicne their
circuitry was less obvious than other components (like buttons).

### Results and Discussion
Overall I am very happy with my controller. In its current form it seems to be inspired by a combination of the PS2 controller, Nintendo DS, Wii U, rumors about the Valve Controller, and my own creativity.

This controler currently meets all basic requirements and many extras.

Requirements:
- Controller with 2 joysticks
- 4 buttons
- 1 switch

Extras:
- 2 extra buttons
- 2 extra potentiometer (on the back)
- 2 touch screens
- SHARP Memory Display

#### Original Pictures:

![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab01_pictures/finished_controller_front.jpg "Finished Controller (Front)")

![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab01_pictures/finished_controller_back.jpg "Finished Controller (Back)")

#### Augmentation Pictures

![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab01_pictures/updated_picture.jpg)

#### All Pictures

More pictures can be found [here](https://github.com/afishberg/e190/tree/master/lab01_pictures)!

### Conclusions
I have learned a lot by constructing this controller. Between planning, ordering parts, and construction, I easily spent over 14 hours on it thus far. 
After the extra parts came in, I easily spend another 8 hours testing the extra components and incorperating them with my
current controller design

Planned functionality:
- One potentiometer on the back will adjust sensitivity of the controller sticks (when they control the mouse)
- One potentiometer will control the key mappings (there will be 10 regions for different setups)
- The SHARP Memory Display will display the user's current  Actions Per Minute (APM)
- The Nintendo DS Touchscreens will be usable as an alternative mouse and key mapings
- The switch will be a turbo switch

Possible Future Improvements:
- Add trigger buttons (below the bumbers)
- Clean up the wiring -- when rewiring the buttons, adding the touch screens, and wiring in the SHARP Memory display, I may drill a hole through the face of the controller so I can run wires through the body of the controller. This would allow for shorter wires and easier access to the Arduino (which is on the back of the controller)
- Design and print a 3D printed plastic chassis

In closing, I think I would be very interested in taking this controller design to the next level later in the semester. I would
like to design a new version to be 3D printed out of plastic (using this version for inspiration). I actually think this controller
is very comfortable, unique, and powerful -- I might be onto something with this new unique design.

### Source Code
Since this lab was strictly the construction of the controller, there is no source code this week.
Next week I will write the Arduino code that will make the controller work.
