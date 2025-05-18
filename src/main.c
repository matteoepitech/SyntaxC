/*
** DEL PROJECT, 2025
** src/main
** File description:
** Main file
*/

#include "syntaxc.h"

/**
 * @brief Main function.
 *
 * @param argc          ARGC
 * @param argv[]        ARGV
 *
 * @return Return status.
 */
int
main(int argc, char *argv[])
{
    syntaxc_t *syntax = NULL;
    token_t *head = NULL;

    if (argc <= 1) {
        fprintf(stderr, "Err: You didn't put any file!\n");
        return KO_OUTPUT;
    }
    syntax = open_file(argv[1]);
    if (syntax == NULL)
        return KO_OUTPUT;
    head = tokenize_buffer(syntax);
    print_final_file(head);
    free_tokens(head);
    free(syntax->_buffer_file);
    free(syntax);
    return OK_OUTPUT;
}
