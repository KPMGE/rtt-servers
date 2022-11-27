#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include "./linkedList.h"
typedef struct distances Distances;
typedef struct network Network;

Network* start_network(FILE* in);
double* djkistra_algorithm(int id, int vertex, LinkedList** linked);
void read_network(FILE* in, Network* n, Distances* d);

#endif
