#include "FileFunctions.h"

FILE *blendFile(FILE *file, char *fileName) {
    FILE* newFile;
    char *newFileName;
    long fileLen;
    int i;

    /*  create new file with ".bend" extension  */
    newFileName = (char*) malloc ((strlen(fileName)
                                   +strlen(BLENDED_EXTENSION)+1)*sizeof(char));
    strcpy(newFileName,fileName);
    strcat(newFileName,BLENDED_EXTENSION);
    newFile = fopen(newFileName, "w+");
    free(newFileName);

    /*  get file len    */
    fseek(file,0,SEEK_END);
    fileLen = ftell(file)-1;
    fseek(file,0,SEEK_SET);

    for (i=0; i<fileLen/2; i++){
        /*  write letter from left  */
        fseek(file,i,SEEK_SET);
        fputc(fgetc(file),newFile);

        /*  write letter from right  */
        fseek(file,-i-2,SEEK_END);
        fputc(fgetc(file),newFile);
    }
    return newFile;
}

FILE *changeWordOrder(FILE *file, char *fileName) {
    char *sentence[MAX_WORDS_IN_SENTENCE];
    char currentWord[MAX_WORD_LEN];
    FILE *newFile;
    int spotInCurrentWord=0;
    int wordsInSentence=0;
    int currentChar;
    int i;
    char *newFileName;

    /*  create new file with .rpl extension */
    newFileName= (char*) malloc ((strlen(fileName)
                                  +strlen(REVERSED_ORDER_EXTENSION)+1)*sizeof(char));
    strcpy(newFileName,fileName);
    strcat(newFileName,REVERSED_ORDER_EXTENSION);
    newFile = fopen(newFileName, "w+");
    free(newFileName);

    currentChar = fgetc(file);

    while (currentChar != EOF){
        /*  if we reached end of line, write it backwards to output file    */
        if (currentChar == LINE_SEPARATOR){
            /*  write the last word that was read (which is still in the buffer)   */
            if (spotInCurrentWord > 0){
                currentWord[spotInCurrentWord] = '\0';
                fprintf(newFile,"%s",currentWord);
                fputc(wordsInSentence==0?'.':' ',newFile);
            }
            /*  write backwards all the words in sentence   */
            for (i=wordsInSentence-1; i>=0; i--){
                fprintf(newFile,"%s",sentence[i]);
                free(sentence[i]);
                fputc(i==0? '.':' ',newFile);
            }
            spotInCurrentWord = 0;
            wordsInSentence = 0;
            /*  if we reached end of word, add it to word array */
        } else if (currentChar == WORD_SEPARATOR){
            /*  if the space character came after a word(rather than a
             *  couple of spaces in a row)  */
            if (spotInCurrentWord > 0) {
                currentWord[spotInCurrentWord] = '\0';
                sentence[wordsInSentence] =
                        (char *) malloc((strlen(currentWord) + 1) * sizeof(char));
                strcpy(sentence[wordsInSentence++], currentWord);
                spotInCurrentWord = 0;
            }
            /*  if we are at a letter inside a word */
        } else {
            currentWord[spotInCurrentWord++] = (char)currentChar;
        }
        currentChar = fgetc(file);
    }
    return newFile;
}

FILE *compressFile(char *fileName) {
    char *newFileName;

    /*  buffer containing coded information of characters
     *  that have already been read */
    unsigned char buffer[MAX_LETTERS_IN_ROW/2] = {0};

    /*  current Byte index  */
    int indexInBuffer=0;

    /*  pointer to output file  */
    FILE *compressedFile = NULL;

    /*  pointer to input file   */
    FILE *file;

    /*  given letter's code */
    int lettersCode;

    /*  number of unique letters in row */
    int numOfLetters = 0;

    /*  array holding the unique letter.
     *  each letters code is it's corresponding index   */
    char letters[MAX_UNIQUE_LETTERS_IN_SENTENCE];

    /*  1 Byte holding information regarding two characters */
    unsigned char toWrite=0;

    /*  loop index  */
    int i;

    /*  current charater being read from input file */
    int c;

    /*  create new output file with ".rds" extension    */
    newFileName = (char*) malloc ((strlen(fileName)
                                   + strlen(COMPRESSED_EXTENSION) + 1) * sizeof(char));

    fileName[strcspn(fileName,".")] = '\0';
    strcpy(newFileName,fileName);
    strcat(newFileName,COMPRESSED_EXTENSION);
    compressedFile = fopen(newFileName,"wb");
    free(newFileName);

    file = fopen(fileName,"r");
    initializeLetters(letters);
    c=fgetc(file);

    while(c != EOF){
        /*  if we hit end of line, write it to output file as following:
         *  1) number of unique letters
         *  2) sequence of the unique letters corresponding to their appearance
         *  3) the coded information that has been gathered in the buffer   */
        if (c==LINE_SEPARATOR){
            fputc((unsigned char)numOfLetters,compressedFile);

            for(i=0; i<numOfLetters; i++){
                fputc(letters[i],compressedFile);
            }
            for (i=0; i<indexInBuffer; i++){
                fputc(buffer[i],compressedFile);
            }
            /*  re-initialize variables */
            initializeLetters(letters);
            numOfLetters = 0;
            indexInBuffer = 0;
        } else {
            /*  compress two letters to one byte, and write to buffer   */
            lettersCode = getCode(letters, c, &numOfLetters);
            if (lettersCode == -1){
                printf("ERROR: could'nt compress file\n");
                exit(3);
            }
            toWrite = (unsigned char) lettersCode;
            toWrite <<= 4;

            c = fgetc(file);
            if (c == LINE_SEPARATOR){
                printf("ERROR: Uneven number of letters in row\n");
                exit(4);
            }
            lettersCode = getCode(letters, c, &numOfLetters);
            if (lettersCode == -1){
                printf("ERROR: could'nt compress file\n");
                exit(5);
            }
            toWrite |= lettersCode;
            buffer[indexInBuffer++] = toWrite;
        }
        c=fgetc(file);
    }

    return compressedFile;
}

/*  marks all letters as un-set*/
void initializeLetters(char *letters) {
    int i;
    for (i=0; i<MAX_UNIQUE_LETTERS_IN_SENTENCE; i++){
        letters[i] = -1;
    }
}
/*  returns given letter's code.
 *  if letter isn't in array of letters &
 *  there is room in the array, it is added.
 *  -1 if doesnt appear & the array is out of room  */
int getCode(char* letters, int c, int *len) {
    int i;

    for (i=0; i<*len; i++){
        if (letters[i] == c) {
            return i;
        }
    }
    if (*len < MAX_WORDS_IN_SENTENCE){
        letters[*len] = (char) c;
        return (*len)++;
    }
    return -1;
}
