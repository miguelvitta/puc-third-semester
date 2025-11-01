#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define V int
#define SIZE_BINARY 64
#define SIZE_BUFFER 128
#define SIZE_EXPRESSION 256

// ===== STACK STRUCTURE =====
typedef struct {
    V *arr;
    int cap;
    int size;
} Stack;

// ===== HELPER FUNCTION =====
int get_int(const char *prompt);

// ===== BASIC STACK OPERATIONS =====
Stack create_stack();
void free_stack(Stack *s);
void push(Stack *s, V value);
V peek(Stack *s);
V pop(Stack *s);
int stack_size(Stack *s);
int is_empty(Stack *s);
void clear_stack(Stack *s);

// ===== DERIVED OPERATIONS =====
void print_stack(Stack *s);
int stacks_equal(Stack *a, Stack *b);
void decimal_to_binary(int x, char *binary_str);
int check_parentheses(char *expression);
int check_delimiters(char *expression);
void reverse_stack(Stack *s);
Stack clone_stack(Stack *s);
int infix_to_postfix(char *infix_expr, char *postfix_expr);

#endif
