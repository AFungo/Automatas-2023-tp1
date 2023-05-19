/*#include "automatonAlgorithms.h"
#include "noDeterministicAutomaton.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

int main (int argc, char *argv[]){

	AFN *a; 
    AFD *afd;
    *a = readAutomaton("automataND.dot");
    int deltaResult[MAX_STATES][ALPHABET_SIZE] ={{0,1,2},{0,1,3},{0,1,3},{0,1,3}};
    bool testDelta=true; 


    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 3; k++){
            if(deltaResult[i][k]!=afd->delta[i][k]){
                testDelta=false;
            }
        }
        
    }
    bool testFinalSt=true;
    int finalStResult[MAX_STATES][MAX_STATES] ={{0,-1,2,-1},{0,1,2,3},{-1,1,2,-1},{0,1,2,-1}};
    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 4; k++){
            if(finalStResult[i][k]!=afd->finalStates[i][k]){
                testFinalSt=false;
            }
        }
        
    }

    bool testStates=true;
    int StatesResult[MAX_STATES][MAX_STATES] ={{0,-1,2,-1},{0,1,2,3},{-1,1,2,-1},{0,1,2,-1}};
    for (int i = 0; i < 4; i++){
        for (int k = 0; k < 4; k++){
            if(finalStResult[i][k]!=afd->finalStates[i][k]){
                testFinalSt=false;
            }
        }
        
    }    
    printf("Resultado del test: %s",(testDelta&&testFinalSt&&testStates==true)? "true \n":"false \n");
}*/