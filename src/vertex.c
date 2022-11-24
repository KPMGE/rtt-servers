#include <stdio.h>
#include <stdlib.h>

#include "vertex.h"

struct vertex {
	int id;
	double value;
};

Vertex* vertex_start(int id, double value) {
	Vertex* v = (Vertex*)malloc(sizeof(Vertex));
	v->id = id;
	v->value = value;
	return v;
}

double vertex_value(Vertex* p) {
	return p->value;
}

int vertex_id(Vertex* p) {
	return p->id;
}

void vertex_set_value(Vertex* p, double value) {
	p->value = value;
}

void vertex_set_id(Vertex* p, int id) {
	p->id = id;
}

void vertex_free(Vertex* p) {
	free(p);
}
