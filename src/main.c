#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "../include/priorityQueue.h"
#include "../include/graph.h"

typedef struct {
  int qtd_vertices, qtd_edges, qtd_servers, qtd_clients, qtd_monitors;
  int *servers, *clients, *monitors;
  Graph *graph;
} Network;

Network *read_net(const char *file_path);
double * dijkstra(Graph* graph, int src); 
double rtt(Graph *graph, int a, int b);

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

  double *distances = dijkstra(n->graph, 3);
  printf("\ndistances: \n");
  for (int i = 0; i < n->qtd_vertices; i++) {
    printf("%.2f\n", distances[i]);
  }

  printf("\nrtt(0, 3): %.2f\n", rtt(n->graph, 0, 3));
}

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
	distance[src - 1] = 0.0;
  PriorityQueue *pq = PriorityQueue_init(amount_vertices);
  Vertex *new_node = vertex_new(src);
  new_node->weight = 0.0;

  PriorityQueue_insert(pq, new_node);

	while (!PriorityQueue_empty(pq))  {
		Vertex *current = PriorityQueue_delmin(pq);
		int index = current->id;
		visited[index - 1] = 1;

		double new_weight;
    Vertex *temp = graph_get_vertex(graph, index);
    while (temp) {
			if (visited[temp->id - 1] == 0) {
				new_weight = distance[index - 1] + temp->weight;
				if (new_weight < distance[temp->id - 1]) {
					distance[temp->id - 1] = new_weight;
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
  return distances_a[b] + distances_b[b];
}
