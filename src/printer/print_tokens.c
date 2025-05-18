/*
** DEL PROJECT, 2025
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
        "STAR", "ADD", "DIV", "SUB", "CHAR", "AND", "OR", "FUNC", "END"
    };

    printf("%s: ", type_names[type]);
    fflush(stdout);
    return;
}

/**
 * @brief Print the color depending of the type.
 *
 * @param type
 */
static void
print_color(token_type_t type)
{
    static const char *type_colors[] = {
        COLOR_RESET, COLOR_IDENTIFIER, COLOR_SYMBOL, COLOR_NUMBER,
        COLOR_STRING, COLOR_SPACE, COLOR_TAB, COLOR_NEWLINE, COLOR_COMMENT_BIG,
        COLOR_COMMENT_SMALL, COLOR_PREPROCESSOR, COLOR_PARENT_OPEN, COLOR_PARENT_CLOSE,
        COLOR_BRACKET_OPEN, COLOR_BRACKET_CLOSE, COLOR_SUPERIOR, COLOR_INFERIOR, COLOR_EQUAL,
        COLOR_SEMICOLON, COLOR_SQUARE_BR_OPEN, COLOR_SQUARE_BR_CLOSE, COLOR_COMMA,
        COLOR_STAR, COLOR_ADD, COLOR_DIV, COLOR_SUB, COLOR_CHAR,
        COLOR_AND, COLOR_OR, COLOR_FUNC, COLOR_END
    };
    printf("%s", type_colors[type]);
    fflush(stdout);
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
    printf(COLOR_RESET);
    for (token_t *tmp = head; tmp != NULL; tmp = tmp->_next_token) {
        print_color(tmp->_type);
        for (size_t i = 0; i < tmp->_length; i++)
            printf("%c", tmp->_start[i]);
    }
    return OK_OUTPUT;
}
