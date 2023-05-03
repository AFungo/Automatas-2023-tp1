//libreria donde se implementan conjuntos

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stdbool.h>

struct nodo{
	int elem;
	struct nodo *next;
};

struct set{
    int qty;
    struct nodo* first;
};

struct set *newSet(){
    struct set *set = (struct set*)malloc(sizeof(struct set));
    set-> first = NULL;
    set-> qty = 0;
    return set;
};

int setContain(struct set *set, int element) {
    struct nodo *actual_node = set->first;
    while (actual_node != NULL) {
        if ((actual_node->elem) == element) {
            return 1;
        }
        actual_node = actual_node->next;
    }
    return 0;
}


void setAdd(struct set *set, int elemento) {
    if (!setContain(set, elemento)) {
        struct nodo *nuevo_nodo = (struct nodo*)malloc(sizeof(struct nodo));
        nuevo_nodo->elem = elemento;
        nuevo_nodo->next = set->first;
        set->first = nuevo_nodo;
        set->qty++;
    }
}


void setRemove(struct set *set, int elemento) {
    struct nodo *actual_node = set->first;
    struct nodo *back_node = NULL;
    if (setContain(set, elemento)) {
        while (actual_node != NULL) {
            if (actual_node->elem == elemento) {
                if (back_node != NULL) {
                    back_node->next = actual_node->next;
                } else {
                    set->first = actual_node->next;
                }
                free(actual_node);
                set->qty--;
                return;
            }
            back_node = actual_node;
            actual_node = actual_node->next;
        }
    }
}
bool equalsSet(struct set *set1,struct set *set2) {
    struct nodo *actual_node = set1->first;
    if (set1->qty==set2->qty){
        while (actual_node!=NULL){
            if(setContain(set2,actual_node->elem)){
                actual_node=actual_node->next;
            } else {
                return false;
            }
            
        }
        return true;
    } else {
        return false;
    }
}

int main(int argc, char const *argv[])
{   
    struct set *set1 = newSet();
    struct set *set2 = newSet();
    setAdd(set1,1);
    setAdd(set1,2);
    setAdd(set1,3);
    setAdd(set2,2);
    setAdd(set2,1);
    //setAdd(set2,3);
    setAdd(set2,4);
    if (equalsSet(set1,set2)){
        printf("los sets son iguales");
    } else {
        printf("los sets son distintos");
    }
}
