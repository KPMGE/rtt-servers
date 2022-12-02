#include "../include/graph.h"
#include "../include/network.h"
#include "../include/rtt_inflation.h"
#include "../include/utils.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  assert(argc >= 2);
  Network *n = read_network(argv[1]);
  int amount_outputs = network_qtd_servers(n) * network_qtd_clients(n);
  RttInflation **rtt_inflations = rtt_inflation_array(amount_outputs);

  rtt_inflation_compute(n, rtt_inflations);

  for (int i = 0; i < amount_outputs; i++) {
    const int server_id = rtt_inflation_server_id(rtt_inflations[i]);
    const int client_id = rtt_inflation_client_id(rtt_inflations[i]);
    const double inflation = rtt_inflation_inflation(rtt_inflations[i]);
    printf("%d %d %.16f\n", server_id, client_id, inflation);
  }

  rtt_inflation_free(rtt_inflations, amount_outputs);
}
