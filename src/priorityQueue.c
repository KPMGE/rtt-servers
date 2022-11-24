#include <stdio.h>
#include <stdlib.h>

#include "priorityQueue.h"
#include "vertex.h"

struct priorityQueue {
	Vertex** array;
	int* map;
	int quantity;
};

void swap(PriorityQueue* p, int i, int j) {
	item_exch(&p->array[i], &p->array[j]);
	p->map[item_id(p->array[i])] = i;
	p->map[item_id(p->array[j])] = j;
}

void fix_up(PriorityQueue* p, int k) {
    while (k > 1 && item_more(p->array[k / 2], p->array[k])) {
        swap(p, k, k / 2);
        k = k / 2;
    }
}

void fix_down(PriorityQueue* p, int k) {
    while (2 * k <= p->quantity) {
        int j = 2 * k;
        if (j < p->quantity && item_more(p->array[j], p->array[j + 1])) {
            j++;
        }
        if (!item_more(p->array[k], p->array[j])) {
            break;
        }
        swap(p, k, j);
        k = j;
    }
}

PriorityQueue* PriorityQueue_init(int maxN) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (Vertex**)malloc((maxN + 1) * sizeof(Vertex*));
    pq->map = (int*)malloc((maxN + 1) * sizeof(int));
    pq->quantity = 0;
    return pq;
}

void PriorityQueue_insert(PriorityQueue* p, Vertex* v) {
    p->quantity++;
    p->array[p->quantity] = v;
    p->map[item_id(v)] = p->quantity;
    fix_up(p, p->quantity);
}

Vertex* PriorityQueue_delmin(PriorityQueue* p) {
    Vertex* min = p->array[1];
    swap(p, 1, p->quantity);
    p->quantity--;
    fix_down(p, 1);
    return min;
}

Vertex* PriorityQueue_min(PriorityQueue* p) {
    return p->array[1];
}

void PriorityQueue_decrease_key(PriorityQueue* p, int id, double value) {
    int i = p->map[id];
    item_setValue(p->array[i], value);
    fix_up(p, i);
}

bool PriorityQueue_empty(PriorityQueue* p) {
    return p->quantity == 0;
}

int  PriorityQueue_size(PriorityQueue* p) {
    return p->quantity;
}

void PriorityQueue_finish(PriorityQueue* p) {
    free(p->array);
    free(p->map);
    free(p);
}