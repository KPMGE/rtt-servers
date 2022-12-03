#ifndef NETWORK_H
#define NETWORK_H

#include "./graph.h"

typedef struct network Network;

Network *read_network(const char *file_path);
int network_qtd_vertices(Network *n);
int network_qtd_edges(Network *n);
int network_qtd_servers(Network *n);
int network_qtd_clients(Network *n);
int network_qtd_monitors(Network *n);
int *network_servers(Network *n);
int *network_clients(Network *n);
int *network_monitors(Network *n);
double *network_distances(Network *n, int pos);
void network_free(Network *n);

#endif // !NETWORK_H

