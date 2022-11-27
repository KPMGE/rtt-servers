#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/priorityQueue.h"
// #include "../include/network.h"

typedef struct {
  int origin_id, destination_id;
  double weight;
} Edge;

typedef struct {

} Graph;

typedef struct {
  int qtd_vertices, qtd_edges, qtd_servers, qtd_clients, qtd_monitors;
  int *servers, *clients, *monitors;
  Edge **edges;
} Network;

Network *read_net(const char *file_path);
Edge *edge_new(int origin_id, int destination_id, double weight);
int edge_origin_id(const Edge *e);
int edge_destination_id(const Edge *e);
double edge_weight(const Edge *e);
double edge_find_weight(const Edge **edges, int qtd_edges, int origin_id, int destination_id);
double *dijkstra(const Edge **edges, const int *vertices, int graph_size, int source);

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

  printf("\nedges:\n");
  for (int i = 0; i < n->qtd_edges; i++) {
    printf("%d->%d: %lf\n", edge_origin_id(n->edges[i]), edge_destination_id(n->edges[i]), edge_weight(n->edges[i]));
  }
}

Edge *edge_new(int origin_id, int destination_id, double weight) {
  Edge *e = malloc(sizeof(Edge));
  e->origin_id = origin_id;
  e->destination_id = destination_id;
  e->weight = weight;
  return e;
}

int edge_origin_id(const Edge *e) { return e->origin_id; }
int edge_destination_id(const Edge *e) { return e->destination_id; }
double edge_weight(const Edge *e) { return e->weight; }
double edge_find_weight(const Edge **edges, int qtd_edges, int origin_id, int destination_id) {
  for (int i = 0; i < qtd_edges; i++) {
    if (edge_origin_id(edges[i]) == origin_id && edge_destination_id(edges[i]) == destination_id) {
      return edge_weight(edges[i]);
    }
  }
  return -1;
}

Network *read_net(const char *file_path) {
  FILE *file = fopen(file_path, "r");
  assert(file != NULL && "Could not open file");

  Network *n = malloc(sizeof(Network));

  fscanf(file, "%d %d", &n->qtd_vertices, &n->qtd_edges);
  fscanf(file, "%d %d %d", &n->qtd_servers, &n->qtd_clients, &n->qtd_monitors);

  n->edges = malloc(sizeof(Edge) * n->qtd_edges);
  n->clients = malloc(sizeof(int) * n->qtd_clients);
  n->servers = malloc(sizeof(int) * n->qtd_servers);
  n->monitors = malloc(sizeof(int) * n->qtd_monitors);

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
    n->edges[i] = edge_new(x, y, weight);
  }

  fclose(file);

  return n;
}
