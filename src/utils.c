#include "../include/priority_queue.h"
#include "../include/rtt_inflation.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define MIN(A, B) ((A) < (B) ? (A) : (B))

double *dijkstra(Graph* graph, int src) {
  int amount_vertices = graph_vertices(graph);
	double *distance = malloc(sizeof(double) * amount_vertices);
	int *visited = malloc(sizeof(int) * amount_vertices);

	for (int i = 0; i < amount_vertices; i++) {
		distance[i] = INFINITY;
		visited[i] = 0;
	}

	distance[src] = 0.0;
  PriorityQueue *pq = priority_queue_init(amount_vertices);
  Vertex *new_node = vertex_new(src);
  new_node->weight = 0.0;

  priority_queue_insert(pq, new_node);

	while (!priority_queue_empty(pq))  {
		Vertex *current = priority_queue_delmin(pq);
		int index = current->id;
		visited[index] = 1;

		double new_weight;
    Vertex *temp = graph_get_vertex(graph, index);

    while (temp) {
			if (visited[temp->id] == 0) {
				new_weight = distance[index] + temp->weight;
				if (new_weight < distance[temp->id]) {
					distance[temp->id] = new_weight;
					if(priority_queue_contains(pq, temp->id)){
            priority_queue_decrease_key(pq, temp->id, new_weight);
					} else {
						Vertex *new_node = vertex_new(temp->id);
						new_node->weight = new_weight;
            priority_queue_insert(pq, new_node);
					}
				}
			}
      temp = temp->next;
    }
    if (current) {
      free(current);
    }
	}

  free(visited);
  priority_queue_finish(pq);
	return distance;
}

double rtt(Network *n, int a, int b) {
  double *distances_a = network_distances(n, a);
  double *distances_b = network_distances(n, b);
  double rtt = distances_a[b] + distances_b[a];
  return rtt;
}

double calculate_estimated_rtt(Network *n, int a, int b) {
  int *monitors = network_monitors(n);
  int qtd_monitors = network_qtd_monitors(n);

  double min = rtt(n, a, monitors[0]) + rtt(n, monitors[0], b);

  for (int i = 1; i < qtd_monitors; i++) {
    double new_rtt = rtt(n, a, monitors[i]) + rtt(n, monitors[i], b);
    if (new_rtt < min) {
      min = new_rtt;
    }
  }

  return min;
}

void save_rtt_inflation_to_file(const char *output_file, RttInflation **rtt_inflations, int qtd_inflations) {
  FILE *file = fopen(output_file, "w");
  assert(file != NULL);

  for (int i = 0; i < qtd_inflations; i++) {
    const int server_id = rtt_inflation_server_id(rtt_inflations[i]);
    const int client_id = rtt_inflation_client_id(rtt_inflations[i]);
    const double inflation = rtt_inflation_inflation(rtt_inflations[i]);
    fprintf(file, "%d %d %.16f\n", server_id, client_id, inflation);
  }

  fclose(file);
}
