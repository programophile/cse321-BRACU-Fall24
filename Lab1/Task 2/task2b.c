#include <stdio.h>
#include <string.h>

int main() {
    char str[1000]; 
    char *token;
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Could not open output file.\n");
        fclose(inputFile); 
        return 1;
    }

    // Read input from the file
    while (fgets(str, sizeof(str), inputFile) != NULL) {
        token = strtok(str, " ");
        while (token != NULL) {
            fprintf(outputFile, "%s ", token);
            token = strtok(NULL, " ");
            if (token == NULL) break;
        }
        fprintf(outputFile, "\n");
    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Check 'output.txt' for results.\n");
    return 0;
}
}