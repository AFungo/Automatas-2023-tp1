#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
int main(){
    printf("\n**********************************************\nTEST write basic automaton\n\n");
    AFN automaton = readAutomaton("test/automatons/automata.dot");
	automatonToString(automaton);
	writeAutomaton("test_automata.dot", automaton);
    printf("\n**********************************************\n\n");
}


