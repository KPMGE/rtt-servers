#include <stdio.h>
#include <stdlib.h>

#include "../include/linkedList.h"
#include "../include/vertex.h"

struct linkedList {
  Vertex *v;
  LinkedList *next;
};

LinkedList *linkedList_start() {
  LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
  return l;
}

LinkedList *linkedList_insert(LinkedList *l, Vertex *v) {
  LinkedList *k = (LinkedList *)malloc(sizeof(LinkedList));
  l->v = v;
  l->next = k;
  return l;
}

LinkedList *linkedList_next(LinkedList *l) { return l->next; }

Vertex *linkedList_vertex(LinkedList *l) { return l->v; }
