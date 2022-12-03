#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/priority_queue.h"
#include "../include/vertex.h"

struct priority_queue {
  Vertex **array;
  int *map;
  int n, size;
};

static void swap(PriorityQueue *p, int i, int j) {
  vertex_exch(&p->array[i], &p->array[j]);
  p->map[vertex_id(p->array[i])] = i;
  p->map[vertex_id(p->array[j])] = j;
}

static void fix_up(PriorityQueue *p, int k) {
  while (k > 1 && vertex_more(p->array[k / 2], p->array[k])) {
    swap(p, k, k / 2);
    k = k / 2;
  }
}

static void fix_down(PriorityQueue *p, int k) {
  while (2 * k <= p->n) {
    int j = 2 * k;
    if (j < p->n && vertex_more(p->array[j], p->array[j + 1])) {
      j++;
    }
    if (!vertex_more(p->array[k], p->array[j])) {
      break;
    }
    swap(p, k, j);
    k = j;
  }
}

PriorityQueue *priority_queue_init(int maxN) {
  PriorityQueue *pq = malloc(sizeof(PriorityQueue));
  pq->array = calloc((maxN + 1), sizeof(Vertex *));
  pq->map = malloc((maxN + 1) * sizeof(int));
  pq->n = 0;
  pq->size = maxN;
  return pq;
}

void priority_queue_insert(PriorityQueue *p, Vertex *v) {
  p->n++;
  p->array[p->n] = v;
  p->map[vertex_id(v)] = p->n;
  fix_up(p, p->n);
}

Vertex *priority_queue_delmin(PriorityQueue *p) {
  Vertex *min = p->array[1];
  swap(p, 1, p->n);
  p->n--;
  fix_down(p, 1);
  return min;
}

Vertex *priority_queue_min(PriorityQueue *p) { return p->array[1]; }

void priority_queue_decrease_key(PriorityQueue *p, int id, double weight) {
  int i = p->map[id];
  vertex_set_weight(p->array[i], weight);
  fix_up(p, i);
}

bool priority_queue_empty(PriorityQueue *p) { return p->n == 0; }

int priority_queue_size(PriorityQueue *p) { return p->size; }

void priority_queue_finish(PriorityQueue *p) {
  free(p->array);
  free(p->map);
  free(p);
}

int priority_queue_contains(PriorityQueue *pq, int key) {
  for (int i = 0; i < pq->n; i++) {
    if (!pq->array[i])
      return false;
    if (pq->array[i]->id == key) {
      return true;
    }
  }
  return false;
}
