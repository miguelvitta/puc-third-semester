#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define V int
#define SIZE_BUFFER 256

typedef struct Node {
    V id;
    int creation_window;
    int qtd_windows;
    int progress;
    int added;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Queue;

Queue create_queue(void);
void free_queue(Queue *q);
void add(Queue *q, V id, int creation_window, int qtd_windows, int progress);
Node* get_front(Queue *q);
Node* remove_queue(Queue *q);
int queue_size(Queue *q);
int is_queue_empty(Queue *q);
void clear_queue(Queue *q);

#endif 