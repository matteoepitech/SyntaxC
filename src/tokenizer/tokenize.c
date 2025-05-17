/*
** EPITECH PROJECT, 2025
** src/tokenizer/tokenize
** File description:
** Tokenize the buffer and return a token list
*/

#include "syntaxc.h"

/**
 * @brief Alpha token.
 *
 * @param syntax         The structure syntax
 */
static void alpha_token(syntaxc_t *syntax, token_t **tail)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    token_t *token = NULL;
    size_t length = 0;

    while (length < syntax->_buffer_file_sz && isalpha(syntax->_buffer_file[syntax->_current_index + length]))
        length++;
    token = create_token(start, length, 0, 0, TOKEN_SYMBOL);
    token->_next_token = *tail;
    *tail = token;
    syntax->_current_index += length;
}

/**
 * @brief Tokenize the buffer.
 *
 * @param syntaxc       The structure syntax
 *
 * @return The head of tokens.
 */
token_t *
tokenize_buffer(syntaxc_t *syntax)
{
    token_t *head = create_token(syntax->_buffer_file, 0, 0, 0, TOKEN_START);
    token_t *tail = head;

    while (syntax->_current_index < syntax->_buffer_file_sz) {
        if (syntax->_buffer_file[syntax->_current_index] == ' ' ||
            syntax->_buffer_file[syntax->_current_index] == '\t' ||
            syntax->_buffer_file[syntax->_current_index] == '\n') {
            syntax->_current_index++;
            continue;
        }
        if (isalpha(syntax->_buffer_file[syntax->_current_index])) {
            alpha_token(syntax, &tail);
            continue;
        }
        // Unknow ?
        syntax->_current_index++;
    }
    return head;
}
