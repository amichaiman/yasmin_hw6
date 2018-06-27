#ifndef HW6_FILEFUNCTIONS_H
#define HW6_FILEFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UNIQUE_LETTERS_IN_SENTENCE 16
#define MAX_WORDS_IN_SENTENCE 50
#define MAX_LETTERS_IN_ROW 1000
#define MAX_WORD_LEN 20
#define BLENDED_EXTENSION ".bend"
#define REVERSED_ORDER_EXTENSION ".rpl"
#define COMPRESSED_EXTENSION ".rds"

#define LINE_SEPARATOR '.'
#define WORD_SEPARATOR ' '

FILE *changeWordOrder(FILE *file, char *fileName);
FILE *blendFile(FILE *file, char *fileName);
FILE *compressFile(char *fileName);

void initializeLetters(char *letters);
int getCode(char* letters, int c, int *len);

#endif