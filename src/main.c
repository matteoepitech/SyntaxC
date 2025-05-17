/*
** EPITECH PROJECT, 2025
** src/main
** File description:
** Main file
*/

#include "syntaxc.h"
#include "ansi_colors.h"

/**
 * @brief Main function.
 *
 * @param argc          ARGC
 * @param argv[]        ARGV
 *
 * @return Return status.
 */
int main(int argc, char *argv[])
{
    if (argc <= 1) {
        fprintf(stderr, "Err: You didn't put any file!\n");
        return KO_OUTPUT;
    }
    printf("Syntax for: " ANSI_COLOR_GREEN "%s\n" ANSI_COLOR_RESET, argv[1]);
    return OK_OUTPUT;
}
