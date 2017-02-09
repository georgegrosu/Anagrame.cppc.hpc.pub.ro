//
//  main.c
//  Anagrame
//
//  Created by George Mircea on 2/8/17.
//  Copyright © 2017 Grosu George-Mircea. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** takeOutWords( char *fileContent);
char** sortWords( char **words, int wordCount);
char** makeUnique( char **words, int wordCount);
char* toLowercase( char *word);
int isAnagram( char *firstWord, char *secondWord);
void listWords( char **words, int wordCount);

int main(int argc, const char * argv[]) {
    char *fileContent;
    long fileSize;
    char **words = NULL;
    int wordCount = 0, i;
    
    if ( argc > 1) {
        
        FILE *wordsFile = fopen( argv[1], "rt");
        if ( wordsFile == NULL) {
            exit( -1);
        }
        
        fseek( wordsFile, 0, SEEK_END);
        fileSize = ftell( wordsFile);
        fseek( wordsFile, 0, SEEK_SET);
        
        fileContent = malloc( fileSize);
        if ( fileContent == NULL) {
            exit( -1);
        }
        
        fread( fileContent, fileSize, 1, wordsFile);
        
        words = takeOutWords( fileContent);
        
        while ( words[ wordCount] != NULL) {
            wordCount ++;
        }
        
        words = makeUnique( words, wordCount);
        
        wordCount = 0;
        while ( words[ wordCount] != NULL) {
            wordCount ++;
        }
        
        words = sortWords( words, wordCount);
        
        listWords( words, wordCount);
        
        for ( i=0; i < wordCount; i++) {
            free( words[i]);
        }
        
        free( words);
        
        free( fileContent);
        fclose( wordsFile);
    }
    else {
        printf( "Introduceti numele fisierului!\n");
    }
    return 0;
}

void listWords( char **words, int wordCount) {
    int i, j;
    int *printedWord;
    
    printedWord = calloc( wordCount, sizeof(int));
    
    for ( i=0; i < wordCount; i++) {
        if ( printedWord[i] == 0) {
            printf( "%s", words[i]);
            printedWord[i] = 1;
            for ( j=i+1; j < wordCount; j++) {
                if ( isAnagram( words[i], words[j]) && printedWord[j] == 0) {
                    printf( "-%s", words[j]);
                    printedWord[j] = 1;
                }
            }
            printf( "\n");
        }
    }
    
    free( printedWord);
}

int isAnagram( char *firstWord, char *secondWord){
    
    int firstWordCharsSum=0, secondWordCharsSum=0;
    unsigned long i;
    
    for ( i=0; i < strlen( firstWord); i++) {
        firstWordCharsSum += firstWord[i];
    }

    for ( i=0; i < strlen( secondWord); i++) {
        secondWordCharsSum += secondWord[i];
    }
    
    if ( firstWordCharsSum == secondWordCharsSum) {
        return 1;
    }
    else {
        return 0;
    }
    
}

char* toLowercase( char *word) {
    unsigned long i;
    
    for ( i=0; i < strlen( word); i++) {
        word[i] = tolower( word[i]);
    }
    
    return  word;
}

char** makeUnique( char **words, int wordCount) {
    int i, j;
    
    for ( i=0; i < wordCount-1; i++) {
        for ( j=i+1; j < wordCount; j++) {
            if ( strcmp( toLowercase( words[i]), toLowercase( words[j])) == 0 ) {
                if ( j == wordCount-1) {
                    words[ wordCount-1] = NULL;
                    wordCount --;
                }
                else {
                    strcpy( words[j], words[ wordCount-1]);
                    words[ wordCount-1] = NULL;
                    wordCount --;
                }
                j--;
            }
         }
    }
    
    words = realloc( words, wordCount * sizeof(char*));
    
    return words;
}

char** sortWords( char **words, int wordCount) {
    int i, j;
    char *wordKeeper;
    
    wordKeeper = malloc(1);
    
    for ( i=0; i < wordCount-1; i++) {
        for ( j=i+1; j < wordCount; j++) {
            if ( strcmp( words[i], words[j]) > 0) {
                
                wordKeeper = realloc( wordKeeper, strlen(words[i]) + 1);
                if ( words[i] == NULL) {
                    exit( -1);
                }
                strcpy( wordKeeper, words[i]);
                
                words[i] = realloc( words[i], strlen(words[j]) + 1);
                if ( words[i] == NULL) {
                    exit( -1);
                }
                strcpy( words[i], words[j]);
                
                words[j] = realloc( words[j], strlen(wordKeeper) + 1);
                if ( words[j] == NULL) {
                    exit( -1);
                }
                strcpy( words[j], wordKeeper);
            
            }
        }
    }

    free( wordKeeper);
    return words;
}

char** takeOutWords( char *fileContent) {
    char delimitators[] = " \n,.;\"\t-:!?";
    char *wordKeeper;
    int wordCount = 0;
    char **words;
    
    wordKeeper = malloc( strlen( fileContent) + 1);
    if ( wordKeeper == NULL) {
        exit( -1);
    }
    
    words = malloc( sizeof(char*) );
    if ( words == NULL) {
        exit( -1);
    }
    wordKeeper = strtok( fileContent, delimitators);
    words[wordCount] = malloc( strlen(wordKeeper) + 1);
    if ( words[ wordCount] == NULL) {
        exit( -1);
    }
    strcpy( words[ wordCount], wordKeeper);
    
    wordKeeper = strtok( NULL, delimitators);
    
    while ( wordKeeper != NULL) {
        
        wordCount ++;
        words = realloc( words, (wordCount+1) * sizeof(char*));
        if ( words == NULL) {
            exit( -1);
        }
        words[wordCount] = malloc( strlen(wordKeeper) + 1);
        if ( words[ wordCount] == NULL) {
            exit( -1);
        }
        strcpy( words[ wordCount], wordKeeper);
        wordKeeper = strtok( NULL, delimitators);
        
    }
    
    free( wordKeeper);
    
    return words;
}
