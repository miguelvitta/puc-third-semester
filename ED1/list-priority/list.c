#include "list.h"

// --- Question 1: Function Implementations (Scaffolding) ---

priority_queue* create_priority_queue(void) {
    priority_queue* pq = (priority_queue*) malloc(sizeof(priority_queue));
    if (pq == NULL) {
        fprintf(stderr, "Memory allocation failed for struct.\n");
        exit(1);
    }
    pq->vet = (V*) malloc(INITIAL_CAPACITY * sizeof(V));
    if (pq->vet == NULL) {
        fprintf(stderr, "Memory allocation failed for vector.\n");
        free(pq);
        exit(1);
    }
    pq->capacity = INITIAL_CAPACITY;
    pq->size = 0;

    return pq;
}

void free_priority_queue(priority_queue* pq) {
    if (pq != NULL) {
        free(pq->vet);
        free(pq);
    }
}

void add(priority_queue* pq, V value) {
    // TODO: Implement the 'add'
}

V get_front(priority_queue* pq) {
    // TODO: Implement 'get_front'
}

V remove_element(priority_queue* pq) {
    // TODO: Implement 'remove_element'
}

int get_size(priority_queue* pq) {
    if (pq == NULL) return 0;
    return pq->size;
}

int is_empty(priority_queue* pq) {
    if (pq == NULL) return 1;
    return (pq->size == 0);
}

void clear(priority_queue* pq) {
    if (pq != NULL) {
        pq->size = 0;
    }
}

// --- Question 2: Function Implementations (Scaffolding) ---

void print_queue(priority_queue* pq) {
    // TODO: Implement 'print_queue' using only Q1 API
}

int queues_equal(priority_queue* a, priority_queue* b) {
    // TODO: Implement 'queues_equal' using only Q1 API
}

priority_queue* clone_queue(priority_queue* pq) {
    // TODO: Implement 'clone_queue' using only Q1 API
}

void sort_vector_ascending(V* vector, int n) {
    // TODO: Implement 'sort_vector_ascending'
}

void sort_vector_descending(V* vector, int n) {
    // TODO: Implement 'sort_vector_descending'
}