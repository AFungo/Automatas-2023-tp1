#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
int main(){
    printf("\n**********************************************\nTEST AFND TO AFD ALGORITHM\n\n");
    AFN automaton = readAutomaton("test/automatons/automatonTestAFNAFD.dot");
	automatonToString(automaton);
    AFD afd = aFNtoAFD(&automaton);
	automatonToString(AFDtoAFN(afd));
	writeAutomaton("test_automataD.dot", AFDtoAFN(afd));
	    printf("\n**********************************************\n\n");
}

