#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
    char* line;
    while((line = readline("$")) != NULL) {
        if(strcmp(line, "exit") == 0) {
            break;
        }
        if(strcmp(line, "hello") == 0) {
            printf("Hello, world!\n");
        } else {
            printf("Unknown command: %s\n", line);
        }
        add_history(line);
        free(line);
    }
    return 0;
}