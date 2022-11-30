#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/network.h"

struct network {
  int qtd_vertices, qtd_edges, qtd_servers, qtd_clients, qtd_monitors;
  int *servers, *clients, *monitors;
  Graph *graph;
};

Network *read_network(const char *file_path) {
  FILE *file = fopen(file_path, "r");
  assert(file != NULL && "Could not open file");

  Network *n = malloc(sizeof(Network));

  fscanf(file, "%d %d", &n->qtd_vertices, &n->qtd_edges);
  fscanf(file, "%d %d %d", &n->qtd_servers, &n->qtd_clients, &n->qtd_monitors);

  n->clients = malloc(sizeof(int) * n->qtd_clients);
  n->servers = malloc(sizeof(int) * n->qtd_servers);
  n->monitors = malloc(sizeof(int) * n->qtd_monitors);
  n->graph = graph_new(n->qtd_vertices);

  for (int i = 0; i < n->qtd_servers; i++) {
    fscanf(file, "%d", &n->servers[i]);
  }

  for (int i = 0; i < n->qtd_clients; i++) {
    fscanf(file, "%d", &n->clients[i]);
  }

  for (int i = 0; i < n->qtd_monitors; i++) {
    fscanf(file, "%d", &n->monitors[i]);
  }

  int x, y;
  double weight;
  for (int i = 0; i < n->qtd_edges; i++) {
    fscanf(file, "%d %d %lf", &x, &y, &weight);
    add_edge(n->graph, x, y, weight);
  }

  fclose(file);

  return n;
}




int network_qtd_vertices(Network *n) {
  return n->qtd_vertices;
}

int network_qtd_edges(Network *n) {
  return n->qtd_edges;
}

int network_qtd_servers(Network *n) {
  return n->qtd_servers;
}

int network_qtd_clients(Network *n) {
  return n->qtd_clients;
}

int network_qtd_monitors(Network *n) {
  return n->qtd_monitors;
}

int *network_servers(Network *n) {
  return n->servers;
}

int *network_clients(Network *n) {
  return n->clients;
}

int *network_monitors(Network *n) {
  return n->monitors;
}

void network_free(Network *n) {
  free(n->clients);
  free(n->servers);
  free(n->monitors);
  free(n);
}

Graph *network_graph(Network *n) {
  return n->graph;
}
