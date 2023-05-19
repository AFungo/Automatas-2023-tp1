#ifndef ALPHABETUTILS_h
#define ALPHABETUTILS_h
#define ALPHABET_SIZE 5

typedef struct{
	int alphabet[ALPHABET_SIZE]; //lambda == 0
	int cant;
}Alphabet;

bool pertenceAlph(int alph[], char *chain);
void initAlphabet(Alphabet *alphabet);
void addNewSymbolToAlphabet(Alphabet *alphabet, int symbol);
int getAlphabetIndex(Alphabet alphabet, int symbol);

#endif