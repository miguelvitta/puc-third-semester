#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The data type to be stored in the priority queue.
 */
#define V int

/**
 * @brief The initial capacity of the heap array.
 */
#define INITIAL_CAPACITY 5

/**
 * @brief The priority queue structure (min-heap implementation).
 */
typedef struct {
    V* vet; // Array storing heap elements
    int capacity; // Size of the allocated array
    int size; // Number of elements in the queue
} priority_queue;

// --- Question 1: Basic Priority Queue Functions ---

/**
 * @brief Creates and initializes an empty priority queue.
 */
priority_queue* create_priority_queue(void);

/**
 * @brief Frees all dynamically allocated memory for the priority queue.
 */
void free_priority_queue(priority_queue* pq);

/**
 * @brief Adds a new value to the priority queue, maintaining the min-heap property.
 */
void add(priority_queue* pq, V value);

/**
 * @brief Returns the element with the highest priority (the minimum value)
 * without removing it.
 */
V get_front(priority_queue* pq);

/**
 * @brief Removes and returns the element with the highest priority (the minimum value).
 */
V remove_element(priority_queue* pq);

/**
 * @brief Returns the number of elements currently in the queue.
 */
int get_size(priority_queue* pq);

/**
 * @brief Checks if the priority queue is empty.
 */
int is_empty(priority_queue* pq);

/**
 * @brief Removes all elements from the priority queue.
 */
void clear(priority_queue* pq);

// --- Question 2: Advanced Operations ---

/**
 * @brief Prints all elements in priority order.
 * Must restore the queue to its original state.
 */
void print_queue(priority_queue* pq);

/**
 * @brief Checks if two priority queues contain the same elements.
 */
int queues_equal(priority_queue* a, priority_queue* b);

/**
 * @brief Creates a new, independent clone of a priority queue.
 * Must restore the original queue to its original state.
 */
priority_queue* clone_queue(priority_queue* pq);

/**
 * @brief Sorts an array in ascending order using a priority queue.
 */
void sort_vector_ascending(V* vector, int n);

/**
 * @brief Sorts an array in descending order using a priority queue.
 */
void sort_vector_descending(V* vector, int n);


#endif