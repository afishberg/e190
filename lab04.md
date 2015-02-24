## Lab 04: Graphical Post-processing

### Introduction
In this lab I augmented the code provided in Nvidia's **postProcessGL.cu** example code. My augmentations enable the code to 
support several additional post-processing effects beyond the simple blur originally provided. Since this code was clearly
shipped before its coder had a chance to clean it up, these augmentations proved to be more challenging than one may expect.
Because of this, I teamed up with Andy Russell for part of this lab. 

Pictures corresponding with this lab report can be found [here](https://github.com/afishberg/e190/tree/master/lab04_pictures)!

### Design Methodology
Since this assignment revolved around modifying existing code, I followed a relatively straight forward methodology:
1.   Read original code and identify useful functions
2.   Clean up useful code and comment it so it is comprehensible
3.   Research possible augmentations
4.   Determine how to implement augmentations
5.   Improve code to support selected augmentations

Interestingly enough, I found several fascinating augmentations that operated by a convolution process. Thus, my primary
goal was to initially modify the code to perform its original functionality, a simple blur, now via a convolution matrix.
Its initial algorithm did operate a lot like a convolution matrix, only rather than multiplying each location by a matrix,
it simply summed all locations together and then divided by the number of pixels summed (an average). This same process can
be achieved with a square matrix of **n**x**n** where each field contained the value **1/n**.

After achieving this, I aimed to implement other matrices that would allow for other cool augmentations.

Currently my supported augmentations are:
*   Box Blur -- A post-processing effect that is similar to the original blur (only is a box instead of a circle)
*   Gaussian Blur -- A post-processing effect that uses a Gaussian, rather than a box, as the blurring mechanic
*   Edge Detection -- A post-processing effect that highlights the edges like a wireframe
*   Sharpen -- A post-processing effect that makes the image more "sharp"
*   Identity -- A post-processing effect that does not modify the picture (more of a proof of concept)

Identified Useful Functions:
*   process() (main.cpp) -- Calling function in main.cpp for all the post-processing
*   keyboard() (main.cpp) -- Function that handles keyboard input interpreting
*   launch_cudaprocess() (postProcessGL.cu) -- Function that calls cudaprocess() on the GPU
*   cudaprocess() (postProcessGL.cu) -- The only actual CUDA function (implements all the post-processing)


### Testing Methodology
Since this lab revolved around modifying existing code, my testing methodology was pretty rudimentary -- basically, I 
compiled my code a lot to ensure it was always working. This way, if I broke something, I knew immediately what I did to
cause the bug. It was challenging to make debugging any more sophisticated than this since I was unable to get printf()
calls working from within cudaprocess() since it ran on the GPU.

Additionally, since this code produces highly visual output, most debugging revolves around simply confirming that the
rendered images "look right."

Below are some examples of when the code malfunctioned and things did not "look right."


### Results and Discussion
Overall I am very happy with my augmentations. Although I have a lot of experience working with image processing libraries
like OpenCV and Dlib, I have very little experience actually writing any of the algorithms I often use. This lab proved
challenging because it had a steep conceptual curve on both the mathematics and CUDA fronts. That being said, I managed
to complete all the requirements and extras required for this lab. Additionally, I got an additional two CUDA augmentations
working beyond the two needed to satisfy the extra clause (totalling to 5 total augmentations).

Requirements:
- I augmented the functionality of the sample CUDA program to preform a box blur (rather than a circle blur)

Extras:
- I augmented the functionality of the sample CUDA program to preform a Gaussian blur
- I augmented the functionality of the sample CUDA program to preform edge detection
- I augmented the functionality of the sample CUDA program to preform a sharpen transformation
- I augmented the functionality of the sample CUDA program to preform a identity transformation

Pictures of these augmentations at work are provided below.


### Conclusions
I have learned a lot by modifying the sample Nvidia program. Specifically, I learned a lot more about image processing and
CUDA. I look forward to future assignments where I will be able to expand my usage of CUDA for entirely novel applications
rather than just modifying code to implement commonplace augmentations. That being said, this was a super valuable lab -- as
of now, I have learned the most new material from this E190U lab assignment.

Between reading the code, cleaning it up, researching augmentations, implementing code, and testing (as well as waiting
for CUDA to compile... it is surprisingly long) I easily spent 9 hours on this lab.

More pictures can be found [here](https://github.com/afishberg/e190/tree/master/lab04_pictures)!


### Source Code
At the moment, I have not pushed the source code. In accordance with the lab rules, I will push it tomorrow sometime after
everyone turns in their assignment.
