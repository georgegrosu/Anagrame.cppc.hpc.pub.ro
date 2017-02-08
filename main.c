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

int takeOutWords( char *fileContent, char **words);
void sortWords( char **words, int wordCount);

int main(int argc, const char * argv[]) {
    char *fileContent;
    long fileSize;
    char **words = NULL;
    int wordCount;
    
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
        
        wordCount = takeOutWords( fileContent, words);
        //sortWords( words, wordCount);
        
        //printf( "%s\n", words[0]);
        
        printf( "sunt %d cuvinte\n", wordCount);
        
        free( fileContent);
        fclose( wordsFile);
    }
    else {
        printf( "Introduceti numele fisierului!\n");
    }
    return 0;
}

void sortWords( char **words, int wordCount) {
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
                words[i] = realloc( words[j], strlen(wordKeeper) + 1);
                if ( words[j] == NULL) {
                    exit( -1);
                }
                strcpy( words[j], wordKeeper);
            }
        }
    }
    
    free( wordKeeper);
}

int takeOutWords( char *fileContent, char **words) {
    char delimitators[] = " \n,.;\"\t-:!?";
    char *wordKeeper;
    int wordCount = 0;
    
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
    while ( words[ wordCount] != NULL) {
        printf( "%s\n", words[ wordCount]);
        wordCount ++;
        words = realloc( words, (wordCount+1) * sizeof(char*));
        words[wordCount] = malloc( strlen(wordKeeper) + 1);
        if ( words[ wordCount] == NULL) {
            exit( -1);
        }
        strcpy( words[ wordCount], wordKeeper);
        wordKeeper = strtok( NULL, delimitators);
    }
    free( wordKeeper);
    
    return wordCount;
}
