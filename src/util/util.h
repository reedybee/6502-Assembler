#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

int read_from_file(char* filepath, char** contents) {

    int current_line = 0;

    FILE* file = fopen(filepath, "r");

    if (file == NULL) {
        printf("Failed to open file\n");
    }

    char buffer[1024];
    while (fgets(buffer, 1024, file)) {

        uint32_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        contents[current_line] = (char*)malloc(len + 1);
        strcpy(contents[current_line], buffer);
        current_line++;
    }
    fclose(file);
    return current_line;
}