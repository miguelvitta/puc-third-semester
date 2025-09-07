#include "list.h"

list *create_list() {
    list *l = malloc(sizeof(list));
    if (l == NULL) {
        fprintf(stderr, "Error allocating new list.\n");
        return NULL;
    }
    l->size = 0;
    l->capacity = 5;
    l->array = malloc(sizeof(V) * l->capacity);
    if (l->array == NULL) {
        fprintf(stderr, "Error allocating new list.\n");
        free_list(l);
        return NULL;
    }

    return l;
}

void free_list(list *l) {
    if (l == NULL) {
        fprintf(stderr, "List is already NULL.\n");   
        return;     
    }
    free(l->array);
    free(l);
    // avoid dangling pointer. Not really a problem here, but it's good practice, and if I understood it right, the way I implement with full freedom to choose functions can actually cause the dangling pointer. Must remember to ask Max
    l = NULL;  
}

void insert_end(list *l, V value) {
    insert_at(l, value, l->size);
}

void insert_start(list *l, V value) {
    insert_at(l, value, 0);
}

void insert_at(list *l, V value, int index) {
    if (index < 0 || index > l->size) {
        fprintf(stderr, "Invalid index %d. Valid range: 0 to %d\n", index, l->size);
        return;
    }

    // Block for resizing (if needed) and inserting when this happen
    if (l->size == l->capacity) {
        // gows 10% + 1(to ensure it grows at minus 10 capacity)
        int new_capacity = (int)(l->capacity * 1.1) + 1;
        V *new_array = malloc(sizeof(V) * new_capacity);
        if (new_array == NULL) {
            fprintf(stderr, "Memory allocation failed during resizing.\n");
            return;
        }

        // Now we will copy the elements and insert the new value during the copying process
        for (int i = 0; i < index; i++) {
            new_array[i] = l->array[i];
        }
        new_array[index] = value;
        for (int i = index; i < l->size; i++) {
            new_array[i + 1] = l->array[i];
        }

        // now for the cleanup
        free(l->array);
        l->array = new_array;
        l->capacity = new_capacity;
        l->size++;
        return;
    }

    // if no resizing is needed, just shift to the right and insert new element
    for (int i = l->size; i > index; i--) {
        l->array[i] = l->array[i - 1];
    }
    l->array = value;
    l->size++;
}

void update_at(list *l, V value, int index) {
    if (index < 0 || index > l->size) {
        fprintf(stderr, "Invalid index %d. Valid range: 0 to %d\n", index, l->size);
        return;
    }
    l->array[index] = value;
}

V get_first(list *l) {
    if (l->size == 0) {
        fprintf(stderr, "List is empty\n");
        return 0;
    }
    get_at(l, 0);
}

V get_last(list *l) {
    if (l->size == 0) {
        fprintf(stderr, "List is empty\n");
        return 0;
    }
    get_at(l, l->size - 1);
}

V get_at(list *l, int index) {
    if (index < 0 || index >= l-> size) {
        fprintf(stderr, "Invalid index %d. Valid range is 0 to %s.\n", index, l->size - 1);
        return 0;
    }
    return l->array[index];
}

V remove_first(list *l) {
    if (l->size == 0) {
        fprintf(stderr, "The list is empty and nothing can be removed\n");
        return 0;
    }
    return remove_at(l, 0);
}

V remove_last(list *l) {
    if (l->size == 0) {
        fprintf(stderr, "The list is empty and nothing can be removed\n");
        return 0;
    }
    return remove_at(l, l->size - 1);
}

V remove_at(list *l, int index) {
    if (index < 0 || index >= l->size) {
        fprintf(stderr, "Invalid index %d. Valid range: 0 to %d\n", index, l->size - 1);
        return 0;
    }
    int value_removed = l->array[index];
    for (int i = index; i < l->size - 1; i++) {
        l->array[i] = l->array[i + 1];
    }
    l->size--;
    return value_removed;
}

int list_size(list *l) {
    return l->size;
}

int is_empty(list *l) {
    return l->size == 0;
}

void clear_list(list *l) {
    // I had first gone for a full wipe here, but I decided to separate responsibilities, and if I want a full wipe I will use free_list
    l->size = 0;
}

void print_list(list *l) {
    if (l->size == 0) {
        fprintf(stderr, "The list is empty, there is nothing to print.\n");
        return;
    }
    for (int i = 0; i < l->size; i++) {
        printf("%d", l->array[i]);
        if (i < l->size - 1) {
            printf(", ");
        }
    }
    printf("\n");
}

void print_reverse(list *l) {
    if (l->size == 0) {
        fprintf(stderr, "The list is empty, there is nothing to print.\n");
        return;
    }
    for (int i = l->size - 1; i >= 0; i--) {
        printf("%d", l->array[i]);
        if (i > 0) {
            printf(", ");
        }
    }
    printf("\n");
}

void insert_sorted(list *l, V value) {
    if (l->size == 0) {
        insert_at(l, value, 0);
        return;
    }
    int i = 0;
    while (i < l->size && l->array[i] < value) {
        i++;
    }
    insert_at(l, value, i);
}

int is_sorted(list *l) {
    if (l->size == 0 || l->size == 1) {
        return 1;
    }
    for (int i = 0; i < l->size - 1; i++) {
        if (l->array[i] > l->array[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int is_fibonacci(list *l) {
    // if it's empty or it has only 1 element, let's consider it is fibonacci
    if (l->size == 0 || l->size == 1) {
        return 1;
    }

    for (int i = 2; i < l->size; i++) {
        if (l->array[i] != l->array[i - 1] + l->array[i - 2]) {
            return 0;
        }
    }
    return 1;
}

int find_position(list *l, V value) {
    if (l == NULL || l->size == 0) {
        return -1;
    }

    for (int i = 0; i < l->size; i++) {
        if (l->array[i] == value) {
            return i;
        }
    }
    return -1;
}

int contains_all(list *l, list *a) {
    // TODO: implement
    return 0;
}

int lists_equal(list *l, list *a) {
    // TODO: implement
    return 0;
}

list union_lists(list *l, list *a) {
    // TODO: implement
    list result;
    return result;
}

list intersection_lists(list *l, list *a) {
    // TODO: implement
    list result;
    return result;
}

list difference_lists(list *l, list *a) {
    // TODO: implement
    list result;
    return result;
}
