#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int vertex;
  struct node *next;
} Node;

Node *node_new(int);

typedef struct {
  int amount_vertices;
  Node **adj_lists;
} Graph;

// Create a node
Node *node_new(int v) {
  Node *new_node = malloc(sizeof(Node));
  new_node->vertex = v;
  new_node->next = NULL;
  return new_node;
}

// Create a graph
Graph *graph_new(int vertices) {
  Graph *graph = malloc(sizeof(Graph));
  graph->amount_vertices = vertices;

  graph->adj_lists = malloc(vertices * sizeof(Node *));

  int i;
  for (i = 0; i < vertices; i++)
    graph->adj_lists[i] = NULL;

  return graph;
}

// Add edge
void add_edge(Graph *graph, int s, int d) {
  // Add edge from s to d
  Node *new_node = node_new(d);
  new_node->next = graph->adj_lists[s];
  graph->adj_lists[s] = new_node;

  // Add edge from d to s
  new_node = node_new(s);
  new_node->next = graph->adj_lists[d];
  graph->adj_lists[d] = new_node;
}

// Print the graph
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

int main() {
  Graph *graph = graph_new(10);
  add_edge(graph, 0, 2);
  add_edge(graph, 0, 3);
  add_edge(graph, 0, 4);
  add_edge(graph, 0, 5);
  add_edge(graph, 0, 8);
  add_edge(graph, 1, 2);
  add_edge(graph, 1, 7);
  add_edge(graph, 2, 0);
  add_edge(graph, 2, 1);
  add_edge(graph, 2, 3);
  add_edge(graph, 2, 5);
  add_edge(graph, 2, 8);
  add_edge(graph, 2, 9);
  add_edge(graph, 3, 0);
  add_edge(graph, 3, 2);
  add_edge(graph, 3, 4);
  add_edge(graph, 3, 6);
  add_edge(graph, 4, 0);
  add_edge(graph, 4, 3);
  add_edge(graph, 4, 6);
  add_edge(graph, 5, 0);
  add_edge(graph, 5, 2);
  add_edge(graph, 5, 7);
  add_edge(graph, 6, 3);
  add_edge(graph, 6, 4);
  add_edge(graph, 7, 1);
  add_edge(graph, 7, 5);
  add_edge(graph, 8, 0);
  add_edge(graph, 8, 2);
  add_edge(graph, 8, 9);
  add_edge(graph, 9, 2);
  add_edge(graph, 9, 8);

  print_graph(graph);
}
