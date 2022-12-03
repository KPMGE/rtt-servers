#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "../include/vertex.h"

Vertex *vertex_new(int v) {
  Vertex *new_node = malloc(sizeof(Vertex));
  new_node->id = v;
  new_node->next = NULL;
  new_node->weight = INFINITY;
  return new_node;
}

double vertex_weight(Vertex *p) { return p->weight; }

int vertex_id(Vertex *p) { return p->id; }

void vertex_set_weight(Vertex *p, double weight) { p->weight = weight; }

void vertex_set_id(Vertex *p, int id) { p->id = id; }

void vertex_free(Vertex *p) { 
  free(p);
}

int vertex_more(Vertex *p, Vertex *q) { return p->weight > q->weight; }

void vertex_exch(Vertex **p, Vertex **q) {
  assert(p != NULL);
  assert(q != NULL);
  Vertex *t = *p;
  *p = *q;
  *q = t;
}
