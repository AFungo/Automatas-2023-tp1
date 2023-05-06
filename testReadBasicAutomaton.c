#include "afnd.h"
#include "utils.h"
int main(){
    AFN automaton = readAutomaton("automata.dot");
	automatonToString(automaton);
}


