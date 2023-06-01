#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "partitions.h"
#include "stateUtils.h"

bool containsPartition(Partitions partitions, States newPartition){
	for(int i = 0; i < partitions.cant; i++){
		if(statesAreEquals(partitions.partitions[i],newPartition)) return true;
	}
	return false;
}

bool partitionsAreEquals(Partitions partitions, Partitions newPartitions){
	if(partitions.cant != newPartitions.cant) return false;
	for(int i = 0; i < partitions.cant; i++){
		if(!containsPartition(newPartitions, partitions.partitions[i])) return false;
	}
	return true;	
}


void addPartition(Partitions *partitions, States newPartition){
	if(!containsPartition(*partitions, newPartition)){
		partitions->partitions[partitions->cant] = newPartition;
		partitions->cant++;
	}
}


int getPartitionIndexOfState(Partitions partitions, int state){
	for(int i = 0; i < partitions.cant; i++){
		int index = getStateIndex(partitions.partitions[i], state);
		if(index != -1) return i;
	}
	return -1;
}

void partitionToString(Partitions partitions){
	for(int i = 0; i < partitions.cant; i++){
		printStates(partitions.partitions[i]);
	}
}

























