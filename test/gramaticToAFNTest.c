#include "../models/noDeterministicAutomaton.h"
#include "../utils/utils.h"
#include <stdio.h>
#include "../models/parsersLL1.h"
#include "../models/automatonAlgorithms.h"

void test(char chain[], char filename[]){
    AFN *afn = malloc(sizeof(AFN));
    getAFNFromRegExp(chain, &afn);
	automatonToString(*afn);
	writeAutomaton(filename, *afn);
    free(afn);
}

int main(){//IMPORTANTE los test no se puede conrrer de mas de a 2, si no retorna segmentation fault, individualmente andan a la perfeccion
    printf("\n**********************************************\nTEST Gramatic TO AFND\n\n");
    // test("((a*).b)|c*#", "test_gramatic_to_automaton_1.dot");
    // printf("\n-----------------------------------------------------\n");
    // test("(a)#", "test_gramatic_to_automaton_2.dot");
    // printf("\n-----------------------------------------------------\n");
    // test("(a*)#", "test_gramatic_to_automaton_3.dot");
    // printf("\n-----------------------------------------------------\n");
    test("a*#", "test_gramatic_to_automaton_4.dot");
    // printf("\n**********************************************\n\n");
}
