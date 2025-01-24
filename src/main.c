#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "compiler/token.h"
#include "util/util.h"

int main(void) {

    char* file_contents[1024];
    int num_lines = read_from_file("example.6502", file_contents);

    for (int i = 0; i < num_lines; i++) {
        Token tokens[MAX_TOKENS];
        int num_tokens = tokenize_line(file_contents[i], tokens);

        for (int j = 0; j < num_tokens; j++) {
            switch (tokens[j].type) {
                case TOKEN_LABEL:
                    printf("Label: %s\n", tokens[j].value);
                    break;
                case TOKEN_OPCODE:
                    printf("%s ", tokens[j].value);
                    break;
                case TOKEN_OPERAND:
                    printf("%s \n", tokens[j].value);
                    break;
                case TOKEN_COMMENT:
                    printf("%s\n", tokens[j].value);
                    break;
                case TOKEN_UNKNOWN:
                    printf("Failed to find operand\n");
                    break;
            }
        }    
        
    }

    return 0;
}