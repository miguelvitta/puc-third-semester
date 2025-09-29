#include "list.h"

#define SIZE_BUFFER 101

// Internal node for a doubly linked list
typedef struct node {
    V value;
    struct node *next;
    struct node *prev;
} node;

// Actual list definition (hidden from list.h)
struct _list {
    node *head;
    node *tail;
    int size;
};

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

// ===== Basic operations =====

list *create_list() {
    list *l = malloc(sizeof(list));
    if (!l) {
        fprintf(stderr, "Error allocating new list.\n");
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void free_list(list **l) {
    if (!l || !*l) {
        return;
    }
    node *current = (*l)->head;
    while (current) {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    free(*l);
    *l = NULL;
}

void insert_end(list *l, V value) {
    node *newNode = malloc(sizeof(node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = l->tail;
    if (l->tail) {
        l->tail->next = newNode;
    } else {
        l->head = newNode;
    }
    l->tail = newNode;
    l->size++;
}

void insert_start(list *l, V value) {
    node *newNode = malloc(sizeof(node));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = l->head;
    if (l->head) {
        l->head->prev = newNode;
    } else {
        l->tail = newNode;
    }
    l->head = newNode;
    l->size++;
}

void insert_at(list *l, V value, int index) {
    if (index <= 0) {
        insert_start(l, value);
        return;
    }
    if (index >= l->size) {
        insert_end(l, value);
        return;
    }
    node *current = l->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    node *newNode = malloc(sizeof(node));
    newNode->value = value;
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    l->size++;
}

void update_at(list *l, V value, int index) {
    if (index < 0 || index >= l->size) {
        return;
    }
    node *current = l->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->value = value;
}

V get_first(list *l) {
    if (l->head == NULL) {
        return 0;
    }
    return l->head->value;
}

V get_last(list *l) {
    if (l->tail == NULL) {
        return 0;
    }
    return l->tail->value;
}

V get_at(list *l, int index) {
    if (index < 0 || index >= l->size) {
        return 0;
    }
    node *current = l->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->value;
}

V remove_first(list *l) {
    if (l->head == NULL) {
        return 0;
    }
    node *temp = l->head;
    V val = temp->value;
    l->head = temp->next;
    if (l->head) {
        l->head->prev = NULL;
    } else {
        l->tail = NULL;
    }
    free(temp);
    l->size--;
    return val;
}

V remove_last(list *l) {
    if (l->tail == NULL) {
        return 0;
    }
    node *temp = l->tail;
    V val = temp->value;
    l->tail = temp->prev;
    if (l->tail) {
        l->tail->next = NULL;
    } else {
        l->head = NULL;
    }
    free(temp);
    l->size--;
    return val;
}

V remove_at(list *l, int index) {
    if (index < 0 || index >= l->size) {
        return 0;
    }
    if (index == 0) {
        return remove_first(l);
    }
    if (index == l->size - 1) {
        return remove_last(l);
    }
    node *current = l->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    V val = current->value;
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    l->size--;
    return val;
}

int list_size(list *l) { return l->size; }

int is_empty(list *l) { return l->size == 0; }

void clear_list(list *l) {
    while (l->head) {
        remove_first(l);
    }
}

// ===== Extra functions =====

void print_list(list *l) {
    node *current = l->head;
    printf("[");
    while (current) {
        printf("%d", current->value);
        if (current->next) {
            printf(", ");
        }
        current = current->next;
    }
    printf("]\n");
}

void print_reverse(list *l) {
    node *current = l->tail;
    printf("[");
    while (current) {
        printf("%d", current->value);
        if (current->prev) {
            printf(", ");
        }
        current = current->prev;
    }
    printf("]\n");
}

// Insert maintaining sorted order (ascending)
void insert_sorted(list *l, V value) {
    if (l->head == NULL || l->head->value >= value) {
        insert_start(l, value);
        return;
    }
    if (l->tail->value <= value) {
        insert_end(l, value);
        return;
    }
    node *current = l->head;
    while (current && current->value < value) {
        current = current->next;
    }
    node *newNode = malloc(sizeof(node));
    newNode->value = value;
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    l->size++;
}

int is_sorted(list *l) {
    if (l->size < 2) {
        return 1;
    }
    node *current = l->head;
    while (current->next) {
        if (current->value > current->next->value) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int is_fibonacci(list *l) {
    if (l->size < 3) {
        return 1;
    }
    node *a = l->head;
    node *b = a->next;
    node *c = b->next;
    while (c) {
        if (c->value != a->value + b->value) {
            return 0;
        }
        a = b;
        b = c;
        c = c->next;
    }
    return 1;
}

// find first position by value
int find_position(list *l, V value) {
    node *current = l->head;
    int index = 0;
    while (current) {
        if (current->value == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

int contains_all(list *l, list *a) {
    node *current = a->head;
    while (current) {
        if (find_position(l, current->value) == -1) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

int lists_equal(list *l, list *a) {
    if (l->size != a->size) {
        return 0;
    }
    node *node1 = l->head;
    node *node2 = a->head;
    while (node1) {
        if (node1->value != node2->value) {
            return 0;
        }
        node1 = node1->next;
        node2 = node2->next;
    }
    return 1;
}

list *union_lists(list *l, list *a) {
    list *result = create_list();
    for (node *c = l->head; c; c = c->next) {
        insert_end(result, c->value);
    }
    for (node *c = a->head; c; c = c->next) {
        if (find_position(result, c->value) == -1) {
            insert_end(result, c->value);
        }
    }
    return result;
}

list *intersection_lists(list *l, list *a) {
    list *result = create_list();
    for (node *c = l->head; c; c = c->next) {
        if (find_position(a, c->value) != -1) {
            insert_end(result, c->value);
        }
    }
    return result;
}

list *difference_lists(list *l, list *a) {
    list *result = create_list();
    for (node *c = l->head; c; c = c->next) {
        if (find_position(a, c->value) == -1) {
            insert_end(result, c->value);
        }
    }
    return result;
}
