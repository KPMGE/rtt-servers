#ifndef UTILS_H
#define UTILS_H
#include "./network.h"
#include "./graph.h"

Network *read_net(const char *file_path);
double *dijkstra(Graph* graph, int src); 
double rtt(Graph *graph, int a, int b);

#endif // !UTILS_H
