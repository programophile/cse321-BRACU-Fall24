#include <stdio.h>

int main() {
    char str[1000]; 
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    FILE *outputFile = fopen("output.txt", "w");
    while (fgets(str, sizeof(str), inputFile) != NULL) {
        int i = 0, start = 0;
        int spaceFlag = 0; // check if first space

        // line cheack
        while (str[i] != '\0') {
            if (str[i] == ' ') {
                if (!spaceFlag) { 
                    fprintf(outputFile, " ");
                    spaceFlag = 1;
                }
            } else if (str[i] != '\n') { 
                fprintf(outputFile, "%c", str[i]);
                spaceFlag = 0;
            }
            i++;
        }
        fprintf(outputFile, "\n"); 
    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Check 'output.txt' for results.\n");
    return 0;
}
}
