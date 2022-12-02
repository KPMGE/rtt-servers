#include "../include/network.h"
#include "../include/utils.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct network {
  int qtd_vertices, qtd_edges, qtd_servers, qtd_clients, qtd_monitors;
  int *servers, *clients, *monitors;
  double **distances;
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
  Graph *graph = graph_new(n->qtd_vertices);
  n->distances = malloc(sizeof(double *) * n->qtd_vertices);

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
    add_edge(graph, x, y, weight);
  }

  fclose(file);


  // for (int i = 0; i < network_qtd_servers(n); i++) {
  //   for (int j = 0; j < network_qtd_clients(n); j++){
  //     const int server_id = n->servers[i];
  //     const int client_id = n->clients[j];

  //     // n->distances[server_id] = dijkstra(graph, i);
  //     // n->distances[client_id] = dijkstra(graph, j);


  //     double *distances_a = dijkstra(graph, server_id);
  //     double *distances_b = dijkstra(graph, client_id);
  //     double rtt = distances_a[client_id] + distances_b[server_id];

  //     free(distances_a);
  //     free(distances_b);

  //     printf("rtt: %.2f\n", rtt);

  //     // const double real_rtt = rtt(n, server_id, client_id);
  //     // const double estimated_rtt = calculate_estimated_rtt(n, server_id, client_id);
  //     // const double inflation = estimated_rtt / real_rtt;

  //     // free(n->distances[i]);
  //     // free(n->distances[j]);

  //     // printf("%d %d %.16f\n", server_id, client_id, inflation);
  //   }
  // }

  printf("start dijkstra\n");
  for (int i = 0; i < n->qtd_vertices; i++) {
    if (i <= 10) {
      n->distances[i] = dijkstra(graph, i);
    } else {
      n->distances[i] = 0;
    }
  }
  printf("finish dijkstra\n");

  graph_free(graph);

  return n;
}

int network_qtd_vertices(Network *n) { return n->qtd_vertices; }

int network_qtd_edges(Network *n) { return n->qtd_edges; }

int network_qtd_servers(Network *n) { return n->qtd_servers; }

int network_qtd_clients(Network *n) { return n->qtd_clients; }

int network_qtd_monitors(Network *n) { return n->qtd_monitors; }

int *network_servers(Network *n) { return n->servers; }

int *network_clients(Network *n) { return n->clients; }

int *network_monitors(Network *n) { return n->monitors; }

double *network_distances(Network *n, int pos) {
  return n->distances[pos];
}

void network_free(Network *n) {
  free(n->clients);
  free(n->servers);
  free(n->monitors);
  free(n);
}
