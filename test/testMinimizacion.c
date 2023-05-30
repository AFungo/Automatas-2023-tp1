#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
int main(){
    printf("\n**********************************************\nTEST MINIMIZACION\n\n");
    AFN automaton = readAutomaton("test/automatons/automatonTestMinimizacion.dot");
	//automatonToString(automaton);
    AFD afd = aFNtoAFD(&automaton);
	automatonToString(AFDtoAFN(afd));
	kIndistinguibilidad(afd);

	//writeAutomaton("test_automataMinimizado.dot", AFDtoAFN(afd));
	    printf("\n**********************************************\n\n");
}