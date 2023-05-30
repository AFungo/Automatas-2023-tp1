gcc -o test7 test/testUnionAutomatons.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c
gcc -o test8 test/testConcatenacionAutomatons.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c
gcc -o test9 test/testKlenneClausure.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c

./test7
./test8
./test9

ls | grep -e "test[0-9]" | xargs rm

