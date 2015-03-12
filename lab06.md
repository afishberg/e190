## Lab 06: Motion Capture Pong

### Introduction

As a continuation of last weeks lab, this week I continued working on a modified lab assignment dealing with puzzle games.
Unlike last week, however, I will not be working with the popular mobile app 
[Unblock Me](https://play.google.com/store/apps/details?id=com.kiragames.unblockmefree&hl=en) or the classic
1970s puzzle game [Rush Hour](http://en.wikipedia.org/wiki/Rush_Hour_%28board_game%29), but rather my own variant of
the puzzle, cleverly called Block Jam. This week, I created Block Jam from scratch using a Java library
called Processing (rather than PyGame). I also wrote several other tools and integrated my code from last week
so my game can solve and play itself if a second program (which uses the GPU) is called. Rather than linking into
the game data, the game is solved either via automated screenshots or external camera pictures.

For this lab, like last time, I deviated significantly from the suggested activity and created my own complex and
(in my opinion) extremely interesting variant. That being said, this required me to reinterpret parts of the assignment 
-- but that's okay given the open ended nature of these labs and encouragement to do extras. Specifically, while my lab 
does not make direct use of motion controls, its implementation shares many fundamental principals with the original
lab assignment (making this a valid and interesting substitution). In fact, one could even argue my application is 
significantly more complex than the proscribed task because I wrote an entire game from scratch, created a callable 
command line tool to automate mouse motions and clicks, wrote a puzzle solver that given a valid, solvable puzzle, it
guarentees a solution with the the minimum possible actions, and integrated and improved my lab code from last week
so the game can solve itself and then play itself to completion (via generated virtual mouse clicks).

Pictures corresponding with this lab report can be found [here](https://github.com/afishberg/e190/tree/master/lab06_pictures)!

### Design Methodology
Since this assignment requires me to implement a novel game, novel command line tools, and modify my code from last week,
my design process was a lot more exploratory than prior labs (even moreso than last week). Specifically, I followed
these step:

1.   Research the Processing library
2.   Gather the required resources *(public domain textures provided by [Pixabay](http://pixabay.com/))*
3.   Write a working version of Block Jam
4.   Modify last week's code to recognize Block Jam graphics 
5.   Output board state as a world string
6.   Write a command line tool that allows virtual mouse movement and clicks
7.   Use world string to generate solution string
8.   Pass solution string into parser that calls the command line tool so that it clicks in the correct places to solve
the puzzle

#### Block Jam
After doing some research, I felt comfortable enough with Processing to start coding my game. That being said, since
I was taking the time to write this from scratch, I didn't want to make the game too easy to image process.
To make it more challenging to image process I first searched for varied public domain texture images I could use for
my background and blocks. After searching around for a while, I decided upon the following textures:

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/original_textures/original_nebula.jpg" width="500">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/original_textures/original_cloth.jpg" width="312">

*The textures used for the background and blocks respectively.*

I then made it so each time you launch the game, a random window of the texture is sampled for each type of block.
This means that the blocks do not have a consistent image. Additionally, I made the player's block texutre from the
horizontal texture and kept the coloration only to a very slight tint. This means the short horizontal block and the
player's red block only differ consistently by a slight tinting and differ unpredictable in texture -- differentiating 
these blocks required a special solution I will discuss later.

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/block_jam/block_jam1.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/block_jam/block_jam2.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/block_jam/block_jam3.png" width="250">

*Three instances of Block Jam. Notice how each instance has a different texture on each type of block.*

Since I am relatively unfamiliar with Processing game design, making this game, debugging it, and having it look
professional took a substancial amount of time (~10hrs). The game is currently functional and playable. It also
serves its purpose for this class and interfaces well with the image processing and other lab-specific code.
That being said, I enjoyed writing this game and plan to bring it to professional completion at some point in the
near future. Because of this I have hosted this game code in a seperate repository, titled
[block_jam](https://github.com/afishberg/block_jam), so I can continue working developing it outside of this class.

#### Last Week's Image Processing Code

Modifying last weeks code took a non-trivial amount of time as well. This is because I intensionally made Block Jam's
blocks more challenging to identify and differentiate. Because of this, I needed to drastically reduce the similarity
threshold to account for the variance in block textures but this led to more problems -- specifically blocks begans
to get frequently confused, especially the player's red block and the short horizontal blocks. To rectify this, I needed
to modify the template matching to do matching on different color channels. Last week, my code simply converted the 
image and template to grayscale and processed it -- here that wasn't sufficient. Ultimately, I ended up:
-   Searching for the board in grayscale
-   Searching for the player's red block in the red channel (to greatly differentiate it from the short horizontal blocks)
-   Searching for the remaining blocks in the blue channel

Thus, by template matching like this, I managed to reestablish reliable identification in both screenshots and
camera pictures. That being said, although the picture identification does work again, I will not be using that explicitly
this week. Since I want the mouse to control itself, I need a better relative understanding of where the individual
pixels are within the monitor, where the mouse is, etc. (something that is much easier via screenshot). Although it is
possible to do this via camera, it is unnecessary complex this particular assignment (perhaps a final project?).

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/boxed_b.png" width="400">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/heatmap_b.png" width="284">

*Detecting the board on the screenshot.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/boxed_p.png" width="400">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/heatmap_p.png" width="368">

*Detecting the player's red block on the screenshot.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/boxed_x2.png" width="400">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/heatmap_x2.png" width="368">

*Detecting the short horizontal block on the screenshot.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/boxed_x3.png" width="400">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/heatmap_x3.png" width="351">

*Detecting the long horizontal block on the screenshot.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/boxed_y2.png" width="400">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/heatmap_y2.png" width="385">

*Detecting the short vertical block on the screenshot.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/boxed_y3.png" width="400">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/screenshot/heatmap_y3.png" width="385">

*Detecting the long vertical block on the screenshot.*



<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/boxed_b.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/heatmap_b.png" width="79">

*Detecting the board on the photograph.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/boxed_p.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/heatmap_p.png" width="203">

*Detecting the player's red block on the photograph.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/boxed_x2.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/heatmap_x2.png" width="203">

*Detecting the short horizontal block on the photograph.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/boxed_x3.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/heatmap_x3.png" width="178">

*Detecting the long horizontal block on the photograph.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/boxed_y2.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/heatmap_y2.png" width="228">

*Detecting the short vertical block on the photograph.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/boxed_y3.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/debug_images/photograph/heatmap_y3.png" width="228">

*Detecting the long vertical block on the photograph.*

That being said, since this is a modified version of last weeks code, it still uses the GPU and OpenCV (as required). Also,
since it successfully identifies the where the pieces are, it is able to output a world string such as
 "x__Yy_X_____p___y_y_x_____yx__x_____".

#### Puzzle Solver
Originally, since this puzzle solver is best approached as a non-trivial dynamic programming problem, I wrote this program
in Java. This is because I am more familiar with Java's standard library than C++'s STL. Additionally, since this program
can be a little tricky to debug, I felt I could achieve a functional program must faster using Eclipse's wonderful Java
debugging tools. Basically, this program works as a black box that takes a valid solvable world string
and returns a sequence of comma seperated world strings that represent states of the world as it undergoes its 
transformations (moves). For instance:

     $ ./solver x__Yy_X_____p___y_y_x_____yx__x_____
     x__Yy_X_____p___y_y_x_____yx__x_____,x__Yy_X______p__y_y_x_____yx__x_____,x__Yy_X______p__y_y_x_____y_x_x_____,x__Yy_X______p__y_yx______y_x_x_____,x___y_X______p_Yy_yx______y_x_x_____,x___y__X_____p_Yy_yx______y_x_x_____,x___y_yX_____p_Yy__x______y_x_x_____,x___y_yX_____p_Yy_x_______y_x_x_____,x___y_yX_____p_Yy_x_y_______x_x_____,x___y_yX_____p_Yy_x_y_______x____x__,x___y_yX_____p_Yy_x_______y_x____x__,x___y_yX_____p_Yy__x______y_x____x__,x___y__X_____p_Yy__x____y_y_x____x__,x___y__X____p__Yy__x____y_y_x____x__,x___y__X____p__Yy_x_____y_y_x____x__,x___y_X_____p__Yy_x_____y_y_x____x__,x___y_X__Y__p___y_x_____y_y_x____x__,x___y_X__Y__p_y_y_x_____y___x____x__,x___y_X__Y__p_y_y_x_____y___x__x____,x___y_X__Y__p_y_y_x_____yx_____x____,x___y_X_____p_y_y_x__Y__yx_____x____,x___y_X_____p_y___x__Y__yx__y__x____,x_____X_____p_y_y_x__Y__yx__y__x____,____x_X_____p_y_y_x__Y__yx__y__x____,____x____X__p_y_y_x__Y__yx__y__x____,__y_x____X__p___y_x__Y__yx__y__x____,__y_x____X___p__y_x__Y__yx__y__x____,__y_x____X___p__y__x_Y__yx__y__x____,y_y_x____X___p__y__x_Y___x__y__x____,y_y_x____X___p__y_x__Y___x__y__x____,y_y_x____X__p___y_x__Y___x__y__x____,y_y_x____X__p___y_x__Y__x___y__x____,y___x____X__p___y_x_yY__x___y__x____,y___x__X____p___y_x_yY__x___y__x____,y_x____X____p___y_x_yY__x___y__x____,y_x_y__X____p_____x_yY__x___y__x____,y_x_y__X________p_x_yY__x___y__x____

Alternatively, for debugging purposes, I also wrote a way to display it in a more "visual-friendly" text form.

    INPUT:
    ------+
    xO_Yy_|
    XOOOO_|
    pO_Oy_|
    y_xOO_|
    O_yxO_|
    xOO___|
    ------+
    
    SOLUTION:
    ======
    ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+
    xO_Yy_|xO_Yy_|xO_Yy_|xO_Yy_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO__y_|xO____|____xO|____xO|__y_xO|__y_xO|__y_xO|y_y_xO|y_y_xO|y_y_xO|y_y_xO|y___xO|y___xO|y_xO__|y_xOy_|y_xOy_|
    XOOOO_|XOOOO_|XOOOO_|XOOOO_|XOO_O_|_XOOO_|yXOOO_|yXOOO_|yXOOO_|yXOOO_|yXOOO_|yXOOO_|_XOOO_|_XOOO_|_XOOO_|XOO_O_|XOOYO_|XOOYO_|XOOYO_|XOOYO_|XOO_O_|XOO_O_|XOO___|XOO___|___XOO|__OXOO|__OXOO|__OXOO|O_OXOO|O_OXOO|O_OXOO|O_OXOO|O__XOO|OXOO__|OXOO__|OXOOO_|OXOOO_|
    pO_Oy_|_pOOy_|_pOOy_|_pOOy_|_pOYy_|_pOYy_|OpOYy_|OpOYy_|OpOYy_|OpOYy_|OpOYy_|OpOYy_|_pOYy_|pO_Yy_|pO_Yy_|pO_Yy_|pO_Oy_|pOyOy_|pOyOy_|pOyOy_|pOy_y_|pOy___|pOy_y_|pOy_y_|pOy_y_|pO__y_|_pO_y_|_pO_y_|_pO_y_|_pO_y_|pO__y_|pO__y_|pO__y_|pO__y_|pO__y_|pO____|____pO|
    y_xOO_|y_xOO_|y_xOO_|yxO_O_|yxOOO_|yxOOO_|_xOOO_|xO_OO_|xOyOO_|xOyOO_|xO_OO_|_xOOO_|_xOOO_|_xOOO_|xO_OO_|xO_OO_|xO_OO_|xOOOO_|xOOOO_|xOOOO_|xOOYO_|xOOY__|xOOYO_|xOOYO_|xOOYO_|xO_YO_|xO_YO_|_xOYO_|_xOYO_|xO_YO_|xO_YO_|xO_YO_|xOyYO_|xOyYO_|xOyYO_|xOyY__|xOyY__|
    O_yxO_|O_yxO_|O_y_xO|O_y_xO|O_yOxO|O_yOxO|__yOxO|__yOxO|__OOxO|__OOxO|__yOxO|__yOxO|y_yOxO|y_yOxO|y_yOxO|y_yOxO|y_y_xO|y___xO|y___xO|yxO___|yxOO__|yxOOy_|yxOOy_|yxOOy_|yxOOy_|yxOOy_|yxOOy_|yxOOy_|_xOOy_|_xOOy_|_xOOy_|xO_Oy_|xOOOy_|xOOOy_|xOOOy_|xOOOy_|xOOOy_|
    xOO___|xOO___|xOO___|xOO___|xOO___|xOO___|xOO___|xOO___|xO____|___xO_|__OxO_|__OxO_|O_OxO_|O_OxO_|O_OxO_|O_OxO_|O_OxO_|O__xO_|OxO___|OxO___|OxOO__|OxOOO_|OxOOO_|OxOOO_|OxOOO_|OxOOO_|OxOOO_|OxOOO_|_xOOO_|_xOOO_|_xOOO_|_xOOO_|_xOOO_|_xOOO_|_xOOO_|_xOOO_|_xOOO_|
    ------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+------+

I have since wrote a C++ implementation and incorperated some CUDA (although there is currently a CUDA bug I
have not been able to fully locate). The idea is, since each state is memoryless, each state can be evaluated
independently for all its possible valid transformations concurrently. To prevent infinite loops and rechecking
the same world strings, you wouldn't want to process an entire tier of moves without waiting to check them against a
Set or Map. In other words, you want to restrict yourself to calculating only the unique board states you can first achieve
after one move, then the unique board states you can first achieve after two moves, etc. This also ensures you will
find a solution that is the minimum possible moves.

#### Move Interpreter
A simple program that reads in the output of the puzzle solver and, using the location of the board determined from the
image processing, calls the virtual mouse command line tool where needed to execute the solution.

#### Virtual Mouse Command Line Tool
Although there is certainly a way to do this in C++, I know from past experience that the Java standard library has a
very convenient class called **java.awt.Robot** that makes virtual mouse movements, virtual keystrokes, and virtual clicks
extremely easy. Thus, rather than learn how to do this in C++ (where it is undobutingly more challening) I made a simple 
command line tool that interfaces cleanly with any program that can call a program with arguments. This program has three
possible commands.
- m x y: moves the mouse to position (x,y) where x and y are integer-strings
- p: presses the left mouse button
- r: releases the left mouse button


### Testing Methodology
Since I was building this system from the ground up, I built it in a very module way. This has a few advantages,
most notably it allows for easier debugging. When something goes wrong, it is pretty apparent what tool is failing so the
issue can be addressed quickly.

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/diagrams/system_architecture.png">

*Diagram of the system architecture and how the individual tools link.*

For instance, at one point the system was not registering all the clicks. I knew the clicker worked because I had
tested that component individually. I also knew the data that was being fed into the Move Interpreter was correct.
This meant that the issue had to be in the Move Interpreter. After a little examination, I realized I should have
some sleeps in between the individual mouse commands so the game had a chance to react to the clicks.

Similar to last lab, I also used a lot of print statements and two types of debugging images, a heatmap and a
boxed image showing where blocks were detected. A heatmap is a grayscale image where black represents no match
and white represents a strong match (the more white, the more strong of a match). A boxed image just drew a green box around
the block it detected. The combination of these images allowed me to manually tune my thresholds to detect the blocks
(and only those blocks) I wanted to detect.

Since even the screenshots for Block Jam had variance, I found a threshold of .5 was needed for the board and .7 was needed
for the individual pieces. Similarly, the photographs needed a .3 threshold for the board and a .41 threshold for the
individual pieces. Additionally, testing showed the photograph was much more finnicky for Block Jam -- presumably because
of the variance of the blocks.


### Used Templates

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/templates/b.png" width="250">

*The template of the board.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/templates/p.png" width="108">

*The template of the red player piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/templates/x2.png" width="108">

*The template of the short horizontal piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/templates/x3.png" width="165">

*The template of the long horizontal piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/templates/y2.png" width="51">

*The template of the short vertical piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/templates/y3.png" width="51"></img>

*The template of the long vertical piece.*


### Results and Discussion
Overall I am very happy with my results for this lab assignment. Since last week, I've managed to write a respectable
game from scratch, build a complex image processing program, and build an entire system that serves some cool (although
not terribly useful) purpose. Although the image processing made use of the GPU, I am upset I wasn't able to completely
debug the CUDA issues with the dynamic programming aspect. I need to learn some of the CUDA debugging tools, especially
if I am looking to do a CUDA intense final project.

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab06_pictures/block_jam/block_jam_solved.png" width="250"></img>

*The board after being autosolved by my system.*

Since the design, testing, and results often informed each other throughout this design process, I've already shared
a majority of my results in the previous sections. Overall though, it worked! I was able to put a game of Block Jam up
on my monitor, and the computer was able to automatically take a screenshot and play the puzzle through to completion.

Requirements:
- Pong game functioning with motion controls **(original)**
- Block Jam plays to via visual analysis **(my version)**
   - Uses image processing to play the game

Extras:
- Wrote an entire visually appealing puzzle game from scratch
- Wrote a dynamic programming puzzle solver
   - Java
   - C++
   - CUDA (there's a bug)
- Puzzle solver guarentees to take the minimum amount of moves
- Wrote a tool for taking automated screenshots
- Wrote a tool for virtual mouse control

### Conclusions
I have learned a lot by implementing this code and building this system. While it is true I deviated from the 
prescribed lab drastically, I still touched on all the major points and, in the end, learned a ton of software related thing.
Furthermore, I created a full working project that serves a purpose, even if it is in a strange roundabout way. This was 
a super valuable lab which allowed me a great amount of creative freedom. As a result, I believe my lab not only shows a
firm grasp of the current material, but a novel and cool way of putting these skills to use.

Between researching how to write certain code, writing the code, cleaning it up, testing it, tweaking parameters, 
and writing up this lab, I easily spent 22+ hours on this lab (not counting last week). I know that is an absurd amount
of time for these labs, but I did this of my own will with the goal of learning a lot -- and I did!

More pictures can be found [here](https://github.com/afishberg/e190/tree/master/lab06_pictures)!

### Source Code
At the moment, I have not pushed the source code. In accordance with the lab rules, I will push it sometime after
everyone turns in their assignment.

### Legal Notes
The intellectual content and images of
[Unblock Me](https://play.google.com/store/apps/details?id=com.kiragames.unblockmefree&hl=en) belong to their respective
owner(s) and [Kira Games](http://www.kiragames.com/). The preceding links lead to their Android App and company website
respectively. Please show your support for their product. I am merely using their content under Fair Use as a subject
for my research and highly recommend it to all bored puzzle lovers.
