#include "../models/automatonAlgorithms.h"
#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
int main(){
    printf("\n**********************************************\nTEST Klenne clausure automaton\n\n");
    printf("\n-----------Klenne clausure automaton a------------------\n");
    AFN a = readAutomaton("test/automatons/automatonA.dot");
    AFN *automaton = automatonKlenneClausure(a);
    automatonToString(*automaton);
	writeAutomaton("test_klenne_clausure_automatonA.dot", *automaton);
    printf("\n-----------Klenne clausure automaton b------------------\n");
    a = readAutomaton("test/automatons/automatonB.dot");
    automaton = automatonKlenneClausure(a);
    automatonToString(*automaton);
	writeAutomaton("test_klenne_clausure_automatonB.dot", *automaton);
    printf("\n-----------Klenne clausure automaton c------------------\n");
    a = readAutomaton("test/automatons/automatonC.dot");
    automaton = automatonKlenneClausure(a);
    automatonToString(*automaton);
	writeAutomaton("test_klenne_clausure_automatonC.dot", *automaton);
    printf("\n**********************************************\n\n");
}