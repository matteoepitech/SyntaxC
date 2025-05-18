/*
** DEL PROJECT, 2025
** src/tokenizer/tokenize_post
** File description:
** After tokenization we do another pass
*/

#include "syntaxc.h"

/**
 * @brief Is the string a identifier.
 *
 * @param string         The string
 * @param length         The length of the string
 *
 * @return Return 1 or 0.
 */
static
char is_identifier(const char *string, size_t length)
{
    static const char *identifiers[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "int", "long", "register", "return", "short", "signed", "sizeof",
        "static", "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while", "_Bool", "_Complex", "_Imaginary", "inline",
        "restrict", "_Alignas", "_Alignof", "_Atomic", "_Generic", "_Noreturn",
        "_Static_assert", "_Thread_local", "define", "include", "ifdef",
        "ifndef", "endif", "elif", "else", "if", "error", "pragma", "undef",
        "warning", NULL
    };

    for (int i = 0; identifiers[i] != NULL; i++) {
        if (strncmp(string, identifiers[i], length) == 0 &&
            strlen(identifiers[i]) == length) {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Get every token and verify if the symbol is a identifier or not.
 *
 * @param head          The HEAD
 *
 * @return The final HEAD.
 */
token_t *
transform_identifier(token_t *head)
{
    token_t *tmp = head;

    while (tmp != NULL) {
        if (tmp->_type != TOKEN_SYMBOL) {
            tmp = tmp->_next_token;
            continue;
        }
        if (is_identifier(tmp->_start, tmp->_length))
            tmp->_type = TOKEN_IDENTIFIER;
        tmp = tmp->_next_token;
    }
    return transform_function(head);
}


/**
 * @brief Get every token and verify if the symbol is a function or not.
 *
 * @param head          The HEAD
 *
 * @return The final HEAD.
 */
token_t *
transform_function(token_t *head)
{
    token_t *tmp = head;

    while (tmp != NULL) {
        if (tmp->_type != TOKEN_SYMBOL) {
            tmp = tmp->_next_token;
            continue;
        }
        if (tmp->_next_token != NULL &&
            tmp->_next_token->_type == TOKEN_PARENT_OPEN)
            tmp->_type = TOKEN_FUNC;
        tmp = tmp->_next_token;
    }
    return head;
}
