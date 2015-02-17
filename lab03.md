## Lab 03: Gameplay Testing

### Introduction
In this lab I modified the game engine for the open source game Lugaru to collect statistics about my controller
and different keymapping configurations for it. For more information about the controller's hardware or firmware please see
[Lab 01](https://github.com/afishberg/e190/blob/master/lab01.md) or [Lab 02](https://github.com/afishberg/e190/blob/master/lab02.md)
respectively. Additionally, I've pushed some new firmware code for this week adding several new features -- these changes
will be outlined later in the report.

Pictures corresponding with this lab report can be found [here](https://github.com/afishberg/e190/tree/master/lab03_pictures)!

### Design Methodology
The goal of this lab is to modify a game engine to non-intrusively gather statistics valuable for evaluating the effectiveness
of my controller. Thus, it was important to modify the game code for Lugaru while not disrupting 
the gameplay. I decided the best way to make this modification was to open a global ofstream, titled myfile, during the
initial call to the main function. Afterward, I added several informative blocks of file writes throughout the code.
I intentionally do not close the file at any point in the code since it will close automatically on program termination.
I do, however, ensure all file writes do eventually get written by calling flush() after each block of file writes.
The outfile is designed to be a valid **.csv** file. While the convenient **.csv** format does allow for easy editing and
analysis in spreadsheet applications, like Microsoft Excel, I personally wrote a simple Python script that calculates the
statistics of interest directly from the **.csv** file. I have included the code **here**, but please note this code is
written to work specifically on the data spit out from my modifactions -- it is not written to be flexiable code that
can be easily adapted to other datasets.

Currently the modified game engine provides the following information:
*   Timestamp -- In Unix Epoch time
*   How Much -- The quantity of damage being inflicted to a Person
*   Num Falls -- The number of times the player has fallen / been knocked down
*   Num Flip Fails -- The number of time the player has failed to properly do an aerial flip resulting in a fall
*   Num Seen -- The number of times enemies have witness the player sneaking
*   Num Sword Attack -- The number of times the player has swung a sword
*   Num Knife Attack -- The number of times the player has swung a knife
*   Num Unarmed Attack -- The number of times the player has swung his fists or feet
*   Num Escape -- The number of enemies the player has escaped from
*   Num Wall Flipped -- The number of wall flips the player has done
*   Num Throw Kill -- The number of kills the player has gotten with knife throws
*   Num After Kill -- The number of times the player hits an opponents corpse
*   Num Reversals -- The number of times the player reverses an opponents attack
*   Num Attacks -- The number of times the player attacks
*   Damage Dealt -- The amount of damage the player has inflicted to opponents
*   Damage Taken -- The amount of damage the player has received from opponents
*   Bonus -- The most recent bonus code (each number corresponds to a bonus type)
*   Bonus Value -- The quantity of bonus points awared for the most recent bonus
*   Bonus Total -- The total quantity of bonus points aquired by the player
*   Person -- The person who is taking damage (either user or other)

_Note: Although I am recording all of these, there are several I have not confirmed to be correctly tracked._

The statistics I am most interested in are:
*   Timestamp
*   Num Falls
*   Num Reversals
*   Num Attacks
*   Damage Dealt
*   Damage Taken
*   Bonus Total
*   Person

I will use these gathered data points for my analysis and to calculate other interesting data.

For this experiment, I designed two keymappings for my controller to use. Since Lugaru won't make good use of the Turbo
function I mapped to the switch, I modified the firmware to switch between these two mappings for these experiments.
Additionally, in preperation for my e-ink, I modified the firmware to output a players actions per minute (APM) to the 
serial output.



#### Modifications to the Game Engine

Below I outline the code I added to the Lugaru game engine in order to output my statistics. Luckily, by familiarizing
myself with Wolfire's well written yet pitifully commented code, I noticed a majority of the statistics I would was 
interested in were already tracked within the game and reset upon each level load.

Files Modified:
*   OpenGL_Windows.cpp
*   Person.cpp
*   GameTick.cpp

Other Noteworthy Files:
*   Globals.cpp
*   Constants.h


### Testing Methodology
To gather more statistics, I setup my Luguru in my dorm lounge and offered to let students play the game so I
could gather statistics from a variaty of gamers.

For each participant I asked them to...


### Results and Discussion
Overall I am very happy with my gathered data. My lab meets the requirements for this assignment plus it provides
a number of extra statistics, calculations, and users.

Requirements:
- I gathered at least two different measurable quantities on at two different controller firmwares

Extras:
- I gathered a total of **X** statistics
- I calculated an extra **X** statistics
- I tested my controller with **X** different participants in my dorm lounge
- I modified my controller firmware to provide another valuable statistic from the controller, APM

### Conclusions
I have learned a lot by modifying the Lugaru game engine. Specifically, I am very impressed how much of the game engine
I was able to understand despite Wolfire providing next to no comments within the code base.

Between modifying the game engine code, updating my controller firmware, and writing my statistics code, I easily spent
about 8 hours on this lab. Additionally, I spent probably another 2 hours experimenting with my new parts, although
I have yet to incorporate these parts onto the controller.

Looking forward to next week, I'm excited to see how my controller performs. That being said, I have a growing interest
in designing a real plastic version of this controller and will start looking into that soon.

More pictures can be found [here](https://github.com/afishberg/e190/tree/master/lab03_pictures)!

### Hardware Experiments
Over the course of this week, I have been experimenting with my Nintendo DS screens attempting to detect an x- and
y-coordinate. This is proving more challenging that I previously expected. Currently, I am able to detect when
the screen is touched by seeing a sudden jump in voltage, but I have not been able to find any way to use this
voltage jump to determine _where_ the screen was touched. I plan to examine this issue with Prof Spjut this week
to better understand what is going on.

![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab02_pictures/hardware_experiment.png "Experimental Hardware")
_The hardware I am currently experimenting with for future inclusion with my controller._

### Source Code
The current firmware code is hosted in this repo. A [link](https://github.com/afishberg/e190/blob/master/Controller/Controller.ino) to it can be found here.

This code is continuously updated, so it is possible at some point in the future, the current version of this code
may no longer reflect the exact version of the code refered to in this writeup.
