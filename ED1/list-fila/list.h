#ifndef LIST_H
#define LIST_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V int
#define SIZE_BUFFER 128
#define INITIAL_CAPACITY 5

// ===== QUEUE STRUCTURE (CIRCULAR ARRAY) =====
typedef struct {
    V *arr;
    int cap;
    int size;
    int head;
    int tail;
} Queue;

// ===== HELPER FUNCTION =====
int get_int(const char *prompt);

// ===== BASIC QUEUE OPERATIONS =====
Queue create_queue(void);
void free_queue(Queue *q);
void add(Queue *q, V value);
V get_front(Queue *q);
V remove_queue(Queue *q);
int queue_size(Queue *q);
int is_queue_empty(Queue *q);
void clear_queue(Queue *q);

// ===== ADVANCED QUEUE OPERATIONS =====
void print_queue(Queue *q);
int queues_equal(Queue *a, Queue *b);
void reverse_queue(Queue *q);
Queue clone_queue(Queue *q);

#endif
