gcc -o test1 test/testStringBelongTheLanguage.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c
gcc -o test2 test/testReadBasicAutomaton.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c
gcc -o test3 test/testWriteBasicAutomaton.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c
gcc -o test4 test/testReadAutomatonWLambda.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c
gcc -o test5 test/testWriteAutomatonWLambda.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c
gcc -o test6 test/testAFNDTOAFD.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c

./test1
./test2
./test3
./test4
./test5
./test6

rm test*
