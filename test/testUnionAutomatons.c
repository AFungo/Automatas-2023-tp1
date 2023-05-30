#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
int main(){
    printf("\n**********************************************\nTEST union automaton\n\n");
    printf("\n-----------Union automaton a and b------------------\n");
    AFN a = readAutomaton("test/automatons/automatonA.dot");
    AFN b = readAutomaton("test/automatons/automatonB.dot");	
    AFN *automaton = automatonUnion(a, b);
    automatonToString(*automaton);
	writeAutomaton("test_union_a_b_automaton.dot", *automaton);

    printf("\n-----------Union automaton c and b------------------\n");
    AFN c = readAutomaton("test/automatons/automatonC.dot");
    b = readAutomaton("test/automatons/automatonB.dot");	
    automaton = automatonUnion(c, b);
    automatonToString(*automaton);
	writeAutomaton("test_union_a_c_automaton.dot", *automaton);
    printf("\n**********************************************\n\n");
}