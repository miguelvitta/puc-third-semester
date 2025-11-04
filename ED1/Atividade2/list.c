#include "list.h"

Queue create_queue(void) {
    Queue q = { .head = NULL, .tail = NULL, .size = 0 };
    return q;
}

void free_queue(Queue *q) {
    if (q == NULL) { return; }
    clear_queue(q);
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void add(Queue *q, V id, int creation_window, int qtd_windows, int progress) {
    if (q == NULL) { return; }

    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    new_node->id = id;
    new_node->creation_window = creation_window;
    new_node->qtd_windows = qtd_windows;
    new_node->progress = 0;
    new_node->added = 0;
    new_node->next = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    q->size++;
}

Node* get_front(Queue *q) {
    if (q == NULL || q->head == NULL) {
        fprintf(stderr, "Error: Queue is empty.\n");
        return NULL;
    }
    return q->head;
}

Node* remove_queue(Queue *q) {
    if (q == NULL || q->head == NULL) {
        fprintf(stderr, "Error: Queue is empty.\n");
        exit(1);
    }
    
    Node *old = q->head;
    q->head = old->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(old);
    q->size--;
    return old;
}

int queue_size(Queue *q) {
    if (q == NULL) { return 0; }
    return q->size;
}

int is_queue_empty(Queue *q) {
    if (q == NULL) { return 1; }
    return q->size == 0;
}

void clear_queue(Queue *q) {
    if (q == NULL) { return; }
    while (!is_queue_empty(q)) {
        free(remove_queue(q));
    }
}

