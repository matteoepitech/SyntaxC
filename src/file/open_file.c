/*
** EPITECH PROJECT, 2025
** src/file/open_file
** File description:
** Open the file and fill the structure
*/

#include "syntaxc.h"

/**
 * @brief Open the file and return a structure containing the syntaxc.
 *
 * @param file          The file
 *
 * @return The structure syntaxc.
 */
syntaxc_t *
open_file(char *file)
{
    FILE *file_stream = fopen(file, "r");
    syntaxc_t *syntax = malloc(sizeof(syntaxc_t));

    if (file_stream == NULL) {
        free(syntax);
        fprintf(stderr, "Err: Cannot open the file %s.\n", file);
        return NULL;
    }
    fseek(file_stream, 0L, SEEK_END);
    syntax->_buffer_file_sz = ftell(file_stream);
    syntax->_buffer_file = malloc(sizeof(char) * syntax->_buffer_file_sz + 1);
    syntax->_current_col = 0;
    syntax->_current_line = 0;
    syntax->_current_index = 0;
    rewind(file_stream);
    fread(syntax->_buffer_file, syntax->_buffer_file_sz, 1, file_stream);
    syntax->_buffer_file[syntax->_buffer_file_sz] = '\0';
    fclose(file_stream);
    return syntax;
}
