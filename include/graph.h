#ifndef GRAPH_H
#define GRAPH_H

typedef struct graph Graph;
Graph *graph_new(int vertices);
void add_edge(Graph *graph, int src, int dest, double weight);
void print_graph(Graph *graph);
int graph_vertices(Graph *graph);

#endif // !GRAPH_H
