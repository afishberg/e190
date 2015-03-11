## Lab 05: Motion Detection

### Introduction

As of late, I've been thoroughly enjoying a puzzle game on my smartphone called
[Unblock Me](https://play.google.com/store/apps/details?id=com.kiragames.unblockmefree&hl=en) -- a variant of the classic
1970s puzzle game [Rush Hour](http://en.wikipedia.org/wiki/Rush_Hour_%28board_game%29). Between this game and some
external reading I've been doing on AI, I thought it would be interesting to make this lab (and next weeks) very
creative by incorporate this game into my assignment.

For this lab, I deviated significantly from the suggested activity and created my own complex and (in my opinion) extremely
interesting variant. That being said, this required me to reinterpret parts of the assignment -- but that's okay given
the open ended nature of these labs and encouragement to do extras. Specifically, while my lab does not make direct use of
hand movement detection, its implementation shares many fundamental principals with the original lab assignment
(making this a valid and interesting substitution). In fact, one could even argue my application is significantly more
complex than the proscribed task because my code detects multiple features simultaneously (rather than just a single hand)
and uses relative positional information to extracts data about the game's current board state.

To clarify: My ultimate goal for this lab and next lab is to directly detect the board state a Unblock Me-like puzzle
board via image processing, solve it, and have the solution execute on the game automatically.

Specifically: This lab deals with writing code to detect board state via image processing. This code works on both
a pixel perfect screenshot of Unblock Me and an image taken from an external camera/Playstation Eye/etc.

Pictures corresponding with this lab report can be found [here](https://github.com/afishberg/e190/tree/master/lab05_pictures)!

### Design Methodology
Since this assignment requires me to implement novel image processing code, my design process was a lot more exploratory
than prior labs. Specifically, I followed these step:

1.   Research image processing solutions
2.   Gather the required resources (screencaping and editing templates from Unblock Me)
3.   Write a functional implementation (for pixel perfect screenshot)
4.   Expand implementation to a camera (for picture variance)
5.   Output board state as a string

After doing some research, it appeared I wanted to use an image processing algorithm called 
[template matching](http://docs.opencv.org/doc/tutorials/imgproc/histograms/template_matching/template_matching.html). 
While there were many potential solutions, template matching seemed especially powerful since I knew the appearance 
of the blocks I wanted to detect.

In many ways template matching can be thought of in a similar way to the image processing kernel code I wrote last week.
In this case, however, rather than having a transformation matrix be your kernel, your kernel is another image (a template)
that you calculate a "difference factor" of at each valid pixel location. This way, by setting a threshold, you can detect
objects have a certain amount mathematical similarity to your template (in this case blocks). A template and the image
you are examining are usually only allowed to be a single channel, so there it is up to the coder to make many different
choices about how to examine the pair (convert to grayscale, look at a single color channel, etc.)

Since this lab requires use of the GPU, I was happy to find the OpenCV library has a GPU implementation of the template
matching function called [gpu::matchTemplate](http://docs.opencv.org/modules/gpu/doc/image_processing.html#gpu-matchtemplate).
Additionally, the OpenCV library has multiple different implementations of template matching that can be accessed by
passing a different ENUM value to the function -- specifically, for this assignment I always used TM_CCOEFF_NORMED.


### Testing Methodology
Since I was building this code from the ground up, it was important to have benchmarks for myself throughout my development
processes. Mostly, I managed this with a lot of print statements and two types of debugging images, a heatmap and a
boxed image showing where blocks were detected. A heatmap is a grayscale image where black represents no match
and white represents a strong match (the more white, the more strong of a match). A boxed image just drew a green box around
the block it detected. The combination of these images allowed me to manually tune my thresholds to detect the blocks
(and only those blocks) I wanted to detect.

In the end I found a .99 threshold to work for the screenshot and a .5 threshold for the board and .91 threshold for the
pieces in the photo.

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/input_images/screenshot.png" width="250">

*A pixel perfect screenshot of Unblock Me.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/screenshot/heatmap_p.png" width="250">

*A heatmap of the screenshot looking for the red player piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/screenshot/boxed_p.png" width="250">

*A boxed image of the screenshot showing where it detected the red player piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/error_images/boxed_x2.png" width="250">

*A mistake where the threshold was too low and extra incorrect pieces were detected (many overlapping).*

### Used Templates

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/templates/b.png" width="250">

*The template of the board.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/templates/p.png" width="108">

*The template of the red player piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/templates/x2.png" width="108">

*The template of the short horizontal piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/templates/x3.png" width="165">

*The template of the long horizontal piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/templates/y2.png" width="51">

*The template of the short vertical piece.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/templates/y3.png" width="51"></img>

*The template of the long vertical piece.*


### Results and Discussion
Overall I am very happy with my progress on my two week project. My code can successfully examine either a screenshot
or a picture and detect the blocks. In terms of accuracy, the pixel perfect screenshot always works and the picture works
if a given set of constraints are followed -- most notably decent lighting, head on picture, consistent distance. When these
constraints are met, it works. If for some reason, if it isn't however, the threshold const threshold values can be tweaked
slightly to fix the problem. So that means the detection works!

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/boxed_b.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/heatmap_b.png" width="125">

*Showing the program detecting the board in a photo and corresponding heatmap.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/boxed_p.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/heatmap_p.png" width="213">

*Showing the program detecting the red player piece in a photo and corresponding heatmap.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/boxed_x2.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/heatmap_x2.png" width="213">

*Showing the program detecting the short horizontal piece in a photo and corresponding heatmap.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/boxed_x3.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/heatmap_x3.png" width="193">

*Showing the program detecting the long horizontal piece in a photo and corresponding heatmap.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/boxed_y2.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/heatmap_y2.png" width="232">

*Showing the program detecting the short vertical piece in a photo and corresponding heatmap.*

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/boxed_y3.png" width="250">
<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/debug_output/photograph/heatmap_y3.png" width="232">

*Showing the program detecting the long vertical piece in a photo and corresponding heatmap.*

Additionally, my code needed to also output an accurate board state. To do this, first I needed to create a way
to represent a given board state. For simplicity in coding and parameter passing, I choose to represent a board
as a string. Since a board always consists of a 6x6 world, I defined a "world string" to be 36 characters long
and denotes the spaces in row-col order using only the following characters:
- '_' - an empty space
- 'p' - the players red piece
- 'x' - the short horizontal piece
- 'X' - the long horizontal piece
- 'y' - the short vertical piece
- 'Y' - the long vertical piece
- **Note: In my code I use a space rather than a '_' to represent a black space -- markdown's syntax makes this difficult
to type.**
- **Note: The letter only represents the upper-left most "square" of the block. This notation does not show where the other
parts of the block are (i.e. an empty space does not denote a valid space one can move to).**

After defining a representation, I needed to detect and output in this notation. To do this, I used the part where I detect
the entire board to figure out where I should be examining. From there, since my program assumes a constant distance, it can
figure out where the detected pieces are since it has a reference point of where the board stops.

To show this works the following board was correctly interpreted as "x__Yy_X_____p___y_y_x_____yx__x_____" (which is correct
for my notation).

<img src="https://raw.githubusercontent.com/afishberg/e190/master/lab05_pictures/input_images/photograph.png" width="250">

*The image used to detect the world string "x__Yy_X_____p___y_y_x_____yx__x_____"*

Requirements:
- CUDA/OpenCV detects hand movement **(original)**
- Use OpenCV to detect the game board **(my version)**
   - Works on pixel perfect screenshot
   - Works on photograph (give the constraints outlined above)

Extras:
- Detect different kinds of blocks
   - Detected the player red block
   - Detected short horizontal block
   - Detected long horizontal block
   - Detected short vertical block
   - Detected long vertical block
- Output useful debug images
   - Heatmap
   - Boxed images
- Output a correct world string given a picture

### Conclusions
I have learned a lot by implementing this code and look forward to expanding my progress next week to complete a 
variation of the Lab 06 assignment. This was a super valuable lab which allowed me a great amount of creative freedom.
As a result, I believe my lab not only shows a firm grasp of the current material, but a novel and cool way of putting
these skills to use.

Between research image processing, writing the code, cleaning it up, testing it, tweaking parameters, and writing up this
lab, I easily spent 14+ hours on this lab (with more to come next week).

More pictures can be found [here](https://github.com/afishberg/e190/tree/master/lab05_pictures)!

### Source Code
At the moment, I have not pushed the source code. In accordance with the lab rules, I will push it tomorrow sometime after
everyone turns in their assignment.

### Legal Notes
The intellectual content and images of
[Unblock Me](https://play.google.com/store/apps/details?id=com.kiragames.unblockmefree&hl=en) belong to their respective
owner(s) and [Kira Games](http://www.kiragames.com/). The preceding links lead to their Android App and company website
respectively. Please show your support for their product. I am merely using their content under Fair Use as a subject
for my research and highly recommend it to all bored puzzle lovers.
