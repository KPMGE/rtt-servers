#ifndef VERTEX_H
#define VERTEX_H

typedef struct vertex Vertex;

Vertex* vertex_start(int id, double value);
double vertex_value(Vertex* p);
int vertex_id(Vertex* p);
void vertex_set_value(Vertex* p, double value);
void vertex_set_id(Vertex* p, int id);
void vertex_free(Vertex* p);
int vertex_more(Vertex* p, Vertex* q);
void vertex_exch(Vertex** p, Vertex** q);


#endif
