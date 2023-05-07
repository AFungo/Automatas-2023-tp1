#include "afnd.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "utils.h"

bool test1 (AFN *a){
	char string[] = "1001011";
	assert(pertence(a,string)==true);
}

bool test2 (AFN *a){
	char string[] = "10";
	assert(pertence(a,string)==false);
}

bool test3 (AFN *a){
	char string[] = "1";
	assert(pertence(a,string)==true);
}

bool test4 (AFN *a){
	char string[] = "101";
	assert(pertence(a,string)==true);
}

bool test5 (AFN *a){
	char string[] = "0";
	assert(pertence(a,string)==false);
}

int main (int argc, char *argv[]){

	AFN *a = malloc(sizeof(AFN));
	
	addSymbolToAutomaton(a, 0);
	addSymbolToAutomaton(a, 1);
	addStateToAutomaton(a, 0);
	addStateToAutomaton(a, 1);
	addStateToAutomaton(a, 2);
	addInitialStateToAutomaton(a, 0);
	addNewDeltaToAutomaton(a, 0, 1, 0);
	addNewDeltaToAutomaton(a, 0, 2, 1);
	addNewDeltaToAutomaton(a, 1, 2, 0);
	addNewDeltaToAutomaton(a, 1, 0, 1);
	addNewDeltaToAutomaton(a, 2, 0, 0);
	addNewDeltaToAutomaton(a, 2, 1, 1);
	addNewFinalStateToAutomaton(a, 2);
	
/*	booleanArray delta[3][2] = { //       0           		1           
							0	{{false,true,false},{false,false,true}},
							1	{{false,false,true},{true,false,false}},
							2	{{true,false,false},{false,true,false}}
								}; 
*/	
//	automatonToString(*a);
	printf("test 1: ");
	printf(test1(a)? "true \n":"false \n");
	printf("test 2: ");
	printf(test2(a)? "true \n":"false \n");
	printf("test 3: ");
	printf(test3(a)? "true \n":"false \n");
	printf("test 4: ");
	printf(test4(a)? "true \n":"false \n");
	printf("test 5: ");
	printf(test5(a)? "true \n":"false \n");
}
