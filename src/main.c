#include "../include/graph.h"
#include "../include/network.h"
#include "../include/rtt_inflation.h"
#include "../include/utils.h"
#include "../include/priority_queue.h"
#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  assert(argc >= 3);

  const char *input_file_path = argv[1];
  const char *output_file_path = argv[2];

  Network *n = read_network(input_file_path);

  int amount_outputs = network_qtd_servers(n) * network_qtd_clients(n);
  RttInflation **rtt_inflations = rtt_inflation_array(amount_outputs);

  rtt_inflation_compute(n, rtt_inflations);
  rtt_inflation_sort(rtt_inflations, amount_outputs);
  save_rtt_inflation_to_file(output_file_path, rtt_inflations, amount_outputs);

  rtt_inflation_free(rtt_inflations, amount_outputs);
  network_free(n);
}
