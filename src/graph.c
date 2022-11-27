#include "../include/graph.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int vertex;
	double weight; 
  struct node *next;
} Node;

struct graph {
  int amount_vertices;
  Node **adj_lists;
};

static Node *node_new(int v) {
  Node *new_node = malloc(sizeof(Node));
  new_node->vertex = v;
  new_node->next = NULL;
  new_node->weight = INFINITY;
  return new_node;
}

Graph *graph_new(int vertices) {
  Graph *graph = malloc(sizeof(Graph));
  graph->amount_vertices = vertices;

  graph->adj_lists = malloc(vertices * sizeof(Node *));

  for (int i = 0; i < vertices; i++) {
    graph->adj_lists[i] = NULL;
  }

  return graph;
}

int graph_vertices(Graph *graph) {
  return graph->amount_vertices;
}

void add_edge(Graph *graph, int src, int dest, double weight) {
  Node *new_node = node_new(dest);
  new_node->next = graph->adj_lists[src];
  graph->adj_lists[src] = new_node;
  new_node = node_new(src);
  new_node->next = graph->adj_lists[dest];
  graph->adj_lists[dest] = new_node;
}

void print_graph(Graph *graph) {
  int v;
  for (v = 0; v < graph->amount_vertices; v++) {
    Node *temp = graph->adj_lists[v];
    printf("\n Vertex %d\n: ", v);
    while (temp) {
      printf("%d -> ", temp->vertex);
      temp = temp->next;
    }
    printf("\n");
  }
}
