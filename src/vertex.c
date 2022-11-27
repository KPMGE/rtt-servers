#include <stdio.h>
#include <stdlib.h>

#include "../include/vertex.h"

struct vertex {
  int id;
  double value;
};

Vertex *vertex_start(int id, double value) {
  Vertex *v = (Vertex *)malloc(sizeof(Vertex));
  v->id = id;
  v->value = value;
  return v;
}

double vertex_value(Vertex *p) { return p->value; }

int vertex_id(Vertex *p) { return p->id; }

void vertex_set_value(Vertex *p, double value) { p->value = value; }

void vertex_set_id(Vertex *p, int id) { p->id = id; }

void vertex_free(Vertex *p) { free(p); }

int vertex_more(Vertex *p, Vertex *q) { return p->value > q->value; }

void vertex_exch(Vertex **p, Vertex **q) {
  Vertex *t = *p;
  *p = *q;
  *q = t;
}
