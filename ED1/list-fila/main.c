#include "flow.h"
#include "list.h"

void print_main_menu();
void print_basic_menu();
void print_advanced_menu();

int main() {
    Queue *q = malloc(sizeof(Queue));
    if (q == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    *q = create_queue();

    int main_option = -1;

    while (main_option != 0) {
        print_main_menu();
        main_option = get_int("Choose an option: ");

        switch (main_option) {
            case 1: {
                int sub_option = -1;
                while (sub_option != 0) {
                    print_basic_menu();
                    sub_option = get_int("Choose an option: ");
                    if (sub_option == 0) {
                        break;
                    }

                    V value;
                    switch (sub_option) {
                        case 1:
                            value = get_int("Enter value to add: ");
                            add(q, value);
                            break;
                        case 2:
                            value = remove_queue(q);
                            printf("Removed value: %d\n", value);
                            break;
                        case 3:
                            value = get_front(q);
                            printf("Front value: %d\n", value);
                            break;
                        case 4:
                            printf("Queue size: %d\n", queue_size(q));
                            break;
                        case 5:
                            printf("Is empty: %d\n", is_queue_empty(q));
                            break;
                        case 6:
                            clear_queue(q);
                            printf("Queue cleared.\n");
                            break;
                        case 7:
                            print_queue(q);
                            break;
                        default:
                            printf("Invalid option.\n");
                    }
                }
                break;
            }

            case 2: {
                int sub_option = -1;
                while (sub_option != 0) {
                    print_advanced_menu();
                    sub_option = get_int("Choose an option: ");
                    if (sub_option == 0) {
                        break;
                    }

                    switch (sub_option) {
                        case 1: {
                            Queue clone = clone_queue(q);
                            printf("Cloned queue:\n");
                            print_queue(&clone);
                            free_queue(&clone);
                            break;
                        }
                        case 2:
                            reverse_queue(q);
                            printf("Queue reversed.\n");
                            break;
                        case 3: {
                            Queue b = create_queue();
                            int n = get_int(
                                "How many elements for the second queue? ");
                            for (int i = 0; i < n; i++) {
                                V val = get_int("Enter value: ");
                                add(&b, val);
                            }
                            int equal = queues_equal(q, &b);
                            printf(equal ? "Queues equal\n"
                                         : "Queues not equal\n");
                            free_queue(&b);
                            break;
                        }
                        default:
                            printf("Invalid option.\n");
                    }
                }
                break;
            }

            case 3: {
                int sub_option = -1;
                while (sub_option != 0) {
                    printf("\n--- FLOW CONTROL ---\n");
                    printf("1 - Multiplexing (3 flows -> 1 channel)\n");
                    printf("2 - Demultiplexing (1 channel -> 3 flows)\n");
                    printf("0 - Back\n");
                    sub_option = get_int("Choose an option: ");
                    if (sub_option == 0) {
                        break;
                    }

                    switch (sub_option) {
                        case 1:
                            multiplex_flows();
                            break;
                        case 2:
                            demultiplex_flow();
                            break;
                        default:
                            printf("Invalid option.\n");
                    }
                }
                break;
            }

            case 0:
                free_queue(q);
                free(q);
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
    printf("1 - Basic queue operations\n");
    printf("2 - Advanced operations\n");
    printf("3 - Flow control (multiplex / demultiplex)\n");
    printf("0 - Exit\n");
}

void print_basic_menu() {
    printf("\n--- BASIC QUEUE OPERATIONS ---\n");
    printf("1 - Add element (enqueue)\n");
    printf("2 - Remove element (dequeue)\n");
    printf("3 - Get front element\n");
    printf("4 - Get queue size\n");
    printf("5 - Check if empty\n");
    printf("6 - Clear queue\n");
    printf("7 - Print queue (front to back)\n");
    printf("0 - Back\n");
}

void print_advanced_menu() {
    printf("\n--- ADVANCED QUEUE OPERATIONS ---\n");
    printf("1 - Clone queue\n");
    printf("2 - Reverse queue\n");
    printf("3 - Compare queues (equals)\n");
    printf("0 - Back\n");
}