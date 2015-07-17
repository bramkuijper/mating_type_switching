#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include "Global.hpp"
#include "Functions.hpp"
#include "InitiationFunctions.hpp"

//////////////
//FUNTIONS //
/////////////

//create random number from 0 to 1
double unifRand()
{
    return rand() / double(RAND_MAX);
}//unifRand

void copyAtoB(int a[N][2], int b[N][2]){
    int i=0;
    for (i=0; i<N; i++) {
        b[i][0]=a[i][0];
        b[i][1]=a[i][1];
    }
}//copyAtoB

//SampleWithReplacement
void SampleWithReplacement(int cells[N][2], int gens){
    int cellsTemp[N][2];
	int randomNum =0;
    int i=0;
    int j=0;

    InitiateX(cellsTemp,0);
    
    for(i=0; i<gens; i++){
        for (j=0; j<N; j++) {
            randomNum = rand()%N;
            cellsTemp[j][0] = cells[randomNum][0];
            cellsTemp[j][1] = cells[randomNum][1];
        }
        copyAtoB(cellsTemp, cells);		
    }
}//SampleWithReplacement

void switchType(int cells[N][2], double prob){
    int i=0;
    double sample = 0.0;
    
    for (i=0; i<N; i++)
		//if a cells has the switching gene
        if(cells[i][1]==1){
            sample = unifRand();
            if(sample<=prob){
                //switch with probability prob
                if(cells[i][0]==0) cells[i][0]=1;
                else    cells[i][0]=0;
            }
        }
}//switchType

//shuffle list 
void shuffleList(int list[N][2]){
	int i=0;
	int temp1=0;
	int temp2=0;
	
	for (i=0; i<N; i++) {
		int rval = rand()%N;
		temp1 = list[i][0];
		temp2 = list[i][1];
		list[i][0] = list[rval][0];
		list[i][1] = list[rval][1];
		list[rval][0] = temp1;
		list[rval][1] = temp2;
	}
}//shuffleList

//shuffle list of size 2N
void shuffleList_2N(int list[2*N][2]){
	int i=0;
	int temp1=0;
	int temp2=0;
	
	for (i=0; i<2*N; i++) {
		int rval = rand()%(2*N);
		temp1 = list[i][0];
		temp2 = list[i][1];
		list[i][0] = list[rval][0];
		list[i][1] = list[rval][1];
		list[rval][0] = temp1;
		list[rval][1] = temp2;
	}
}//shuffleList_2N


void mate(int cells[N][2]){
	int i=0;
    int sum=0;
	int count =0;
	int indexCount=0;
	int randomNum=0;
    
    for(i=0; i<N;i++) sum=sum+cells[i][0];
	
	shuffleList(cells);
	//if more 1s than zeros
	if(sum>N/2 && sum<N){
		int cellsMATED[2*(N-sum)][2];
		int h=0;
		for(h=0; h<2*(N-sum);h++){
			cellsMATED[h][0]= -1;
			cellsMATED[h][1] = -1;
		}
		for(i=0; i<N; i++){
			//if current cell a 0, add it to mated list
			if(cells[i][0]==0){
				cellsMATED[indexCount][0] = cells[i][0];
				cellsMATED[indexCount][1] = cells[i][1];
				indexCount++;
			}
			//if current cell at 1 and no more than N-sum 1's already chosen, add it to mated list
			else if(cells[i][0]==1 && count<(N-sum)) {
				cellsMATED[indexCount][0] = cells[i][0];
				cellsMATED[indexCount][1] = cells[i][1];
				count++;
				indexCount++;
			}
			if(indexCount>2*(N-sum)-1) break;
		}
		//impose recombination
//		int l =0; //this is the number of mated cells carrying the switch mutant
//		for(i=0; i<2*(N-sum);i++) l=l+cellsMATED[i][1];
		//reasign cells MATED based on recombination
//		if(l%2==0){
//			for (i=0; i<l/2; i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=1;
//			}
//			for (i=l/2; i<(N-sum); i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=0;
//			}
//			for (i=(N-sum); i<(N-sum + l/2); i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=1;
//			}
//			for (i=(N-sum + l/2); i<2*(N-sum); i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=0;
//			}
//		}
//		else {
//			for (i=0; i<(l/2+1); i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=1;
//			}
//			for (i=(l/2+1); i<(N-sum); i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=0;
//			}
//			for (i=(N-sum); i<(N-sum + l/2); i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=1;
//			}
//			for (i=(N-sum + l/2); i<2*(N-sum); i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=0;
//			}
//		}//recombination finished
		//restore original matrix with N cells by sampling with replacement from mated cells
		for(i=0; i<N; i++){
			randomNum = rand()%(2*(N-sum));
			cells[i][0] = cellsMATED[randomNum][0];
			cells[i][1] = cellsMATED[randomNum][1];
		}
	}
	//if more 0's than 1's
	else if(sum>0 && sum<N/2){
		int cellsMATED[2*sum][2];
		int h=0;
		for(h=0; h<2*sum;h++){
			cellsMATED[h][0]= -1;
			cellsMATED[h][1] = -1;
		}
		for(i=0; i<N; i++){
			//if current cell a 1, add it to mated list
			if(cells[i][0]==1){
				cellsMATED[indexCount][0] = cells[i][0];
				cellsMATED[indexCount][1] = cells[i][1];
				indexCount++;
			}
			//if current cell at 0 and no more than sum 0's already chosen, add it to mated list
			else if(cells[i][0]==0 && count<sum) {
				cellsMATED[indexCount][0] = cells[i][0];
				cellsMATED[indexCount][1] = cells[i][1];
				count++;
				indexCount++;
			}
			if(indexCount>2*sum-1) break;
		}
//		//impose recombination
//		int l =0; //this is the number of mated cells carrying the switch mutant
//		for(i=0; i<2*sum;i++) l=l+cellsMATED[i][1];
//		//reasign cells MATED based on recombination
//		if(l%2==0){
//			for (i=0; i<l/2; i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=1;
//			}
//			for (i=l/2; i<sum; i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=0;
//			}
//			for (i=sum; i<(sum + l/2); i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=1;
//			}
//			for (i=(sum + l/2); i<2*sum; i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=0;
//			}
//		}
//		else {
//			for (i=0; i<(l/2+1); i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=1;
//			}
//			for (i=(l/2+1); i<sum; i++) {
//				cellsMATED[i][0]=0;
//				cellsMATED[i][1]=0;
//			}
//			for (i=sum; i<(sum + l/2); i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=1;
//			}
//			for (i=(sum + l/2); i<2*sum; i++) {
//				cellsMATED[i][0]=1;
//				cellsMATED[i][1]=0;
//			}
//		}//recombination finished
		//restore original matrix with N cells by sampling with replacement from mated cells
		for(i=0; i<N; i++){
			randomNum = rand()%(2*sum);
			cells[i][0] = cellsMATED[randomNum][0];
			cells[i][1] = cellsMATED[randomNum][1];
		}
	}		
}//mate

//finds the freuqncy of the switch gene in the population
double computeP(int cells[N][2]){
	int i=0;
	int sum=0;
	
	for(i=0; i<N;i++) sum=sum+cells[i][1];
	
	return((1.0*sum+0.0)/(1.0*N+0.0));
}//computeP

//veg_growth
void veg_growth(int cells[N][2], int gens){
    int cells_new[2*N][2];
	int randomNum =0;
    int i=0;
    int j=0;
    
    //initiate cells new
    for(i=0; i<(2*N+1);i++){
        cells_new[i][0]=0;
        cells_new[i][1]=0;
    }
        
    for(i=0; i<gens; i++){
        grow(cells, cells_new); //double and switch
        shuffleList_2N(cells_new);
        back_to_N(cells_new, cells); //back from 2N to N through sampling
    }
}//veg_growth

//this function imposes one veg growth step with the population size doubling and
//allows for switching depending on the switchinbg probability
void grow(int cells[N][2], int cells_2[2*N][2]){
    int i=0;
    int count =0;
    
    for (i=0; i<(N+1); i++) {
        //first daughter cell is clonal
        cells_2[count][0] = cells[i][0];
        cells_2[count][1] = cells[i][1];
        if(cells[i][1]==0){//if cell does not have the capacity to switch both daughter cells are clonal
            cells_2[count+1][0] = cells[i][0];
            cells_2[count+1][1] = cells[i][1];
        }
        else{//else one daughter cell will switch with given probability
            if(unifRand()<pswitch){//switch with prob (pwitch)
                if(cells[i][0]==0) cells_2[count+1][0]=1;
                else    cells_2[count+1][0]=0;
            }
            else cells_2[count+1][0] = cells[i][0]; //if no swicthing then take type of parent cell
        }
        cells_2[count+1][1] = cells[i][1];//inherit the switching gene state of parent cell
        count=count+2;
    }//for
}//grow

void back_to_N(int cells2N[2*N][2], int c[N][2]){
    int i=0;
    
    //sshuffle 2N population and choose first N
    shuffleList_2N(cells2N);
    for (i=0; i<N; i++) {
        c[i][0] = cells2N[i][0];
        c[i][1] = cells2N[i][1];
    }
}//back_to_N







