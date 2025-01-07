#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg_C, char *arg_V[]) {
    if (arg_C != 2) {
        fprintf(stderr, "usage: %s <filename>\n", arg_V[0]);
        return 1;
    }

    FILE *file = fopen(arg_V[1], "a");
    if (file == NULL) {
        perror("error!!! file will not open");
        return 1;
    }

    char input[256];
    printf("enter the string to write the file (enter '-1' to stop):\n");

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", input);
    }

    fclose(file);
    printf("the string is written %s\n", arg_V[1]);
    return 0;
}
