#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>

int main(){
    printf("\n**********************************************\nTEST write automaton with lambda\n\n");
    AFN automaton = readAutomaton("test/automatons/automataND.dot");
	automatonToString(automaton);
	writeAutomaton("test_automataND.dot", automaton);
    printf("\n**********************************************\n");
}


