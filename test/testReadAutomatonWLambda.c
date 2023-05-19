#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>

int main(){
    printf("\n**********************************************\nTEST read automaton with lambda\n\n");
    AFN automaton = readAutomaton("test/automatons/automataND.dot");
	automatonToString(automaton);
    printf("\n**********************************************\n\n");

}


