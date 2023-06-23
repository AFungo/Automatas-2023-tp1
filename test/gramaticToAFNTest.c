#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
#include "../models/parsersLL1.h"
#include "../models/automatonAlgorithms.h"


int main(){
    printf("\n**********************************************\nTEST Gramatic TO AFND\n\n");
    AFN *afn = gramatictoAFN();
	automatonToString(*afn);
	writeAutomaton("test_gramatic_to_automaton.dot", *afn);
    printf("\n**********************************************\n\n");
}
