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

// --- Private Helper Functions (Min-Heap Logic) ---

static void swap(V* a, V* b) {
    V temp = *a;
    *a = *b;
    *b = temp;
}

static void sift_up(priority_queue* pq, int index) {
    // Move the element up until the parent is smaller (or we reach the root)
    while (index > 0) {
        int parent_index = (index - 1) / 2;
        
        // If current element is smaller than parent, swap (Min-Heap)
        if (pq->vet[index] < pq->vet[parent_index]) {
            swap(&pq->vet[index], &pq->vet[parent_index]);
            index = parent_index;
        } else {
            break; // Heap property satisfied
        }
    }
}

static void sift_down(priority_queue* pq, int index) {
    int smallest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    // Check if left child exists and is smaller than current smallest
    if (left_child < pq->size && pq->vet[left_child] < pq->vet[smallest]) {
        smallest = left_child;
    }

    // Check if right child exists and is smaller than current smallest
    if (right_child < pq->size && pq->vet[right_child] < pq->vet[smallest]) {
        smallest = right_child;
    }

    // If the smallest is not the current index, swap and continue sifting down
    if (smallest != index) {
        swap(&pq->vet[index], &pq->vet[smallest]);
        sift_down(pq, smallest);
    }
}

// --- Public API Implementations ---

void add(priority_queue* pq, V value) {
    // Check if resizing is necessary
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        V* temp = (V*) realloc(pq->vet, pq->capacity * sizeof(V));
        if (temp == NULL) {
            fprintf(stderr, "Memory allocation error during resize.\n");
            exit(1);
        }
        pq->vet = temp;
    }

    // Insert at the end
    pq->vet[pq->size] = value;
    pq->size++;

    // Restore heap property
    sift_up(pq, pq->size - 1);
}

V get_front(priority_queue* pq) {
    if (is_empty(pq)) {
        printf("Error: Queue is empty.\n");
        return (V)0; // Returning arbitrary value on error
    }
    // In a Min-Heap, the smallest element is always at index 0
    return pq->vet[0];
}

V remove_element(priority_queue* pq) {
    if (is_empty(pq)) {
        printf("Error: Queue is empty.\n");
        return (V)0; // Returning arbitrary value on error
    }

    V min_value = pq->vet[0];

    // Move the last element to the root
    pq->vet[0] = pq->vet[pq->size - 1];
    pq->size--;

    // Restore heap property if there are elements left
    if (pq->size > 0) {
        sift_down(pq, 0);
    }

    return min_value;
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

// --- Question 2: Function Implementations ---

void print_queue(priority_queue* pq) {
    if (pq == NULL) return;

    // Create a temporary queue to hold elements while printing
    priority_queue* temp = create_priority_queue();

    // 1. Drain the original queue, print elements, and store them in temp
    while (!is_empty(pq)) {
        V val = remove_element(pq);
        printf("%d ", val); // Assuming V is int
        add(temp, val);
    }
    printf("\n");

    // 2. Restore the original queue from temp
    while (!is_empty(temp)) {
        add(pq, remove_element(temp));
    }

    // 3. Clean up
    free_priority_queue(temp);
}

int queues_equal(priority_queue* a, priority_queue* b) {
    if (a == NULL || b == NULL) return 0;
    
    // Quick check on size
    if (get_size(a) != get_size(b)) {
        return 0;
    }

    // Create temp queues to store elements during comparison
    priority_queue* temp_a = create_priority_queue();
    priority_queue* temp_b = create_priority_queue();
    
    int are_equal = 1; // Assume true until proven false

    // 1. Compare elements one by one
    while (!is_empty(a)) {
        V val_a = remove_element(a);
        V val_b = remove_element(b);

        if (val_a != val_b) {
            are_equal = 0;
        }

        // Save elements to restore later
        add(temp_a, val_a);
        add(temp_b, val_b);
    }

    // 2. Restore both original queues
    while (!is_empty(temp_a)) {
        add(a, remove_element(temp_a));
    }
    while (!is_empty(temp_b)) {
        add(b, remove_element(temp_b));
    }

    // 3. Clean up
    free_priority_queue(temp_a);
    free_priority_queue(temp_b);

    return are_equal;
}

priority_queue* clone_queue(priority_queue* pq) {
    if (pq == NULL) return NULL;

    priority_queue* clone = create_priority_queue();
    priority_queue* temp = create_priority_queue();

    // 1. Move elements from source to BOTH clone and temp
    while (!is_empty(pq)) {
        V val = remove_element(pq);
        add(clone, val);
        add(temp, val);
    }

    // 2. Restore the source queue from temp
    while (!is_empty(temp)) {
        add(pq, remove_element(temp));
    }

    // 3. Clean up temp
    free_priority_queue(temp);

    return clone;
}

void sort_vector_ascending(V* vector, int n) {
    if (vector == NULL || n <= 0) return;

    priority_queue* pq = create_priority_queue();

    // 1. Add all vector elements to the min-heap
    for (int i = 0; i < n; i++) {
        add(pq, vector[i]);
    }

    // 2. Remove elements. Min-heap removes smallest first -> Ascending order.
    for (int i = 0; i < n; i++) {
        vector[i] = remove_element(pq);
    }

    free_priority_queue(pq);
}

void sort_vector_descending(V* vector, int n) {
    if (vector == NULL || n <= 0) return;

    priority_queue* pq = create_priority_queue();

    // 1. Add all vector elements to the min-heap
    for (int i = 0; i < n; i++) {
        add(pq, vector[i]);
    }

    // 2. Remove elements. Min-heap removes smallest first.
    // To get descending order, fill the vector from the END (index n-1) to the START (0).
    for (int i = n - 1; i >= 0; i--) {
        vector[i] = remove_element(pq);
    }

    free_priority_queue(pq);
}