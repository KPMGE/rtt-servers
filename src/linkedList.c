#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"

struct linkedList {
	Vertex* v;
	LinkedList* next;
};

LinkedList* linkedList_start() {
	LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
	return l;
}

LinkedList* linkedList_insert(LinkedList* l, Vertex* v) {
	LinkedList* l = (LinkedList*)malloc(sizeof(LinkedList));
	l->v = v;
	l->next = l;
	return l;
}

LinkedList* linkedList_next(LinkedList* l) {
	return l->next;
}

LinkedList* linkedList_vertex(LinkedList* l) {
	return l->v;
}