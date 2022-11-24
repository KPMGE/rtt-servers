#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "vertex.h"

typedef struct linkedList LinkedList;

LinkedList* linkedList_start();

LinkedList* linkedList_insert(LinkedList* l, Vertex* v);

LinkedList* linkedList_next(LinkedList* l);

LinkedList* linkedList_vertex(LinkedList* l);


#endif
