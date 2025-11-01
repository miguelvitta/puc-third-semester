#include "list.h"

void print_main_menu();
void print_basic_menu();
void print_advanced_menu();

int main() {
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    *s = create_stack();

    int main_option = -1;

    while (main_option != 0) {
        print_main_menu();
        main_option = get_int("Choose an option: ");

        switch (main_option) {
            // BASIC STACK OPERATIONS
            case 1: {
                int sub_option = -1;
                while (sub_option != 0) {
                    print_basic_menu();
                    sub_option = get_int("Choose an option: ");
                    if (sub_option == 0)
                        break;

                    V value;
                    switch (sub_option) {
                        case 1:
                            value = get_int("Enter value to push: ");
                            push(s, value);
                            break;
                        case 2:
                            value = pop(s);
                            printf("Popped value: %d\n", value);
                            break;
                        case 3:
                            value = peek(s);
                            printf("Top value: %d\n", value);
                            break;
                        case 4:
                            printf("Stack size: %d\n", stack_size(s));
                            break;
                        case 5:
                            printf("Is empty: %d\n", is_empty(s));
                            break;
                        case 6:
                            clear_stack(s);
                            printf("Stack cleared.\n");
                            break;
                        case 7:
                            print_stack(s);
                            break;
                        default:
                            printf("Invalid option.\n");
                    }
                }
                break;
            }

            // ADVANCED STACK OPERATIONS
            case 2: {
                int sub_option = -1;
                while (sub_option != 0) {
                    print_advanced_menu();
                    sub_option = get_int("Choose an option: ");
                    if (sub_option == 0)
                        break;

                    switch (sub_option) {
                        case 1: {
                            Stack clone = clone_stack(s);
                            printf("Cloned stack:\n");
                            print_stack(&clone);
                            free_stack(&clone);
                            break;
                        }
                        case 2:
                            reverse_stack(s);
                            printf("Stack reversed.\n");
                            break;
                        case 3: {
                            int x = get_int("Enter decimal number: ");
                            char binary[SIZE_BINARY];
                            decimal_to_binary(x, binary);
                            printf("Binary: %s\n", binary);
                            break;
                        }
                        case 4: {
                            char expr[SIZE_EXPRESSION];
                            printf("Enter expression: ");
                            fgets(expr, sizeof(expr), stdin);
                            int valid = check_parentheses(expr);
                            printf("Parentheses valid: %d\n", valid);
                            break;
                        }
                        case 5: {
                            char expr[SIZE_EXPRESSION];
                            printf("Enter expression: ");
                            fgets(expr, sizeof(expr), stdin);
                            int valid = check_delimiters(expr);
                            printf("Delimiters valid: %d\n", valid);
                            break;
                        }
                        case 6: {
                            char infix[SIZE_EXPRESSION], postfix[SIZE_EXPRESSION];
                            printf("Enter infix expression: ");
                            fgets(infix, sizeof(infix), stdin);
                            if (infix_to_postfix(infix, postfix))
                                printf("Postfix: %s\n", postfix);
                            else
                                printf("Invalid infix expression.\n");
                            break;
                        }
                        case 7: {
                            Stack b = create_stack();
                            int n = get_int("How many elements for the second stack? ");
                            for (int i = 0; i < n; i++) {
                                V val = get_int("Enter value: ");
                                push(&b, val);
                            }
                            int eq = stacks_equal(s, &b);
                            printf("Stacks equal: %d\n", eq);
                            free_stack(&b);
                            break;
                        }
                        default:
                            printf("Invalid option.\n");
                    }
                }
                break;
            }

            case 0:
                free_stack(s);
                free(s);
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option.\n");
        }
    }

    return 0;
}

void print_main_menu() {
    printf("\n=== MAIN MENU ===\n");
    printf("1 - Basic stack operations\n");
    printf("2 - Advanced operations\n");
    printf("0 - Exit\n");
}

void print_basic_menu() {
    printf("\n--- BASIC STACK OPERATIONS ---\n");
    printf("1 - Push element\n");
    printf("2 - Pop element\n");
    printf("3 - Get top element\n");
    printf("4 - Get stack size\n");
    printf("5 - Check if empty\n");
    printf("6 - Clear stack\n");
    printf("7 - Print stack (top to bottom)\n");
    printf("0 - Back\n");
}

void print_advanced_menu() {
    printf("\n--- ADVANCED STACK OPERATIONS ---\n");
    printf("1 - Clone stack\n");
    printf("2 - Reverse stack\n");
    printf("3 - Convert decimal to binary\n");
    printf("4 - Check parentheses\n");
    printf("5 - Check delimiters\n");
    printf("6 - Convert infix to postfix\n");
    printf("7 - Compare stacks (equals)\n");
    printf("0 - Back\n");
}
