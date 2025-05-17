/*
** EPITECH PROJECT, 2025
** src/tokenizer/tokens_utils
** File description:
** This file contains some functions inline to check some things in tokens
*/

#include "syntaxc.h"

/**
 * @brief Is the start of a comment big?
 *
 * @param string     The start of the string
 *
 * @return 
 */
int
is_start_comment_big(const char *string)
{
    return string[0] == '/' && string[1] == '*';
}

/**
 * @brief Is the end of a comment big?
 *
 * @param string     The start of the string
 *
 * @return 
 */
int
is_end_comment_big(const char *string)
{
    return string[0] == '*' && string[1] == '/';
}

/**
 * @brief Is the start of a comment small?
 *
 * @param string     The start of the string
 *
 * @return 
 */
int
is_start_comment_small(const char *string)
{
    return string[0] == '/' && string[1] == '/';
}

/**
 * @brief Is the end of a comment small?
 *
 * @param string     The start of the string
 *
 * @return 
 */
int
is_end_comment_small(const char *string)
{
    return string[0] == '\n';
}
