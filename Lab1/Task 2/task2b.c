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

    // Open the output file for writing
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Could not open output file.\n");
        fclose(inputFile); // Close input file before exiting
        return 1;
    }

    // Read input from the file
    while (fgets(str, sizeof(str), inputFile) != NULL) {
        // Remove the newline character, if any
        str[strlen(str) - 1] = '\0';

        // Tokenize the string
        token = strtok(str, " ");
        while (token != NULL) {
            // Write each token to the output file with a single space
            fprintf(outputFile, "%s ", token);
            token = strtok(NULL, " ");
        }
        fprintf(outputFile, "\n"); // Add a newline after processing each line
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Check 'output.txt' for results.\n");
    return 0;
}