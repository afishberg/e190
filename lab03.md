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
statistics of interest directly from the **.csv** file. I have included the code and collected data [here](https://github.com/afishberg/e190/tree/master/lab03_data). Please note this code is
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

For this experiment, I designed two keymappings for my controller to use. Since Lugaru won't make good use of the Turbo
function I mapped to the switch last week, I now modified the firmware to use the switch to swap between these two unique mappings.

The two controller keybindings I tested for this experiment are:
![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/keybindings1.png "Keybindings when switch is to the left")
![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/keybindings2.png "Keybindings when switch is to the right")



#### Modifications to the Game Engine

Below I outline the code I added to the Lugaru game engine in order to output my statistics. Luckily, by familiarizing
myself with Wolfire's well written yet pitifully commented code, I noticed a majority of the statistics I would was 
interested in were already tracked within the game and reset upon each level load.

Files Modified:
*   OpenGL_Windows.cpp
*   Person.cpp
*   GameTick.cpp
   
![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/opengl_windows.png "Code modifications in main()")

*Code added within OpenGL_Windows.cpp's main() function -- this code opens the output file and sets up the top of the __.csv__*


![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/person.png "Code modifications in DoDamage()")

*Code added within Person.cpp's DoDamage() function -- this code prints updated data everytime a character takes damage*


![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/gametick.png "Code modifications in LoadLevel()")

*Code added within GameTick.cpp's LoadLevel() function -- this code prints out the time and a message so the log can tell when a new level is started*

Other Noteworthy Files:
*   Globals.cpp
*   Constants.h

![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/globals.png "The variables that store the valuable statistics")

*Shows the global variables that store the valuable statistics I am collecting -- these variables are extern'd into most other files*


![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/constants.png "The integer values that represent the bonuses")

*Shows the integer values that correspond to the various types of bonuses you can get*

### Testing Methodology
To gather more statistics, I setup my Luguru in my dorm lounge and offered to let students play the game so I
could gather statistics from a variaty of gamers.

For each participant I asked them to complete the first three challenge levels on easiest game setting with each contoller keybindings -- this makes a minimum of 6 full games of Lugaru. Many players lost on at least one of the levels, however, forcing them to replay the stage. I personally logged what levels the players failed on so I could later identify which records in the log files corresponded to which stage on which controller keybindings.

I wrote a Python Script that consolidated each matches data points into a single row of data. Each rows has the following fields.

*   Seconds -- Duration of the stage
*   Falls -- Number of times the player was knocked down
*   Reversals -- Number of times the player reversed an enemy's attack
*   Damage Dealt -- Damage points inflicted
*   Damaged Taken -- Damage points taken
*   Score -- Amount of points awarded for the match
*   Times Hit -- Number of times damage was applied to the player
*   Times Hit Enemies -- Number of times damage was applied to the enemies

*Note: The values for Times Hit and Times Hit Enemies appears very high because damage is often applied from physics injuries are applied with lots of little values*

From here, the data was taken into Excel and analyzed. The analyzed data was used to make Graphics that will be discussed in the next session. Additionally I asked each participant which keybindings felt better to them.


### Results and Discussion
After all the raw data was collected it was analyzed using the following steps:

1.   Lugaru output **.csv** files. Files were renamed to include the gamer's name. All files were named of the form **statistics_X.csv**.
2.   I ran my Python Script on each **.csv** file. This script condenses and simplified all the data points for a given stage into a single row as well as only keeping only the most interesting columns. This script outputs these rows as a **.csv** file. These files are named of the form **X_out.csv**).
3.   The data from each of the comdensed files was pasted into a an Excel file called  **combined_data.xlsx**. This file shows all the data together as well as the gamer's name, the stage they played, and the keybindings they used. The data was then sorted by which Keybindings they used.
4.   The Excel file **combined_data.xlsx** was split into two smaller files: **keybindings1.xlsx** and **keybindings2.xlsx**. These files each only contain the stages played with their respective keybindings. The appropriate columns of data were then averaged.
5.   The Excel files **keybindings1.xlsx** and **keybindings2.xlsx** were simplified to **keybindings1_best.xlsx** and **keybindings2_best.xlsx**. These files kept only the three trials for each player where the successfully beat the level. The appropriate columns of data were then averaged.
6.  The average values of the best trials for **keybindings1_best.xlsx** and **keybindings2_best.xlsx** were then copy/pasted into a final **.xlsx** file, **graphics.xlsx**. The table was made more aesthetically appealling and then two graphics were made.
7.  Graphics were then analyzed for results.
  

![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/table.png "The table of average values of each participant's successful trial at each level")

*Numerically shows the values obtained from averaging each participant's successful trial at each level*


![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/bar.png "A bar graph showing the average values compared to each other")

*A comparing bar graph showing the average values from each participant's successful trial with each keybindings*


![alt text](https://raw.githubusercontent.com/afishberg/e190/master/lab03_pictures/weightedbar.png "A weighted bar graph showing the average values compared to each other")

*A more readable version of the previous bar graph because it shows the compared values in proportion to each other*


By examining these graphics, especially the last one we see which keybindings have the more desirable statistics:
*   Seconds: Less time is better; means gamer completed level faster -- **Keybindings 1**
*   Falls: Less falls is better; means gamer got knocked over fewer times -- **Keybindings 1**
*   Reversals: More is better; means gamer countered more attacks -- **Keybindings 1**
*   Attacks: More is better; means gamer had more successful strikes -- **Keybindings 1**
*   DmgDealt: More is better; means gamer dealt more powerful blows to enemies -- **Keybindings 1**
*   DmgTaken: Less is better; means gamer took less devistating hits -- **Keybindings 1**
*   Score: More is better; means gamer earned more points -- **Keybindings 1**
*   Times Hit: Less is better; means gamer had less instances of damage applied to his character -- **Keybindings 2**
*   Times Hit Enemies: More is better; means gamer had more instances of damage applied to his enemies -- **Keybindings 2**

When examining this data, it seems that Keybindings 1 enabled gamers for significantly better results. Especially because the only two values Keybindings 2 outpreformed Keybindings 1, Times Hit and Times Hit Enemies, are actually less important than their DmgDealt and DmgTaken counterparts. Times Hit and Times Hit Enemies are simply the number of instance of damage applied (a majority of these coming from ragdoll physics damage), not how much.

When asking players what they thought of the two keybindings most expressed the following:
* Keybindings 1 -- Pressing Crouch is challenging on the Joystick
* Keybindings 2 -- Attack is better on a trigger so you don't need to remove a finger from the right joystick


Overall I am very happy with my gathered data. My lab meets the requirements for this assignment plus it provides
a number of extra statistics, calculations, and participants.

Requirements:
- I gathered at least two different measurable quantities on at two different controller firmwares

Extras:
- I gathered a total of **21** statistics
- I made explicit use of **9** average statistics
- I used my stats to make a informative graphics which I used to determine which layout was favorable
- I tested my controller with **4** different participants -- that weren't me -- in my dorm lounge
   - Each participant completed the first three challenges with each controller binding
   - Some players needed to retry levels
- I modified my controller firmware to switch between keybindings without reprogramming the controller

### Conclusions
I have learned a lot by modifying the Lugaru game engine. Specifically, I am very impressed how much of the game engine
I was able to understand despite Wolfire providing next to no comments within the code base.

Between modifying the game engine code, updating my controller firmware, and writing my statistics code, I easily spent
about 8 hours on this lab. Additionally, I spent probably another 2 hours experimenting with my new parts, although
I have yet to incorporate these parts onto the controller.

In the future, I would be interested in testing out another set of keybindings. Using the opinions of my testers, I would be interested in creating a hybrid binding. Most notably I would be interested in seeing the bumpers be Crouch and Attack and Jump would be Left button top. This allows players to not have to press the control stick while keeping attack as a bumper.

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

At the moment, I have not bothered to push the Lugaru code since it is a lot for only ~30 lines of new code (all of which are screencaptured above).
