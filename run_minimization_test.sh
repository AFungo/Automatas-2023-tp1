gcc -o test9 test/testMinimizacion.c utils/alphabetUtils.c models/automatonAlgorithms.c  models/deterministicAutomaton.c  models/noDeterministicAutomaton.c  utils/stateUtils.c  utils/utils.c utils/partitions.c


./test9

ls | grep -e "test[0-9]" | xargs rm