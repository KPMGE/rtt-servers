#include "../include/utils.h"
#include "../include/priorityQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define MIN(A, B) ((A) < (B) ? (A) : (B))

Network *read_net(const char *file_path) {
  FILE *file = fopen(file_path, "r");
  assert(file != NULL && "Could not open file");

  Network *n = malloc(sizeof(Network));

  fscanf(file, "%d %d", &n->qtd_vertices, &n->qtd_edges);
  fscanf(file, "%d %d %d", &n->qtd_servers, &n->qtd_clients, &n->qtd_monitors);

  n->clients = malloc(sizeof(int) * n->qtd_clients);
  n->servers = malloc(sizeof(int) * n->qtd_servers);
  n->monitors = malloc(sizeof(int) * n->qtd_monitors);
  n->graph = graph_new(n->qtd_vertices);

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
    add_edge(n->graph, x, y, weight);
  }

  fclose(file);

  return n;
}


double * dijkstra(Graph* graph, int src) {
  int amount_vertices = graph_vertices(graph);
	double *distance = malloc(sizeof(double) * amount_vertices);
	int visited[amount_vertices];

	for (int i = 0; i < amount_vertices; i++) {
		distance[i] = INFINITY;
		visited[i] = 0;
	}
	distance[src] = 0.0;
  PriorityQueue *pq = PriorityQueue_init(amount_vertices);
  Vertex *new_node = vertex_new(src);
  new_node->weight = 0.0;

  PriorityQueue_insert(pq, new_node);

	while (!PriorityQueue_empty(pq))  {
		Vertex *current = PriorityQueue_delmin(pq);
		int index = current->id;
		visited[index] = 1;

		double new_weight;
    Vertex *temp = graph_get_vertex(graph, index);
    while (temp) {
			if (visited[temp->id] == 0) {
				new_weight = distance[index] + temp->weight;
				if (new_weight < distance[temp->id]) {
					distance[temp->id] = new_weight;
					if(PriorityQueue_contains(pq, temp->id)){
            PriorityQueue_decrease_key(pq, temp->id, new_weight);
					} else {
						Vertex *newNode = vertex_new(temp->id);
						newNode->weight = new_weight;
            PriorityQueue_insert(pq, newNode);
					}
				}
			}
      temp = temp->next;
    }
	}
	return distance;
}

double rtt(Graph *graph, int a, int b) {
  double *distances_a = dijkstra(graph, a);
  double *distances_b = dijkstra(graph, b);
  return distances_a[b] + distances_b[a];
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

double *calculate_rtts(Graph *graph, int *s1, int s1_size, int *s2, int s2_size) {
  double *rtts = malloc(sizeof(double) * s1_size);

  for (int i = 0; i < s1_size; i++) {
    rtts[i] = rtt(graph, s1[i], s2[i]);
  }

  return rtts;
}
