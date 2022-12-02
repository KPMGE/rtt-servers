#include <stdlib.h>
#include "../include/rtt_inflation.h"
#include "../include/utils.h"

struct rtt_inflation {
  int server_id, client_id;
  double inflation;
};

static RttInflation *rtt_inflation_new(int server_id, int client_id, double inflation) {
  RttInflation *n = malloc(sizeof(RttInflation));
  n->inflation = inflation;
  n->client_id = client_id;
  n->server_id = server_id;
  return n;
}

static int comp_fn(const void * a, const void * b) {
  RttInflation *rtt_a = *(RttInflation**)a;
  RttInflation *rtt_b = *(RttInflation**)b;
  if (rtt_a->inflation < rtt_b->inflation) return -1;
  if (rtt_a->inflation > rtt_b->inflation) return 1;
  return 0;
}

RttInflation **rtt_inflation_array(int n) {
  return malloc(sizeof(RttInflation *) * n);
}

void rtt_inflation_insert(RttInflation **array, int pos, int server_id, int client_id, double inflation) {
  array[pos] = rtt_inflation_new(server_id, client_id, inflation);
}

void rtt_inflation_sort(RttInflation **r, int qtd_elements) {
  qsort(r, qtd_elements, sizeof(RttInflation*), comp_fn);
}

int rtt_inflation_client_id(RttInflation *r) {
  return r->client_id;
}

int rtt_inflation_server_id(RttInflation *r) {
  return r->server_id;
}

double rtt_inflation_inflation(RttInflation *r) {
  return r->inflation;
}

void rtt_inflation_compute(Network *n, RttInflation **rtt_inflations) {
  int *servers = network_servers(n);
  int *clients = network_clients(n);

  int k = 0;
  for (int i = 0; i < network_qtd_servers(n); i++) {
    for (int j = 0; j < network_qtd_clients(n); j++) {
      const int server_id = servers[i];
      const int client_id = clients[j];
      const double real_rtt = rtt(n, server_id, client_id);
      const double estimated_rtt =
          calculate_estimated_rtt(n, server_id, client_id);
      const double inflation = estimated_rtt / real_rtt;
      rtt_inflation_insert(rtt_inflations, k++, server_id, client_id, inflation);
    }
  }
}

void rtt_inflation_free(RttInflation **r, int n) {
  for (int i = 0; i < n; i++) {
    if (r[i]) {
      free(r[i]);
    }
  }
  free(r);
}
