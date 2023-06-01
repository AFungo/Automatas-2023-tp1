#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
int main(){
    printf("\n**********************************************\nTEST MINIMIZACION\n\n");
    AFN automaton = readAutomaton("test/automatons/automatonTestMinimizacion.dot");
	//automatonToString(automaton);
    AFD afd = aFNtoAFD(&automaton);
//	writeAutomaton("automataTranformado.dot", AFDtoAFN((afd)));
	AFD *minimizado = minimization(afd);
	automaton = AFDtoAFN(*minimizado);
	automatonToString(automaton);
	writeAutomaton("test_automataMinimizado.dot", automaton);
	// kIndistinguibilidad(afd);

	    printf("\n**********************************************\n\n");
}