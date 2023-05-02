#include "afnd.h"

int main(){
    AFN automaton = readAutomaton("automata.dot");
	automatonToString(automaton);
	writeAutomaton("test_automata.dot", automaton);
}


