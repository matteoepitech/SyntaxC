/*
** EPITECH PROJECT, 2025
** include/syntaxc
** File description:
** SyntaxC Header file
*/

#ifndef SYNTAXC_H_

    #include <unistd.h>
    #include <stdio.h>
    #include <stddef.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    
    #define SYNTAXC_H_

    #define OK_OUTPUT 0
    #define KO_OUTPUT 1
    #define UNUSED __attribute__((unused))

/**
 * @brief Syntaxc structure
 */
typedef struct {
    char *_buffer_file;
    size_t _buffer_file_sz;
    size_t _current_index;
    size_t _current_line;
    size_t _current_col;
} syntaxc_t;

typedef enum {
    TOKEN_START,
    TOKEN_IDENTIFIER,
    TOKEN_SYMBOL,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_SPACE,
    TOKEN_TAB,
    TOKEN_NEWLINE,
    TOKEN_COMMENT_BIG,
    TOKEN_COMMENT_SMALL,
    TOKEN_PREPROCESSOR,
    TOKEN_PARENT_OPEN,
    TOKEN_PARENT_CLOSE,
    TOKEN_BRACKET_OPEN,
    TOKEN_BRACKET_CLOSE,
    TOKEN_SUPERIOR,
    TOKEN_INFERIOR,
    TOKEN_EQUAL,
    TOKEN_SEMICOLON,
    TOKEN_SQUARE_BRACKET_OPEN,
    TOKEN_SQUARE_BRACKET_CLOSE,
    TOKEN_COMMA,
    TOKEN_STAR,
    TOKEN_ADD,
    TOKEN_DIV,
    TOKEN_SUB,
    TOKEN_CHAR,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_FUNC,
    TOKEN_END
} token_type_t;

/**
 * @brief Token structure
 */
typedef struct token_s {
    const char *_start;
    size_t _length;
    size_t _line;
    size_t _col;
    token_type_t _type;
    struct token_s *_next_token;
} token_t;

/*
 * Folder : src/file/
 */
syntaxc_t *open_file(char *file);

/*
 * Folder : src/tokenizer/
 */
token_t *tokenize_buffer(syntaxc_t *syntax);
token_t *create_token(const char *start, size_t length, size_t line, size_t col, token_type_t type);
token_t *transform_identifier(token_t *head);
token_t *transform_function(token_t *head);

void free_tokens(token_t *head);

int is_start_comment_big(const char *string);
int is_start_comment_small(const char *string);
int is_end_comment_big(const char *string);
int is_end_comment_small(const char *string);

/*
 * Folder : src/printer/
 */
int print_tokens(token_t *head);
int print_final_file(token_t *head);

#endif /* ifndef SYNTAXC_H_ */
