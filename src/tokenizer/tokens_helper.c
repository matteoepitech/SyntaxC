/*
** EPITECH PROJECT, 2025
** src/tokenizer/tokens_helper
** File description:
** Tokens helper
*/

#include "syntaxc.h"

/**
 * @brief Create a token.
 *
 * @param start         The start of the token
 * @param length        The length of the token
 * @param line          The line
 * @param col           The col
 *
 * @return The token.
 */
token_t *
create_token(const char *start, size_t length, size_t line, size_t col, token_type_t type)
{
    token_t *token = NULL;

    if (start == NULL)
        return NULL;
    token = malloc(sizeof(token_t));
    token->_start = start;
    token->_col = col;
    token->_line = line;
    token->_length = length;
    token->_type = type;
    token->_next_token = NULL;
    return token;
}
