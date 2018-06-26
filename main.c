#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEW_FILE_END ".rpl"
#define BLEND_FILE_END ".bend"
#define WORD_SEPARATOR ' '
#define LINE_SEPARATOR '.'
#define MAX_WORD_LEN 20
#define MAX_WORDS_IN_SENTENCE 15

FILE *copyTextReveresed(FILE *originalFile, char *originalFileName);

FILE *blendFile(FILE *originalFile, char *originalFileName);

int main(int argc, char **argv) {
    FILE *originalFile=NULL;
    FILE *newFile=NULL;
    FILE *blendedFile=NULL;
    if (argc < 2){
        printf("Invalid input. expected: ./executionName fileName.dat\n");
        exit(1);

    }

    originalFile = fopen(argv[1],"r+");

    if (!originalFile){
        printf("File not found\n");
        exit(2);
    }

    newFile = copyTextReveresed(originalFile,argv[1]);
    printf("here");
    blendedFile = blendFile(originalFile,argv[1]);


    fclose(originalFile);
    fclose(newFile);
    fclose(blendedFile);
    return 0;
}

FILE *blendFile(FILE *originalFileEnd, char *originalFileName) {
    FILE *blendedFile = fopen(strcat(originalFileName,BLEND_FILE_END),"w");
    FILE *originalFileStart;

    originalFileStart = originalFileEnd;
    fseek(originalFileEnd,-1,SEEK_END);

    while (ftell(originalFileStart) < ftell(originalFileEnd)){
        fputc(fgetc(originalFileStart),blendedFile);
        fputc(fgetc(originalFileEnd),blendedFile);
        fseek(originalFileEnd,-2,SEEK_CUR);
    }
    return blendedFile;
}

FILE *copyTextReveresed(FILE *originalFile, char *originalFileName) {
    FILE *newFile = fopen(strcat(originalFileName,NEW_FILE_END),"w");
    char *sentence[MAX_WORDS_IN_SENTENCE];
    char currentWord[MAX_WORD_LEN];
    int spotInCurrentWord=0;
    int wordsInSentence=0;
    int currentChar;
    int i;

    rewind(newFile);
    currentChar = fgetc(originalFile);

    while (currentChar != EOF){
        if (currentChar == LINE_SEPARATOR){
            if (spotInCurrentWord > 0){
                currentWord[spotInCurrentWord] = '\0';
                fprintf(newFile,"%s",currentWord);
                fputc(wordsInSentence==0?'.':' ',newFile);
            }
            for (i=wordsInSentence-1; i>=0; i--){
                fprintf(newFile,"%s",sentence[i]);
                free(sentence[i]);
                fputc(i==0? '.':' ',newFile);
            }
            fputc(' ',newFile);
            spotInCurrentWord = 0;
            wordsInSentence = 0;
        } else if (currentChar == WORD_SEPARATOR){
            if (spotInCurrentWord > 0) {
                currentWord[spotInCurrentWord] = '\0';
                sentence[wordsInSentence] =
                        (char *) malloc((strlen(currentWord) + 1) * sizeof(char));
                strcpy(sentence[wordsInSentence++], currentWord);
                spotInCurrentWord = 0;
            }
        } else {
            currentWord[spotInCurrentWord++] = (char)currentChar;
        }
        currentChar = fgetc(originalFile);
    }
}

