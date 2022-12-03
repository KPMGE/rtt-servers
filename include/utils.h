#ifndef UTILS_H
#define UTILS_H
#include "./network.h"
#include "./graph.h"
#include "./rtt_inflation.h"

Network *read_net(const char *file_path);
double *dijkstra(Graph* graph, int src); 
double rtt(Network *n, int a, int b);
double calculate_estimated_rtt(Network *n, int a, int b);
double *calculate_rtts(Graph *graph, int *s1, int s1_size, int *s2, int s2_size);
void save_rtt_inflation_to_file(const char *output_file, RttInflation **rtt_inflations, int qtd_inflations);

#endif // !UTILS_H
