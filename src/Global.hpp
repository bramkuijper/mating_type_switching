#ifndef GLOBAL
#define GLOBAL //Global.hpp

//dimensions
#define N (600)             //number of cells

//Define global fixed parameters
#define maxSteps (50000)	//maximum number of time steps per iteration
#define max (100000)
#define runs (10000)		//number of runs for a single parameter set to get average
#define repeats (1)        //number of repeats to average over pfixation


//define global parameters that can be modified in main
extern double pswitch;			//probabilitty a cell carrying the mutation will switch
extern int g;                //vegetative generations
extern double p_initial;                //initial frequency of p



#endif
