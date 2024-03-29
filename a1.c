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
    char *str1 = NULL;
    char *str2 = NULL;
    char *filename = argv[1];
    char *outputFilename = argv[2];
    int is_empty_or_whitespace = 1;
    FILE *outputFile = fopen(outputFilename, "w");  // Open the output file for writing

    // Open the file for reading
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(outputFile, "error");
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

        int str1_length = 0;
        while ((ch = fgetc(file)) != '\n' && ch != EOF) {
            str1_length++;
        }
        rewind(file); // Go back to the start of the file to read the strings

        // allocate memory based on the length of the first string
        str1 = (char *)malloc((str1_length + 1) * sizeof(char));
        if (str1 == NULL) {
            fprintf(outputFile, "error");
            fclose(file);
            return 1;
        }

        if (!fgets(str1, str1_length + 1, file)) {
            fprintf(outputFile, "error");
            fclose(file);
            free(str1);
            return 1;
        }

        fgetc(file);

        int str2_length = 0;
        while ((ch = fgetc(file)) != '\n' && ch != EOF) {
            str2_length++;
        }

        // allocate memory based on the length of the second string
        str2 = (char *)malloc((str2_length + 1) * sizeof(char));
        if (str2 == NULL){
            fprintf(outputFile, "error");
            fclose(file);
            free(str1);
            return 1;
        }

        rewind(file);
        while((ch = fgetc(file)) != '\n' && ch != EOF);

        if (!fgets(str2, str2_length + 1, file)) {
            fprintf(outputFile, "error");
            fclose(file);
            free(str1);
            free(str2);
            return 1;
        }

        // Close the input file after reading
        fclose(file);

        if (outputFile == NULL) {
            fprintf(outputFile, "error");
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
            fprintf(outputFile, "error");
            free(str1);
            free(str2);
            return 1;
        }

        fprintf(outputFile, "error"); // write error message to the output file
        fclose(file); // Close the file if it's empty
    }

    return 0;
}
