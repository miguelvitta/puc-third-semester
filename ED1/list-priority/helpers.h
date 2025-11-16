#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_BUFFER 128

/**
 * @brief Prompts the user and safely reads an integer from stdin.
 *
 * @param prompt The message to display to the user.
 * @return The integer value entered by the user.
 */
int get_int(const char *prompt);

/**
 * @brief Prompts the user and safely reads a string from stdin.
 *
 * @param prompt The message to display to the user.
 * @param buffer The buffer to store the string in.
 * @param length The size of the buffer.
 */
void get_string(const char *prompt, char *buffer, int length);

#endif