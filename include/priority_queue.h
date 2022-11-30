#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdbool.h>
#include "vertex.h"

typedef struct priority_queue PriorityQueue;

PriorityQueue* priority_queue_init(int maxN);
void priority_queue_insert(PriorityQueue* p, Vertex* v);
Vertex* priority_queue_delmin(PriorityQueue* p);
Vertex* priority_queue_min(PriorityQueue* p);
void priority_queue_decrease_key(PriorityQueue* p, int id, double value);
bool priority_queue_empty(PriorityQueue* p);
int  priority_queue_size(PriorityQueue* p);
void priority_queue_finish(PriorityQueue* p);
int priority_queue_contains(PriorityQueue *pq, int key);

#endif
