#include "../include/graph.h"
#include "../include/vertex.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct graph {
  int amount_vertices;
  Vertex **adj_lists;
};

Graph *graph_new(int vertices) {
  Graph *graph = malloc(sizeof(Graph));
  graph->amount_vertices = vertices;

  graph->adj_lists = malloc(vertices * sizeof(Vertex *));

  for (int i = 0; i < vertices; i++) {
    graph->adj_lists[i] = NULL;
  }

  return graph;
}

int graph_vertices(Graph *graph) {
  return graph->amount_vertices;
}

Vertex *graph_get_vertex(Graph *graph, int index) {
  return graph->adj_lists[index];
}

void add_edge(Graph *graph, int src, int dest, double weight) {
  Vertex *new_node = vertex_new(dest);
  new_node->weight = weight;
  new_node->next = graph->adj_lists[src];
  graph->adj_lists[src] = new_node;
  new_node = vertex_new(src);
  new_node->next = graph->adj_lists[dest];
  graph->adj_lists[dest] = new_node;
}

void print_graph(Graph *graph) {
  for (int v = 0; v < graph->amount_vertices; v++) {
    Vertex *temp = graph->adj_lists[v];
    printf("\n Vertex %d\n: ", v);
    while (temp) {
      printf("%d(%.2f) -> ", temp->id, temp->weight);
      temp = temp->next;
    }
    printf("\n");
  }
}

void graph_free(Graph *graph) {
  for (int v = 0; v < graph->amount_vertices; v++) {
    Vertex *temp = graph->adj_lists[v];
    while (temp) {
      Vertex *aux = temp;
      temp = temp->next;
      free(aux);
    }
  }
  free(graph->adj_lists);
  free(graph);
}
