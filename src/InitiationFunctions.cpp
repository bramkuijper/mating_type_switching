#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include "Global.hpp"
#include "Functions.hpp"
#include "InitiationFunctions.hpp"


///////////////////////////////////
/////////Initiating matirces//////
/////////////////////////////////


//Initiate Nx2 matrix
void  InitiateX(int array[N][2], double initial_p){
	int i=0;
	
	for (i=0; i<(N/2-1); i++){
		array[i][0] = 0;
		array[i][1] = 0;
	}
	for (i=(N/2-1); i<N; i++){
		array[i][0] = 1;
		array[i][1] = 0;
	}
    //set initial p levels
    for(i=0; i<(N/2-1)*initial_p; i++) array[i][1] = 1;
    for(i=(1-initial_p/2)*N; i<N; i++) array[i][1] = 1;
	
}//InitiateX

void InitiateP(double mat[runs][2]){
	int i=0;
	
	for (i=0; i<runs; i++){
		mat[i][0] = 0.0;
		mat[i][1] = 0.0;
	}
}//InitiateP

void IntiatepTraj(double mat[runs][maxSteps]){
	int i =0;
	int j=0;
	
	for (i=0; i<runs; i++) 
		for (j=0; j<maxSteps; j++) 
			mat[i][j]=0.0;
}//InitiatepTraj