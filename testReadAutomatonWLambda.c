#include "afnd.h"

int main(){
    AFN automaton = readAutomaton("automataND.dot");
	automatonToString(automaton);
}


