#ifndef RTT_INFLATION
#define RTT_INFLATION
#include "network.h"

typedef struct rtt_inflation RttInflation;

RttInflation **rtt_inflation_array(int n);
void rtt_inflation_insert(RttInflation **array, int pos, int server_id, int client_id, double inflation);
void rtt_inflation_sort(RttInflation **r, int qtd_elements);
int rtt_inflation_client_id(RttInflation *r);
int rtt_inflation_server_id(RttInflation *r);
double rtt_inflation_inflation(RttInflation *r);
void rtt_inflation_compute(Network *n, RttInflation **rtt_inflations);
void rtt_inflation_free(RttInflation **r, int n);

#endif // !RTT_INFLATION
