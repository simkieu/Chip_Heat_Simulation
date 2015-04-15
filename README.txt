#Instruction

Tips on compiling and running the code:

1/ For compiling: serial code use "gcc SerialCode3D.c"; parallel code use "gcc ParallelCode3D.c -fopenmp"
note we used some primitives in parallel version that require OpenMP 3.1 which is available in GCC 4.7 and further versions. You could download from here:
https://gcc.gnu.org/mirrors.html

2/ For purely computation, we set two macros "DEBUG" and "OUTPUT" to 0 to see the performance of parallel code and compare it with serial version. If one need to get the txt files which 
contain all the data, set macro "OUTPUT" to 1.
