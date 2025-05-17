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
 * @param tail           The tail of tokens
 */
static void
alpha_token(syntaxc_t *syntax, token_t **tail)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    size_t i = syntax->_current_index;
    size_t length = 0;
    token_t *token = NULL;

    while (i < syntax->_buffer_file_sz &&
        (isalpha(syntax->_buffer_file[i]) || syntax->_buffer_file[i] == '_')) {
        i++;
    }
    length = i - syntax->_current_index;
    token = create_token(start, length, syntax->_current_line,
        syntax->_current_col, TOKEN_SYMBOL);
    (*tail)->_next_token = token;
    *tail = token;
    syntax->_current_index = i;
}

/**
 * @brief String token.
 *
 * @param syntax         The structure syntax
 * @param tail           The tail of tokens
 */
static
void string_token(syntaxc_t *syntax, token_t **tail)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    size_t i = syntax->_current_index + 1;
    token_t *token = NULL;

    while (i < syntax->_buffer_file_sz && syntax->_buffer_file[i] != '"') {
        i++;
    }
    if (i < syntax->_buffer_file_sz && syntax->_buffer_file[i] == '"') {
        i++;
    }
    size_t length = i - syntax->_current_index;
    token = create_token(start, length, syntax->_current_line,
        syntax->_current_col, TOKEN_STRING);
    (*tail)->_next_token = token;
    *tail = token;
    syntax->_current_index = i;
}

/**
 * @brief Digit token.
 *
 * @param syntax         The structure syntax
 * @param tail           The tail of tokens
 */
static void
digit_token(syntaxc_t *syntax, token_t **tail)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    size_t i = syntax->_current_index;
    size_t length = 0;
    token_t *token = NULL;

    while (i < syntax->_buffer_file_sz &&
        (isdigit(syntax->_buffer_file[i]) || syntax->_buffer_file[i] == '.')) {
        i++;
    }
    length = i - syntax->_current_index;
    token = create_token(start, length, syntax->_current_line,
        syntax->_current_col, TOKEN_NUMBER);
    (*tail)->_next_token = token;
    *tail = token;
    syntax->_current_index = i;
}

/**
 * @brief Comment token.
 *
 * @param syntax         The structure syntax
 * @param tail           The tail of tokens
 * @param type           Is a big or small comment
 */
static void
comment_token(syntaxc_t *syntax, token_t **tail, token_type_t type)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    size_t i = syntax->_current_index;
    int length = 0;
    token_t *token = NULL;

    if (type != TOKEN_COMMENT_BIG && type != TOKEN_COMMENT_SMALL) {
        syntax->_current_index = i + 1;
        return;
    }
    if (type == TOKEN_COMMENT_BIG) {
        while (i < syntax->_buffer_file_sz && !is_end_comment_big(&syntax->_buffer_file[i]))
            i++;
        i += 2;
    }
    if (type == TOKEN_COMMENT_SMALL) {
        while (i < syntax->_buffer_file_sz && !is_end_comment_small(&syntax->_buffer_file[i]))
            i++;
        i++;
    }
    length = i - syntax->_current_index;
    if (length < 0)
        return;
    token = create_token(start, length, syntax->_current_line,
        syntax->_current_col, type);
    (*tail)->_next_token = token;
    *tail = token;
    syntax->_current_index += length;
}

/**
 * @brief Preprocessor token.
 *
 * @param syntax         The structure syntax
 * @param tail           The tail of tokens
 */
static void
preprocessor_token(syntaxc_t *syntax, token_t **tail)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    size_t i = syntax->_current_index;
    size_t length = 0;
    token_t *token = NULL;

    while (i < syntax->_buffer_file_sz && syntax->_buffer_file[i] != ' '
        && syntax->_buffer_file[i] != '\t') {
        i++;
    }
    length = i - syntax->_current_index;
    token = create_token(start, length, syntax->_current_line,
        syntax->_current_col, TOKEN_PREPROCESSOR);
    (*tail)->_next_token = token;
    *tail = token;
    syntax->_current_index = i;
}

/**
 * @brief Char token.
 *
 * @param syntax         The structure syntax
 * @param tail           The tail of tokens
 */
static void
char_token(syntaxc_t *syntax, token_t **tail)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    size_t i = syntax->_current_index + 1;
    token_t *token = NULL;

    while (i < syntax->_buffer_file_sz && syntax->_buffer_file[i] != '\'') {
        i++;
    }
    if (i < syntax->_buffer_file_sz && syntax->_buffer_file[i] == '\'') {
        i++;
    }
    size_t length = i - syntax->_current_index;
    token = create_token(start, length, syntax->_current_line,
        syntax->_current_col, TOKEN_CHAR);
    (*tail)->_next_token = token;
    *tail = token;
    syntax->_current_index = i;
}

/**
 * @brief Misc tokens.
 *
 * @param syntax        The structure syntax
 * @param tail          The tail of tokens
 * @param type          The type of token
 */
static void
misc_token(syntaxc_t *syntax, token_t **tail, token_type_t type, size_t len)
{
    const char *start = &syntax->_buffer_file[syntax->_current_index];
    token_t *token = create_token(start, len, syntax->_current_line,
        syntax->_current_col, type);

    (*tail)->_next_token = token;
    *tail = token;
    syntax->_current_index += len;
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
        if (syntax->_buffer_file[syntax->_current_index] == ' ') {
            misc_token(syntax, &tail, TOKEN_SPACE, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '\n') {
            misc_token(syntax, &tail, TOKEN_NEWLINE, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '\t') {
            misc_token(syntax, &tail, TOKEN_TAB, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '(') {
            misc_token(syntax, &tail, TOKEN_PARENT_OPEN, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == ')') {
            misc_token(syntax, &tail, TOKEN_PARENT_CLOSE, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '{') {
            misc_token(syntax, &tail, TOKEN_BRACKET_OPEN, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '}') {
            misc_token(syntax, &tail, TOKEN_BRACKET_CLOSE, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '>') {
            misc_token(syntax, &tail, TOKEN_SUPERIOR, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '<') {
            misc_token(syntax, &tail, TOKEN_INFERIOR, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '=') {
            misc_token(syntax, &tail, TOKEN_EQUAL, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == ';') {
            misc_token(syntax, &tail, TOKEN_SEMICOLON, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '[') {
            misc_token(syntax, &tail, TOKEN_SQUARE_BRACKET_OPEN, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == ']') {
            misc_token(syntax, &tail, TOKEN_SQUARE_BRACKET_CLOSE, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == ',') {
            misc_token(syntax, &tail, TOKEN_COMMA, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '*') {
            misc_token(syntax, &tail, TOKEN_STAR, 1);
            continue;
        }
        if (is_start_comment_big(&syntax->_buffer_file[syntax->_current_index])) {
            comment_token(syntax, &tail, TOKEN_COMMENT_BIG);
            continue;
        }
        if (is_start_comment_small(&syntax->_buffer_file[syntax->_current_index])) {
            comment_token(syntax, &tail, TOKEN_COMMENT_SMALL);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '/') {
            misc_token(syntax, &tail, TOKEN_DIV, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '+') {
            misc_token(syntax, &tail, TOKEN_ADD, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '-') {
            misc_token(syntax, &tail, TOKEN_SUB, 1);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '&' &&
            syntax->_buffer_file[syntax->_current_index + 1] == '&') {
            misc_token(syntax, &tail, TOKEN_AND, 2);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '|' &&
            syntax->_buffer_file[syntax->_current_index + 1] == '|') {
            misc_token(syntax, &tail, TOKEN_OR, 2);
            continue;
        }
        if (isalpha(syntax->_buffer_file[syntax->_current_index])) {
            alpha_token(syntax, &tail);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '"') {
            string_token(syntax, &tail);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '\'') {
            char_token(syntax, &tail);
            continue;
        }
        if (syntax->_buffer_file[syntax->_current_index] == '#') {
            preprocessor_token(syntax, &tail);
            continue;
        }
        if (isdigit(syntax->_buffer_file[syntax->_current_index])) {
            digit_token(syntax, &tail);
            continue;
        }
        syntax->_current_index++;
    }
    return head;
}
