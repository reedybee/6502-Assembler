#include "compiler/token.h"

int tokenize_line(const char *line, Token tokens[]) {
    int tokenCount = 0;
    const char *start = line;

    // Skip leading whitespace
    while (*start && isspace((unsigned char)*start)) start++;

    // Process label (if it ends with ':')
    if (*start && strchr(start, ':')) {
        const char *end = strchr(start, ':');
        size_t len = end - start;
        if (len > 0 && tokenCount < MAX_TOKENS) {
            tokens[tokenCount].type = TOKEN_LABEL;
            strncpy(tokens[tokenCount].value, start, len);
            tokens[tokenCount].value[len] = '\0';
            tokenCount++;
        }
        start = end + 1;  // Skip past ':'
        while (*start && isspace((unsigned char)*start)) start++;
    }

    // Process opcode (next non-whitespace word)
    if (*start && !isspace(*start) && tokenCount < MAX_TOKENS) {
        const char *end = start;
        while (*end && !isspace((unsigned char)*end)) end++;
        size_t len = end - start;
        tokens[tokenCount].type = TOKEN_OPCODE;
        strncpy(tokens[tokenCount].value, start, len);
        tokens[tokenCount].value[len] = '\0';
        tokenCount++;
        start = end;
        while (*start && isspace((unsigned char)*start)) start++;
    }

    // Process operand (if present)
    if (*start && *start != ';' && tokenCount < MAX_TOKENS) {
        const char *end = start;
        while (*end && *end != ';' && !isspace((unsigned char)*end)) end++;
        size_t len = end - start;
        tokens[tokenCount].type = TOKEN_OPERAND;
        strncpy(tokens[tokenCount].value, start, len);
        tokens[tokenCount].value[len] = '\0';
        tokenCount++;
        start = end;
        while (*start && isspace((unsigned char)*start)) start++;
    }

    // Process comment (if present)
    if (*start && *start == ';' && tokenCount < MAX_TOKENS) {
        tokens[tokenCount].type = TOKEN_COMMENT;
        strncpy(tokens[tokenCount].value, start + 1, 63);  // Skip ';'
        tokens[tokenCount].value[63] = '\0';  // Ensure null-terminated
        tokenCount++;
    }

    return tokenCount;
}