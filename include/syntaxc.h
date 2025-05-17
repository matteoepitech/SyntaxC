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

/*
 * Folder : src/printer/
 */
int print_tokens(token_t *head);

#endif /* ifndef SYNTAXC_H_ */
