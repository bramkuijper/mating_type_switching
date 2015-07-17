#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cmath>
#include <iostream>
#include "Global.hpp"
#include "Functions.hpp"
#include "InitiationFunctions.hpp"
#include "WriteFiles.hpp"

using namespace std;

//declare matrices
int x[N][2];						//x has the mating type and presence or absence of mating type gene
int x_double[2*N][2];
double p[runs][2];					//p has the final frequency of the switching gene at the end of each reapeat (needed for prob of fixation)
double pTrajectory[runs][maxSteps];     //for each run, keep track of the frequency of the siwtching gene over time for each run

//declare parameters
int g=50;
double pswitch = 1.0;
int length = maxSteps*(g+1)+1;
double p_initial=0.05;



//////////////////////////////////////////////////////////////////////////////
////////////////////////// M A I N   P R O G R A M //////////////////////////
////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv) {
    
	//s = atof(argv[1]);
	//m = atoi(argv[2]);	
	
    double p_traj_with_g[maxSteps];//this will keep track of the trajectory of p
    
	//srand((unsigned)time(0));
	srand(time(NULL));

	int t=0;                //time step, generation
	int h=0;
	int k=0;
    int i=0;
    int j=0;
    int count=0;
    //initiate parameters
    int glist[15];
    glist[0]=1;
    glist[1]=5;
    glist[2]=10;
    glist[3]=25;
    glist[4]=50;
    glist[5]=75;
    for(k=6; k<15; k++) glist[k] = (k-4)*50;
    double plist[11];
    for(k=0; k<11; k++) plist[k] = k*0.1;
    plist[0]=0.01;
    //main loop
    for(j=0; j<repeats; j++){//repeats for writing files multiple times
        for(k=0; k<11; k++){
            //g=glist[k];
            pswitch =plist[k];
            InitiateX(x, p_initial);
            InitiateP(p);
            IntiatepTraj(pTrajectory);
            for(h=0; h<runs; h++){
                InitiateX(x, p_initial);
                t=0;
                pTrajectory[h][t] = computeP(x);
                //   SampleWithReplacement(x, 1);
                //   switchType(x,pswitch);
                //   mate(x);
                //if p has not reached fixation of extinction repeat
                count=0;
                while(t<maxSteps && pTrajectory[h][t]!=1 && pTrajectory[h][t]!=0){
                    //sample g times to make the new x matrix after vegetative growth
                    //SampleWithReplacement(x, g);
                    //switch, every cell that has the switching gene swicthes with probability pswitch
                    //switchType(x,pswitch);
                    for(i=0; i<g; i++){
                        grow(x,x_double);
                        back_to_N(x_double,x);
                        p_traj_with_g[count]=computeP(x);
                        count++;
                    }
                    //mate, all possible pairs mate and everything amplified back to N
                    mate(x);
                    pTrajectory[h][t+1] = computeP(x);
                    p_traj_with_g[count]=computeP(x);
                    count++;
                    t++;
                }
                p[h][0] = computeP(x); //p will be either 0 or 1 (fixed or lost)
                p[h][1] = t*1.0; //time to fixation or extinction
                p_traj_with_g[count+2]=100.0;
            }
            //int sum=0;
            //int i=0;
            //for(i=0; i<runs;i++) sum=sum+p[i][0];
            printf("%.2f \n", computeP(x));
            WritePfix(p, j);
            //WriteP_trajectory(p_traj_with_g);
        }//for k
    }//forj
	return 0;
}



