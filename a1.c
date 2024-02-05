//A01366116 Caitlyn
//A01364159
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TEXT_SIZE 1024


void check(char str[], int* count) {
    char ch;
    int* p;
    for (int i = 0; i< MAX_TEXT_SIZE; i++) {
        ch=NULL;
        p=NULL;
         //printf("%c",str[i]);

        if (str[i]>='A'&&str[i]<='Z'){
            // use tolower method to convert character to lowercase
            str[i] = tolower(str[i]);
        }
        if (str[i]>='a' && str[i]<='z') {
          ch = str[i];
          //printf("%c",ch);
          p = count + ch - 'a';
         //printf("%c\n",ch);
          (*p)++;
        }

        }
    }

int areAnagrams(char str1[], char str2[]) {
    int count1[26]={0};
    int count2[26]={0};
    // Count frequency of characters in both strings
    check(str1, count1);
    check(str2, count2);


    // Compare character counts of both strings
    for (int i = 0; i < 26; i++) {
        //printf("%d\n",count1[i]);
        //printf("%d\n",count2[i]);
        if (count1[i] != count2[i]) {
            // Not anagrams
            return 0;
        }
    }
    // Anagrams
    return 1;
}

  int main(int argc, char *argv[]){
  char str1[MAX_TEXT_SIZE]={0}, str2[MAX_TEXT_SIZE]={0};
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
        if (!isspace((unsigned char)ch)) {
            is_empty_or_whitespace = 0;
            break;
        }
    }

    if (!is_empty_or_whitespace) {
        rewind(file); // Go back to the start of the file to read the strings

        // Read the first string
        if (!fgets(str1, MAX_TEXT_SIZE, file)) {
            fprintf(stderr, "Error reading the first string\n");
            fclose(file);
            return 1;
        }
        // Read the second string
        if (!fgets(str2, MAX_TEXT_SIZE, file)) {
            fprintf(stderr, "Error reading the second string\n");
            fclose(file);
            return 1;
        }
        printf("%s\n", str2);
        printf("%s\n", str1);


        // Close the input file after reading
        fclose(file);

        // Open the output file for writing
        FILE *outputFile = fopen(outputFilename, "w");
        if (outputFile == NULL) {
            perror("Error opening output file");
            return 1;
        }

        // Check if the strings are anagrams and write the result to the output file

        if (areAnagrams(str1, str2)) {
            fprintf(outputFile, "1! anagram");
        } else {
            fprintf(outputFile, "0! not anagram");
        }

        fclose(outputFile); // Close the output file after writing
    } else {
        perror("Input file is empty or contains only whitespace");
        fclose(file); // Close the file if it's empty
    }

    return 0;
}
