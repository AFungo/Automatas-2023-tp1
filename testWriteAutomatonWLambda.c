#include "afnd.h"
#include "utils.h"
int main(){
    AFN automaton = readAutomaton("automataND.dot");
	automatonToString(automaton);
	writeAutomaton("test_automataND.dot", automaton);
}

