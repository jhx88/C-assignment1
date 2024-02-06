//A01366116 Caitlyn
//A01364159
//A01355003
//A01357572
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(char str[], int* count) {
    char ch;
    int* p;
    for (int i = 0; str[i] != '\0'; i++) {
        // ch = NULL;
        p = NULL;


        if (str[i]>='A' && str[i]<='Z') {
            //convert character to lowercase
            str[i] = str[i] + 32;
        }
        if (str[i]>='a' && str[i]<='z') {
            ch = str[i];
            p = count + ch - 'a';
            (*p)++;
        }
        }
    }

int areAnagrams(char str1[], char str2[]) {
    int *count1 = (int *)malloc(26 * sizeof(int));
    int *count2 = (int *)malloc(26 * sizeof(int));

    if (count1 == NULL || count2 == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }   

    // initialize arrays
    memset(count1, 0, 26 * sizeof(int));
    memset(count2, 0, 26 * sizeof(int));

    // Count frequency of characters in both strings
    check(str1, count1);
    check(str2, count2);

    // Compare character counts of both strings
    for (int i = 0; i < 26; i++) {
        if (count1[i] != count2[i]) {
            // Not anagrams
            free(count1);
            free(count2);
            return 0;
        }
    }

    free(count1);
    free(count2);
    // Anagrams
    return 1;
}

int isWhitespace(int ch) {
    // white spaces in ascii 
    return ch == 32 || ch == 9 || ch == 10 || ch == 13;
}

int main(int argc, char *argv[]) {
    char *str1, *str2;
    char *filename = argv[1];
    char *outputFilename = argv[2];
    int is_empty_or_whitespace = 1;

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    // Check if the file is empty or contains only white space
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (!isWhitespace((unsigned char)ch)) {
            is_empty_or_whitespace = 0;
            break;
        }
    }

    if (!is_empty_or_whitespace) {
        rewind(file); // Go back to the start of the file to read the strings

        // read the first string
        // allocate possible max size
        str1 = (char *)malloc(1024 * sizeof(char)); 
        if (str1 == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            return 1;
        }

        if (!fgets(str1, 1024, file)) {
            fprintf(stderr, "Error reading the first string\n");
            fclose(file);
            free(str1);
            return 1;
        }

        // read the second string and allocate
        str2 = (char *)malloc(1024 * sizeof(char));
        if (str2 == NULL){
            fprintf(stderr, "Memory allocation failed\n");
            fclose(file);
            free(str1);
            return 1;
        }

        if (!fgets(str2, 1024, file)) {
            fprintf(stderr, "Error reading the first string\n");
            fclose(file);
            free(str1);
            free(str2);
            return 1;
        }

        // Close the input file after reading
        fclose(file);

        // Open the output file for writing
        FILE *outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            free(str1);
            free(str2);
            return 1;
        }

        // Check if the strings are anagrams and write the result to the output file
        if (areAnagrams(str1, str2)) {
            fprintf(outputFile, "1! anagram");
        } else {
            fprintf(outputFile, "0! not anagram");
        }

        fclose(outputFile); // Close the output file after writing

        free(str1);
        free(str2);

    } else {
        FILE *outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            free(str1);
            free(str2);
            return 1;
        }

        fprintf(outputFile, "Error: input file is empty"); // write error message to the output file
        fclose(file); // Close the file if it's empty
    }

    return 0;
}
