#ifndef PARTITIONS_h
#define PARTITIONS_h
#include "stateUtils.h"

#define MAX_PARTITIONS 100

typedef struct{
	States partitions[MAX_PARTITIONS];
	int cant;
}Partitions;

bool containsPartition(Partitions partitions, States newPartition);
void addPartition(Partitions *partitions, States newPartition);
bool partitionsAreEquals(Partitions partitions, Partitions newPartitions);
int getPartitionIndexOfState(Partitions partitions, int state);
void partitionToString(Partitions partitions);
#endif