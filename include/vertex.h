#ifndef VERTEX_H
#define VERTEX_H

typedef struct vertex {
  int id;
  double weight;
  struct vertex *next;
} Vertex;

double vertex_weight(Vertex *p);
int vertex_id(Vertex *p);
void vertex_set_weight(Vertex *p, double weight);
void vertex_set_id(Vertex *p, int id);
void vertex_free(Vertex *p);
int vertex_more(Vertex *p, Vertex *q);
void vertex_exch(Vertex **p, Vertex **q);
Vertex *vertex_new(int v);

#endif
