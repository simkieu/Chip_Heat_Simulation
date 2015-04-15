/*
 * serialcode3D.c
 *
 *  Created on: Nov 11, 2014
 *      Author: Yuanzheng
 */


#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//macros
#define DEBUG 0
#define OUTPUT 0
#define HIGHT 40
#define WIDTH 200
#define LENTH 200

#define MAX_ITERATION 1000
#define MAX_DELTA_TEMP 0.001

//global variables
double T[LENTH][WIDTH][HIGHT];
double T_old[LENTH][WIDTH][HIGHT];

void Initialization();
void SetBoundary();
double MaxFunc(double a, double b);//get max of two double
int main(){
	int i,j,k;
	int iter;
	//temperature difference of current time and previous time
	double deltaT;

	//to evaluate program performance
	clock_t begin, end;
	double duration_time;


	iter = 1;
	deltaT = 1000;//initially set deltaT to a large number


	//begin simulation, clock begins
	printf("Simulation begins, serial code version \n\n");
	begin = clock();

	Initialization();
	SetBoundary();

	//initialize T_old equal to T
	for (i = 0; i < LENTH; ++i) {
			for (j = 0; j < WIDTH; ++j) {
				for (k = 0; k < HIGHT; ++k) {
					T_old[i][j][k] = T[i][j][k];
				}
			}
		}


	//heat dissipation process
	while(iter < MAX_ITERATION && deltaT > MAX_DELTA_TEMP){
		//loop through all the nodes, note i,j,k start from 1, ends to MAX-1
		for (i = 1; i < LENTH-1; ++i) {
				for (j = 1; j < WIDTH-1; ++j) {
					for (k = 1; k < HIGHT-1; ++k) {
						T[i][j][k] = 1.0/6 *(T_old[i-1][j][k] + T_old[i+1][j][k]
											+T_old[i][j-1][k] + T_old[i][j+1][k]
											+T_old[i][j][k-1] + T_old[i][j][k+1]);
					}
				}
			}

		//reset deltaT to minimal value
		deltaT = 0.0;
		for (i = 1; i < LENTH-1; ++i) {
				for (j = 1; j < WIDTH-1; ++j) {
					for (k = 1; k < HIGHT-1; ++k) {
						deltaT = MaxFunc(deltaT, fabs(T[i][j][k]-T_old[i][j][k]));
						T_old[i][j][k] = T[i][j][k];
					}
				}
			}

#if DEBUG == 1
		//Debug: print out temperature of vertical center line T[LENTH/2][WIDTH/2][k]

		if(iter % 100 == 0){
			printf("------------Iteration: %d-----------\n",iter);
			printf("Temperature of vertical center line:\n");
			for (k = 0; k < HIGHT; ++k) {
					printf("T[%d,%d,%d] = %.5f\n",LENTH/2,WIDTH/2,k,T[LENTH/2][WIDTH/2][k]);
				}
		}
#endif


		////////////////////////////////Output to file /////////////////////////////////////

#if OUTPUT ==1
		//print out temperature values every 100 time steps to see instantaneous temperature map
		FILE *ofp;

		//construct filename for output data, in the form of "Temperature200.dat", for instance
		char filename[20];

		if(iter % 100 == 0){
			sprintf(filename,"Temperature%d.txt",iter);
			if( (ofp = fopen(filename,"w")) == NULL){
				fprintf(stderr,"Could not open file to write data\n");
				exit(1);
			}

			//loop through all nodes to write temperature to file
			for (i = 0; i < LENTH; ++i) {
				for (j = 0; j < WIDTH; ++j) {
					for (k = 0; k < HIGHT; ++k) {
						fprintf(ofp,"%d,%d,%d %f\n",i,j,k,T[i][j][k]);
					}
				}
			}

		}
#endif

		iter ++;
	}


	///////////////////////////////// Print final temperature map to console ////////////////////////////


	//print out final temperature map
	printf("------------Iteration: %d-----------\n",iter);
	printf("Temperature of vertical center line:\n");
	for (k = 0; k < HIGHT; ++k) {
			printf("T[%d,%d,%d] = %.5f\n",LENTH/2,WIDTH/2,k,T[LENTH/2][WIDTH/2][k]);
		}

	//end of simulation, clock ends
	end = clock();
	duration_time = (double)(end - begin)/CLOCKS_PER_SEC;



	//print out statistics for duration time
	printf("Simulation ends.\nTotol running time is %f seconds\n",duration_time);
	return 0;
}


void Initialization(){
	int i,j,k;
	for (i = 0; i < LENTH; ++i) {
		for (j = 0; j < WIDTH; ++j) {
			for (k = 0; k < HIGHT; ++k) {
				T[i][j][k] = 0.0;
			}
		}
	}
}


//Can be modified
void SetBoundary(){
	int i,j;
	for (i = LENTH/4; i < 3*LENTH/4; ++i) {
		for (j = WIDTH/4; j < 3*WIDTH/4; ++j) {
			T[i][j][0] = 1000.0;
			}
	}
}


double MaxFunc(double a, double b){
	if(a>=b) return a;
	else return b;
}
