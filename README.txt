The submitted Zip file contains:

1/ Final Report: Final Report.pdf
2/ Presentation slide: Project_HeatDissipation.pptx
3/ Source codes: SerialCode3D.c and ParallelCode3D.c
4/ Matlab code for displaying simulation: data_plot.m
5/ Video created from Matlab simulation: Heat Simulation.wmv
6/ Output data files created from the C code (height x width x length = 20x150x150): From Temperature100.txt to Temperature900.txt 
(You can create these text files by running one of the two C codes)
7/ README file: README.txt


Tips on compiling and running the code:
1/ For compiling: serial code use "gcc SerialCode3D.c"; parallel code use "gcc ParallelCode3D.c -fopenmp"
note we used some primitives in parallel version that require OpenMP 3.1 which is available in GCC 4.7 and further versions. You could download from here:
https://gcc.gnu.org/mirrors.html
2/ For purely computation, we set two macros "DEBUG" and "OUTPUT" to 0 to see the performance of parallel code and compare it with serial version. If one need to get the txt files which 
contain all the data, set macro "OUTPUT" to 1.