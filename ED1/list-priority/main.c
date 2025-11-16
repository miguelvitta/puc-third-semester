#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "helpers.h"

// --- Menu Printing Prototypes ---
void print_main_menu(void);
void print_q2_menu(void);

int main() {
    int main_option = -1;

    while (main_option != 0) {
        print_main_menu();
        main_option = get_int("Choose an option: ");

        switch (main_option) {
            
            // Runs the menu for Question 2 functions
            case 1: {
                printf("\n--- Q2 Menu (Advanced Operations) ---\n");
                
                priority_queue* test_pq = create_priority_queue();
                
                // Add dummy data so print/clone can be tested
                add(test_pq, 10);
                add(test_pq, 5);
                add(test_pq, 20);

                int sub_option = -1;
                
                while (sub_option != 0) {
                    print_q2_menu();
                    sub_option = get_int("Choose Q2 option: ");

                    switch (sub_option) {
                        case 1:
                            print_queue(test_pq);
                            break;
                        case 2:
                            printf("Not implemented yet.\n");
                            break;
                        case 3:
                        {
                            priority_queue* cloned = clone_queue(test_pq);
                            if (cloned != NULL) {
                                printf("Queue cloned (but clone logic is TODO).\n");
                                free_priority_queue(cloned);
                            }
                            break;
                        }
                        case 4:
                            printf("Not implemented in this menu.\n");
                            break;
                        case 5:
                            printf("Not implemented in this menu.\n");
                            break;
                        case 0:
                            printf("Returning to main menu...\n");
                            break;
                        default:
                            printf("Invalid option.\n");
                    }
                }
                free_priority_queue(test_pq);
                break;
            }

            // Placeholder for Question 3
            case 2: {
                printf("\n// TODO: Implement Question 3 (Generic PQ w/ Comparator)\n");
                break;
            }

            // Placeholder for Question 4
            case 3: {
                printf("\n// TODO: Implement Question 4 (Bank Simulation)\n");
                break;
            }

            // Exits the program
            case 0:
                printf("Exiting...\n");
                break;

            // Handles invalid input
            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

// --- Menu Printing Functions ---

void print_main_menu(void) {
    printf("\n===== MAIN MENU (Priority Queue) =====\n");
    printf("1. Run Question 2 Menu (Advanced Operations)\n");
    printf("2. (TODO) Run Question 3 (Generic PQ)\n");
    printf("3. (TODO) Run Question 4 (Simulation)\n");
    printf("0. Exit\n");
}

void print_q2_menu(void) {
    printf("\n--- Q2 Operations ---\n");
    printf("1. Print Queue (in order)\n");
    printf("2. Queues Equal\n");
    printf("3. Clone Queue\n");
    printf("4. Sort Vector (Ascending)\n");
    printf("5. Sort Vector (Descending)\n");
    printf("0. Back to Main Menu\n");
}