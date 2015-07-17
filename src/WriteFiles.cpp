#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include "Global.hpp"
#include "Functions.hpp"
#include "InitiationFunctions.hpp"
#include "WriteFiles.hpp"

//saving mycells.position file

//write pair stats file
void WritePfix(double array[runs][2], int index){
	char name[250];
		
	FILE *pfile=NULL;
	  
	sprintf(name, "Pfix_N%.d_g%.d_runs%.d_pswitch%.3f0_pintro%.3f_%.d.txt", N, g, runs, pswitch, p_initial, index);
	
	pfile = fopen(name, "w+");
		
	int i=0;
	for (i=0; i<runs; i++) fprintf(pfile, "%.5f0	%.5f0\n", array[i][0], array[i][1]);
	
	fclose(pfile);
}//WritePfix

//write pair stats file
void WriteP_trajectory(double array[maxSteps]){
	char name[250];
    
	FILE *pfile=NULL;
    
	sprintf(name, "p_traj_N%.d_g%.d_runs%.d_pswitch%.3f0.txt", N, g, runs, pswitch);
	
	pfile = fopen(name, "w+");
    
	int i=0;

    while(array[i]!=100){
        fprintf(pfile, "%.5f0\n", array[i]);
        i++;
    }
	
	fclose(pfile);
}//WritePfix


//save halflifes
void WriteHalflifes(int array[runs]){
//	char name[250];
//	
//	FILE *pfile=NULL;
  //  
//	sprintf(name, "BM-HL_N%.d_K%.d_RUNS%.d_mu%.5f0_D%.5f0_u%.8f0_s%.12f0_Kd%.3f0._alpha%.2f0_radius%.3f0_step%.3f.txt", N, K, iterations, mu, D, u, s, log10(Kd/s), alpha, radius, step);
//	
///	pfile = fopen(name, "w+");
	
//	int i=0;
//	for (i=0; i<iterations; i++) fprintf(pfile, "%.d\n", array[i]);
//	fclose(pfile);
}//WriteHalflifes







