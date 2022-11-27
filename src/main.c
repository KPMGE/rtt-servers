#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/priorityQueue.h"
#include "../include/graph.h"

typedef struct {
  int qtd_vertices, qtd_edges, qtd_servers, qtd_clients, qtd_monitors;
  int *servers, *clients, *monitors;
  Graph *graph;
} Network;

Network *read_net(const char *file_path);

int main(int argc, char *argv[]) {
  assert(argc >= 2);
  Network *n = read_net(argv[1]);

  printf("|V|: %d, |E|: %d\n", n->qtd_vertices, n->qtd_edges);
  printf("|S|: %d, |C|: %d, |M|: %d\n", n->qtd_servers, n->qtd_clients,
         n->qtd_monitors);
  printf("\n");

  printf("\nservers: \n");
  for (int i = 0; i < n->qtd_servers; i++) {
    printf("%d\n", n->servers[i]);
  }

  printf("\nclients: \n");
  for (int i = 0; i < n->qtd_clients; i++) {
    printf("%d\n", n->clients[i]);
  }

  printf("\nmonitors: \n");
  for (int i = 0; i < n->qtd_monitors; i++) {
    printf("%d\n", n->monitors[i]);
  }

  printf("\nGraph: \n");
  print_graph(n->graph);
}

Network *read_net(const char *file_path) {
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
