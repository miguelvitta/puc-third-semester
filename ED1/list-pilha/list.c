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

// ===== BASIC STACK OPERATIONS =====

Stack create_stack() {
    Stack s;
    // TODO: allocate memory, initialize attributes
    return s;
}

void free_stack(Stack *s) {
    // TODO: free allocated memory
}

void push(Stack *s, V value) {
    // TODO: push element onto stack
}

V peek(Stack *s) {
    // TODO: return top element
    return 0;
}

V pop(Stack *s) {
    // TODO: remove and return top element
    return 0;
}

int stack_size(Stack *s) {
    // TODO: return number of elements
    return 0;
}

int is_empty(Stack *s) {
    // TODO: return 1 if empty, 0 otherwise
    return 0;
}

void clear_stack(Stack *s) {
    // TODO: clear all elements
}

// ===== DERIVED OPERATIONS =====

void print_stack(Stack *s) {
    // TODO: print stack elements from top to bottom
}

int stacks_equal(Stack *a, Stack *b) {
    // TODO: compare if stacks are equal
    return 0;
}

void decimal_to_binary(int x, char *binary_str) {
    // TODO: convert decimal number to binary using a stack
}

int check_parentheses(char *expression) {
    // TODO: check if parentheses are balanced
    return 0;
}

int check_delimiters(char *expression) {
    // TODO: check if (), {}, [] are balanced
    return 0;
}

void reverse_stack(Stack *s) {
    // TODO: reverse the stack
}

Stack clone_stack(Stack *s) {
    Stack clone;
    // TODO: create and return a clone of the stack
    return clone;
}

int infix_to_postfix(char *infix_expr, char *postfix_expr) {
    // TODO: convert infix expression to postfix
    return 0;
}
