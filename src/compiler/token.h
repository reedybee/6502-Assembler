#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKENS 4

typedef enum {
    TOKEN_LABEL,
    TOKEN_OPCODE,
    TOKEN_OPERAND,
    TOKEN_COMMENT,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

int tokenize_line(const char *line, Token tokens[]);

#endif // TOKEN_H