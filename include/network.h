#ifndef NETWORK_H
#define NETWORK_H
#include "./graph.h"

typedef struct {
  int qtd_vertices, qtd_edges, qtd_servers, qtd_clients, qtd_monitors;
  int *servers, *clients, *monitors;
  Graph *graph;
} Network;

#endif // !NETWORK_H

