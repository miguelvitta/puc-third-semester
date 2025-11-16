#include "helpers.h"

int get_int(const char *prompt) {
    int value = 0;
    char buffer[SIZE_BUFFER];
    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            char *endptr = NULL;
            value = strtol(buffer, &endptr, 10);
            
            // Trim trailing whitespace
            while (*endptr == ' ' || *endptr == '\t') {
                endptr++;
            }
            
            if (*endptr == '\0' || *endptr == '\n') {
                return value; // Valid integer
            }
            printf("Invalid input. Please enter an integer.\n");
        } else {
            // Handle EOF or read error
            fprintf(stderr, "Error reading input.\n");
            exit(1);
        }
    }
}

void get_string(const char *prompt, char *buffer, int length) {
    printf("%s", prompt);
    if (fgets(buffer, length, stdin) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;
    } else {
        // Handle error
        buffer[0] = '\0';
    }
}