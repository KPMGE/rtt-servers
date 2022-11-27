#include <stdio.h>
#include <stdlib.h>

#include "../include/linkedList.h"
#include "../include/network.h"
#include "../include/priorityQueue.h"

struct network {
  int quantityVertex, quantityEdges, quantityClients, quantityMonitors,
      quantityServers;
  int *idServers;
  int *idClients;
  int *idMonitors;
  LinkedList **linked;
};

struct distances {
  double **vertexDistanceServers;
  double **vertexDistanceClients;
  double **vertexDistanceMonitors;
};

Network *start_network(FILE *in) {
  Network *network = (Network *)malloc(sizeof(Network));
  Distances *distances = (Distances *)malloc(sizeof(Distances));
  read_network(in, network, distances);

  for (int i = 0; i < network->quantityServers; i++) {
    fscanf(in, "%d", &network->idServers[i]);
  }
  for (int i = 0; i < network->quantityClients; i++) {
    fscanf(in, "%d", &network->idClients[i]);
  }
  for (int i = 0; i < network->quantityMonitors; i++) {
    fscanf(in, "%d", &network->idMonitors[i]);
  }
  int idVertex1;
  int idVertex2;
  double cost;

  for (int i = 0; i < network->quantityEdges; i++) {
    fscanf(in, "%d %d %lf", &idVertex1, &idVertex2, &cost);
    network->linked[idVertex1] = linkedList_insert(
        network->linked[idVertex1], vertex_start(idVertex2, cost));
  }
}

double *djkistra_algorithm(int id, int vertex, LinkedList **linked) {
  double *cost = (double *)malloc(sizeof(double) * vertex);
  int *visited = (int *)malloc(sizeof(int) * vertex);
  PriorityQueue *pq = PriorityQueue_init(vertex);

  for (int i = 0; i < vertex; i++) {
    cost[i] = -999;
    visited[i] = 0;
  }

  cost[id] = 0;
  PriorityQueue_insert(pq, vertex_start(id, cost[id]));
  while (!PriorityQueue_empty(pq)) {
    Vertex *v = PriorityQueue_delmin(pq);
    id = vertex_id(v);

    if (!visited[id]) {
      visited[id] = 1;
    }

    for (LinkedList *l = linked[id]; l != NULL; l = linkedList_next(l)) {
      Vertex *aux = linkedList_vertex(l);
      int idConnected = vertex_id(aux);
      int costConnected = vertex_value(aux);

      if (cost[idConnected] < 0) {
        cost[idConnected] = cost[id] + costConnected;
        PriorityQueue_insert(pq, vertex_start(idConnected, cost[idConnected]));
      } else if (cost[idConnected] > (cost[id] + costConnected)) {
        cost[idConnected] = cost[id] + costConnected;
        PriorityQueue_decrease_key(pq, idConnected, cost[idConnected]);
      }
    }
    free(v);
  }
  free(visited);
  PriorityQueue_finish(pq);
  return cost;
}

void read_network(FILE *in, Network *n, Distances *d) {
  int idVertex, idVertex2;
  double cost;

  fscanf(in, "%d %d %d %d %d", &n->quantityVertex, &n->quantityEdges,
         &n->quantityServers, &n->quantityClients, &n->quantityMonitors);

  n->linked = (LinkedList **)malloc(sizeof(LinkedList *) * n->quantityVertex);
  for (int i = 0; i < n->quantityVertex; i++) {
    n->linked = linkedList_start();
  }

  n->idClients = (int *)malloc(sizeof(int *) * n->quantityClients);
  n->idMonitors = (int *)malloc(sizeof(int *) * n->quantityMonitors);
  n->idServers = (int *)malloc(sizeof(int *) * n->quantityServers);

  d->vertexDistanceClients = (int *)malloc(sizeof(int *) * n->quantityClients);
  d->vertexDistanceMonitors =
      (int *)malloc(sizeof(int *) * n->quantityMonitors);
  d->vertexDistanceServers = (int *)malloc(sizeof(int *) * n->quantityServers);
}
