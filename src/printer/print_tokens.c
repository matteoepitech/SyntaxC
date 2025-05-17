/*
** EPITECH PROJECT, 2025
** src/printer/print_tokens
** File description:
** Print of tokens
*/

#include "ansi_colors.h"
#include "syntaxc.h"

/**
 * @brief Print the token type name.
 *
 * @param type           The token type
 */
static void
print_token_name(token_type_t type)
{
    static const char *type_names[] = {"START", "IDENTIFIER", "SYMBOL",
        "NUMBER", "STRING", "SPACE", "TAB", "NEWLINE", "COMMENT_BIG",
        "COMMENT_SMALL", "PREPROCESSOR", "PARENT_OPEN", "PARENT_CLOSE",
        "BRACKET_OPEN", "BRACKET_CLOSE", "SUPERIOR", "INFERIOR", "EQUAL",
        "SEMICOLON", "SQUARE_BR_OPEN", "SQUARE_BR_CLOSE", "COMMA",
        "STAR", "ADD", "DIV", "SUB", "CHAR", "AND", "OR", "END"};

    if (type == 0 || type >= 6)
        printf(ANSI_COLOR_BLUE "%s: ", type_names[type]);
    else
        printf(ANSI_COLOR_YELLOW "%s: ", type_names[type]);
    fflush(stdout);
    return;
}

/**
 * @brief Print tokens.
 *
 * @param head          The head
 *
 * @return Everything worked?
 */
int
print_tokens(token_t *head)
{
    if (head->_type != TOKEN_START) {
        fprintf(stderr, "Err: Tokenizer failed (no start)\n");
        return KO_OUTPUT;
    }
    for (token_t *tmp = head; tmp != NULL; tmp = tmp->_next_token) {
        print_token_name(tmp->_type);
        if (tmp->_type == TOKEN_START || tmp->_type == TOKEN_END ||
            tmp->_type == TOKEN_NEWLINE) {
            printf("\n");
            fflush(stdout);
            continue;
        }
        for (size_t i = 0; i < tmp->_length; i++)
            printf("%c", tmp->_start[i]);
        printf("\n");
        fflush(stdout);
    }
    return OK_OUTPUT;
}

/**
 * @brief Print the final file using the colors.
 *
 * @param head          The head
 *
 * @return Everything worked ?
 */
int
print_final_file(token_t *head)
{
    printf(ANSI_COLOR_RESET);
    for (token_t *tmp = head; tmp != NULL; tmp = tmp->_next_token) {
        for (size_t i = 0; i < tmp->_length; i++)
            printf("%c", tmp->_start[i]);
    }
    return OK_OUTPUT;
}
