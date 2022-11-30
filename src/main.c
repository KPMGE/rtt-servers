#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/priorityQueue.h"
#include "../include/graph.h"
#include "../include/network.h"
#include "../include/utils.h"

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

  double *distances = dijkstra(n->graph, 0);
  printf("\ndistances: \n");
  for (int i = 0; i < n->qtd_vertices; i++) {
    printf("%.2f\n", distances[i]);
  }

  printf("\nrtt(0, 4): %.2f\n", rtt(n->graph, 0, 4));
}
