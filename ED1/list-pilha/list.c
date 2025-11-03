#include "list.h"

#define ASCII_PARENTHESIS_OPEN 40   // '('
#define ASCII_PARENTHESIS_CLOSE 41  // ')'
#define ASCII_BRACKET_OPEN 91       // '['
#define ASCII_BRACKET_CLOSE 93      // ']'
#define ASCII_BRACE_OPEN 123        // '{'
#define ASCII_BRACE_CLOSE 125       // '}'
#define OP_PLUS '+'
#define OP_MINUS '-'
#define OP_MULT '*'
#define OP_DIV '/'
#define OP_EXP '^'

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

Stack create_stack(void) {
    Stack s;
    s.cap = INITIAL_CAPACITY;
    s.size = 0;
    s.arr = malloc(s.cap * sizeof(V));
    if (s.arr == NULL) {
        fprintf(stderr, "Memory Allocation failed.\n");
        exit(1);
    }
    return s;
}

void free_stack(Stack *s) {
    if (s == NULL) {
        return;
    }
    free(s->arr);
    s->arr = NULL;
    s->cap = 0;
    s->size = 0;
}

void push(Stack *s, V value) {
    if (s == NULL) {
        return;
    }

    if (s->size == s->cap) {
        s->cap = (s->cap * 1.1) + 1;
        V *temp = realloc(s->arr, s->cap * sizeof(V));
        if (temp == NULL) {
            fprintf(stderr, "Realocation failed.\n");
            exit(1);
        }
        s->arr = temp;
    }
    s->arr[s->size++] = value;
}

V peek(Stack *s) {
    if (s == NULL || s->size == 0) {
        fprintf(stderr, "Error: Stack is empty.\n");
        return 0;
    }
    return s->arr[s->size - 1];
}

V pop(Stack *s) {
    if (s == NULL || s->size == 0) {
        fprintf(stderr, "Error: Stack is empty.\n");
        return 0;
    }
    s->size--;
    return s->arr[s->size];
}

int stack_size(Stack *s) {
    if (s == NULL) {
        return 0;
    }
    return s->size;
}

int is_empty(Stack *s) {
    if (s == NULL) {
        return 1;
    }
    return s->size == 0;
}

void clear_stack(Stack *s) {
    if (s == NULL) {
        return;
    }
    s->size = 0;
}

// ===== ADVANCED STACK OPERATIONS =====

static void print_rec(Stack *s) {
    if (is_empty(s)) {
        return;
    }
    V v = pop(s);
    printf("%d\n", v);
    print_rec(s);
    push(s, v);
}

void print_stack(Stack *s) {
    if (s == NULL || is_empty(s)) {
        printf("empty stack.\n");
        return;
    }
    print_rec(s);
}

static int stacks_equal_helper(Stack *a, Stack *b) {
    if (is_empty(a) && is_empty(b)) {
        return 1;
    }
    if (is_empty(a) || is_empty(b)) {
        return 0;
    }

    V va = pop(a);
    V vb = pop(b);
    int same = (va == vb) && stacks_equal_helper(a, b);

    push(a, va);
    push(b, vb);
    return same;
}

int stacks_equal(Stack *a, Stack *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    if (stack_size(a) != stack_size(b)) {
        return 0;
    }
    return stacks_equal_helper(a, b);
}

void decimal_to_binary(int x, char *binary_str) {
    if (x == 0) {
        binary_str[0] = '0';
        binary_str[1] = '\0';
        return;
    }
    Stack temp = create_stack();
    int index = 0;

    while (x > 0) {
        int bit = x % 2;
        push(&temp, bit);
        x /= 2;
    }
    while (!is_empty(&temp)) {
        binary_str[index++] = '0' + pop(&temp);
    }

    binary_str[index] = '\0';
    free_stack(&temp);
}

int check_parentheses(char *expression) {
    Stack s = create_stack();
    int i = 0;
    char c;

    while ((c = expression[i++]) != '\0') {
        if (c == ASCII_PARENTHESIS_OPEN) {
            push(&s, ASCII_PARENTHESIS_OPEN);
        } else if (c == ASCII_PARENTHESIS_CLOSE) {
            if (is_empty(&s)) {
                free_stack(&s);
                return 0;
            }
            int top = pop(&s);
            if (top != ASCII_PARENTHESIS_OPEN) {
                free_stack(&s);
                return 0;
            }
        }
    }

    int valid = is_empty(&s);
    free_stack(&s);
    return valid;
}

static int is_opening(char c) {
    return c == ASCII_PARENTHESIS_OPEN || c == ASCII_BRACKET_OPEN ||
           c == ASCII_BRACE_OPEN;
}

static int is_closing(char c) {
    return c == ASCII_PARENTHESIS_CLOSE || c == ASCII_BRACKET_CLOSE ||
           c == ASCII_BRACE_CLOSE;
}

static int get_matching_open(char close) {
    if (close == ASCII_PARENTHESIS_CLOSE) return ASCII_PARENTHESIS_OPEN;
    if (close == ASCII_BRACKET_CLOSE) return ASCII_BRACKET_OPEN;
    if (close == ASCII_BRACE_CLOSE) return ASCII_BRACE_OPEN;
    return 0;
}

int check_delimiters(char *expression) {
    Stack s = create_stack();
    int i = 0;
    char c;

    while ((c = expression[i++]) != '\0') {
        if (is_opening(c)) {
            push(&s, (int)c);
        } else if (is_closing(c)) {
            if (is_empty(&s)) {
                free_stack(&s);
                return 0;
            }
            int open = pop(&s);
            if (open != get_matching_open(c)) {
                free_stack(&s);
                return 0;
            }
        }
    }

    int valid = is_empty(&s);
    free_stack(&s);
    return valid;
}

void reverse_stack(Stack *s) {
    if (s == NULL || is_empty(s)) {
        return;
    }

    Stack temp1 = create_stack();
    Stack temp2 = create_stack();

    while (!is_empty(s)) {
        push(&temp1, pop(s));
    }
    while (!is_empty(&temp1)) {
        push(&temp2, pop(&temp1));
    }
    while (!is_empty(&temp2)) {
        push(s, pop(&temp2));
    }

    free_stack(&temp1);
    free_stack(&temp2);
}

Stack clone_stack(Stack *s) {
    Stack clone = create_stack();
    if (s == NULL || is_empty(s)) {
        return clone;
    }

    Stack temp = create_stack();
    while (!is_empty(s)) {
        push(&temp, pop(s));
    }
    while (!is_empty(&temp)) {
        V value = pop(&temp);
        push(s, value);
        push(&clone, value);
    }

    free_stack(&temp);
    return clone;
}

static int precedence(char op) {
    if (op == OP_PLUS || op == OP_MINUS) return 1;
    if (op == OP_MULT || op == OP_DIV) return 2;
    if (op == OP_EXP) return 3;
    return 0;
}

static int is_operator(char c) {
    return c == OP_PLUS || c == OP_MINUS || c == OP_MULT || c == OP_DIV ||
           c == OP_EXP;
}

// oh boy! This one deserves comments
int infix_to_postfix(char *infix_expr, char *postfix_expr) {
    // First, validate that all delimiters are balanced: ( ) [ ] { }
    // If unbalanced then the expression is invalid, so return 0 immediately
    // the problem is not yours anymore
    if (!check_delimiters(infix_expr)) {
        return 0;
    }

    // Create a local stack to hold operators and opening delimiters
    Stack op_stack = create_stack();
    int i = 0, j = 0;  // i: index in input, j: index in output
    char c;            // current character being processed

    // Remove trailing newline from fgets() input
    int len = strlen(infix_expr);
    if (len > 0 && infix_expr[len - 1] == '\n') {
        infix_expr[len - 1] = '\0';
    }

    // Main loop: scan the infix expression character by character
    while ((c = infix_expr[i++]) != '\0') {
        // Skip spaces and tabs
        if (c == ' ' || c == '\t') {
            continue;
        }

        // Single-digit number only will be testes
        // copy to output with space separator
        if (isdigit(c)) {
            postfix_expr[j++] = c;
            postfix_expr[j++] = ' ';
        }
        // Opening delimiter: ( [ { -> push onto operator stack
        else if (is_opening(c)) {
            push(&op_stack, (int)c);
        }
        // Closing delimiter: ) ] } -> pop until matching opening is found
        else if (is_closing(c)) {
            int opening = get_matching_open(c); // ')' -> '('

            // Pop all operators inside the delimiters
            while (!is_empty(&op_stack) && peek(&op_stack) != opening) {
                postfix_expr[j++] = (char)pop(&op_stack);
                postfix_expr[j++] = ' ';
            }

            // Check if matching opening delimiter exists
            if (!is_empty(&op_stack) && peek(&op_stack) == opening) {
                pop(&op_stack); // discard the opening delimiter
            } else {
                free_stack(&op_stack);
                return 0; // unmatched closing delimiter
            }
        }
        // Operator: + - * / ^ -> apply shunting-yard precedence rules
        else if (is_operator(c)) {
            while (!is_empty(&op_stack)) {
                int top = peek(&op_stack);

                // Don't pop opening delimiters — they act as barriers
                if (is_opening((char)top)) break;

                // Higher precedence -> keep on stack
                if (precedence((char)top) < precedence(c)) break;

                // Same precedence, left-associative -> pop (except ^)
                if (precedence((char)top) == precedence(c) && c != OP_EXP)
                    break;

                // Otherwise, pop operator to output
                postfix_expr[j++] = (char)pop(&op_stack);
                postfix_expr[j++] = ' ';
            }
            push(&op_stack, (int)c); // push current operator
        }
        // Any other character -> invalid input
        else {
            free_stack(&op_stack);
            return 0; // invalid character in expression
        }
    }

    // After input ends: empty remaining operators from stack
    while (!is_empty(&op_stack)) {
        int top = pop(&op_stack);

        // If any opening delimiter remains -> unmatched thus -> error
        if (is_opening((char)top)) {
            free_stack(&op_stack);
            return 0;
        }

        // Append operator to output
        postfix_expr[j++] = (char)top;
        postfix_expr[j++] = ' ';
    }

    // Remove trailing space from output
    if (j > 0 && postfix_expr[j - 1] == ' ') {
        j--;
    }

    // Null-terminate the postfix expression
    postfix_expr[j] = '\0';

    // Clean up the operator stack
    free_stack(&op_stack);

    // if you reached this point, then the happy path is done
    return 1;
}
