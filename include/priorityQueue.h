#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdbool.h>

typedef struct priorityQueue PriorityQueue;

void swap(PriorityQueue* p, int i, int j);
void fix_up(PriorityQueue* p, int k);
void fix_down(PriorityQueue* p, int k);
PriorityQueue* PriorityQueue_init(int maxN);
void PriorityQueue_insert(PriorityQueue* p, Vertex* v);
Vertex* PriorityQueue_delmin(PriorityQueue* p);
Vertex* PriorityQueue_min(PriorityQueue* p);
void PriorityQueue_decrease_key(PriorityQueue* p, int id, double value);
bool PriorityQueue_empty(PriorityQueue* p);
int  PriorityQueue_size(PriorityQueue* p);
void PriorityQueue_finish(PriorityQueue* p);

#endif
