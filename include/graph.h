#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"

typedef struct graph Graph;

Graph *graph_new(int vertices);
void add_edge(Graph *graph, int src, int dest, double weight);
void print_graph(Graph *graph);
int graph_vertices(Graph *graph);
Vertex *graph_get_vertex(Graph *graph, int index);

#endif // !GRAPH_H
