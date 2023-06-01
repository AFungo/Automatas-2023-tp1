#ifndef AUTOMATONALGORITHM_H
#define AUTOMATONALGORITHM_H
#include "deterministicAutomaton.h"
#include "noDeterministicAutomaton.h"
#include "../utils/partitions.h"

AFN readAutomaton(char *fileName);
void writeAutomaton(char *fileName, AFN automaton);
bool pertence(AFN *t, char *chain);
AFD aFNtoAFD(AFN *a);
AFN AFDtoAFN(AFD afd);
AFN *automatonUnion(AFN a, AFN b);
AFN *automatonConcatenacion(AFN a, AFN b);
AFN *automatonKlenneClausure(AFN a);
Partitions *kIndistinguibilidad(AFD afd);
AFD *minimization(AFD afd);
#endif