#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/graph.h"
#include "../include/network.h"
#include "../include/utils.h"

int main(int argc, char *argv[]) {
  assert(argc >= 2);
  Network *n = read_network(argv[1]);
  /*int *servers = network_servers(n);
  int *clients = network_clients(n);
  int *monitors = network_monitors(n);
  Graph *graph = network_graph(n);
  int qtd_monitors = network_qtd_monitors(n);

  for (int i = 0; i < network_qtd_servers(n); i++) {
    for (int j = 0; j < network_qtd_clients(n); j++){
      const int server_id = servers[i];
      const int client_id = clients[j];

      const double real_rtt = rtt(graph, server_id, client_id);
      const double estimated_rtt = calculate_estimated_rtt(graph, server_id, client_id, monitors, qtd_monitors);
      const double inflation = estimated_rtt / real_rtt;

      printf("%d %d %.16f\n", server_id, client_id, inflation);
    }
  }*/
}
