#include "afnd.h"
#include "utils.h"
int main(){
    
    AFN automaton = readAutomaton("automatonTestAFNAFD.dot");
	//automatonToString(automaton);
    AFD afd = aFNtoAFD(&automaton);
	automatonToString(AFDtoAFN(afd));
	writeAutomaton("test_automataD.dot", AFDtoAFN(afd));
}

