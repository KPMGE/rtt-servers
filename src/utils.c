#include "../include/utils.h"
#include "../include/priority_queue.h"
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
						Vertex *newNode = vertex_new(temp->id);
						newNode->weight = new_weight;
            priority_queue_insert(pq, newNode);
					}
				}
			}
      temp = temp->next;
    }
	}

  priority_queue_finish(pq);
  free(visited);
	return distance;
}

double rtt(Graph *graph, int a, int b) {
  double *distances_a = dijkstra(graph, a);
  double *distances_b = dijkstra(graph, b);
  double rtt = distances_a[b] + distances_b[a];
  free(distances_a);
  free(distances_b);
  return rtt;
}

double calculate_estimated_rtt(Graph *graph, int a, int b, int *monitors, int qtd_monitors) {
  double min = rtt(graph, a, monitors[0]) + rtt(graph, monitors[0], b);

  for (int i = 1; i < qtd_monitors; i++) {
    double new_rtt = rtt(graph, a, monitors[i]) + rtt(graph, monitors[i], b);
    if (new_rtt < min) {
      min = new_rtt;
    }
  }

  return min;
}
