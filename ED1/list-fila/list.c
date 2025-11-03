#include "list.h"

// ===== HELPER FUNCTION =====
int get_int(const char *prompt) {
    int value = 0;
    char buffer[SIZE_BUFFER];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *endptr = NULL;
            value = strtol(buffer, &endptr, 10);
            while (*endptr == ' ' || *endptr == '\t') {
                endptr++;
            }
            if (*endptr == '\0' || *endptr == '\n') {
                return value;
            }
            printf("Invalid input. Please enter an integer.\n");
        } else {
            printf("Error reading input.\n");
            exit(1);
        }
    }
}

// ===== BASIC QUEUE OPERATIONS =====

Queue create_queue(void) {
    Queue q;
    q.cap = INITIAL_CAPACITY;
    q.size = 0;
    q.head = 0;
    q.tail = 0;
    q.arr = malloc(q.cap * sizeof(V));
    if (q.arr == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    return q;
}

void free_queue(Queue *q) {
    if (q == NULL) {
        return;
    }
    free(q->arr);
    q->arr = NULL;
    q->cap = 0;
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

void add(Queue *q, V value) {
    if (q == NULL) {
        return;
    }

    if (q->size == q->cap) {
        q->cap = (q->cap * 1.1) + 1;
        V *temp = realloc(q->arr, q->cap * sizeof(V));
        if (temp == NULL) {
            fprintf(stderr, "Reallocation failed.\n");
            exit(1);
        }
        if (q->head != 0) {
            for (int i = 0; i < q->size; i++) {
                temp[i] = q->arr[(q->head + i) % q->cap];
            }
            q->head = 0;
            q->tail = q->size;
        }
        q->arr = temp;
    }

    q->arr[q->tail] = value;
    q->tail = (q->tail + 1) % q->cap;
    q->size++;
}

V get_front(Queue *q) {
    if (q == NULL || q->size == 0) {
        fprintf(stderr, "Error: Queue is empty.\n");
        return 0;
    }
    return q->arr[q->head];
}

V remove_queue(Queue *q) {
    if (q == NULL || q->size == 0) {
        fprintf(stderr, "Error: Queue is empty.\n");
        return 0;
    }
    V value = q->arr[q->head];
    q->head = (q->head + 1) % q->cap;
    q->size--;
    return value;
}

int queue_size(Queue *q) {
    if (q == NULL) {
        return 0;
    }
    return q->size;
}

int is_queue_empty(Queue *q) {
    if (q == NULL) {
        return 1;
    }
    return q->size == 0;
}

void clear_queue(Queue *q) {
    if (q == NULL) {
        return;
    }
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

void print_queue(Queue *q) {
    if (q == NULL || is_queue_empty(q)) {
        printf("empty queue.\n");
        return;
    }

    Queue temp = create_queue();
    while (!is_queue_empty(q)) {
        V val = remove_queue(q);
        printf("%d\n", val);
        add(&temp, val);
    }
    while (!is_queue_empty(&temp)) {
        add(q, remove_queue(&temp));
    }
    free_queue(&temp);
}

int queues_equal(Queue *a, Queue *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (queue_size(a) != queue_size(b)) {
        return 0;
    }

    Queue temp_a = clone_queue(a);
    Queue temp_b = clone_queue(b);
    int equal = 1;

    while (!is_queue_empty(&temp_a) && !is_queue_empty(&temp_b)) {
        if (remove_queue(&temp_a) != remove_queue(&temp_b)) {
            equal = 0;
            break;
        }
    }

    free_queue(&temp_a);
    free_queue(&temp_b);
    return equal;
}

void reverse_queue(Queue *q) {
    if (q == NULL || is_queue_empty(q)) {
        return;
    }

    Queue temp1 = create_queue();
    Queue temp2 = create_queue();

    while (!is_queue_empty(q)) {
        add(&temp1, remove_queue(q));
    }
    while (!is_queue_empty(&temp1)) {
        add(&temp2, remove_queue(&temp1));
    }
    while (!is_queue_empty(&temp2)) {
        add(q, remove_queue(&temp2));
    }

    free_queue(&temp1);
    free_queue(&temp2);
}

Queue clone_queue(Queue *q) {
    Queue clone = create_queue();
    if (q == NULL || is_queue_empty(q)) {
        return clone;
    }

    Queue temp = create_queue();
    while (!is_queue_empty(q)) {
        V val = remove_queue(q);
        add(&temp, val);
        add(&clone, val);
    }
    while (!is_queue_empty(&temp)) {
        add(q, remove_queue(&temp));
    }
    free_queue(&temp);
    return clone;
}
