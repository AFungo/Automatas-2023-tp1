#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
int main(){
    printf("\n**********************************************\nTEST concatenacion automaton\n\n");
    printf("\n-----------Concatenacion automaton a and b------------------\n");
    AFN a = readAutomaton("test/automatons/automatonA.dot");
    AFN b = readAutomaton("test/automatons/automatonB.dot");	 
    AFN *automaton = automatonConcatenacion(a, b);
    automatonToString(*automaton);
	writeAutomaton("test_concanetacion_a_b_automaton.dot", *automaton);

    printf("\n-----------Concatenacion automaton c and b------------------\n");
    AFN c = readAutomaton("test/automatons/automatonC.dot");
    b = readAutomaton("test/automatons/automatonB.dot");	
    automaton = automatonConcatenacion(c, b);
    automatonToString(*automaton);
	writeAutomaton("test_concanetacion_c_b_automaton.dot", *automaton);
    printf("\n**********************************************\n\n");
}