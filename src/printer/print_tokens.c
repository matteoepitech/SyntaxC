/*
** EPITECH PROJECT, 2025
** src/printer/print_tokens
** File description:
** Print of tokens
*/

#include "syntaxc.h"

/**
 * @brief Print tokens.
 *
 * @param head          The head
 *
 * @return Everything worked?
 */
int print_tokens(token_t *head)
{
    if (head->_type != TOKEN_START) {
        fprintf(stderr, "Err: Tokenizer failed (no start)\n");
        return KO_OUTPUT;
    }
    return OK_OUTPUT;
}
