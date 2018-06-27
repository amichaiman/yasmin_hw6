#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileFunctions.h"

int main(int argc, char** argv) {
    FILE *file;
    FILE *changeWordOrderFile;
    FILE *blendedFile;
    FILE *compressedFile;
    char *changeWordOrderFileName;

    if (argc < 2){
        printf("ERROR. expected: ./executionName fileName\n");
        exit(1);
    }

    file = fopen(argv[1],"r+");

    if (!file){
        printf("ERROR. could'nt open file\n");
        exit(2);
    }

    changeWordOrderFile = changeWordOrder(file,argv[1]);
    blendedFile = blendFile(changeWordOrderFile,argv[1]);


    /*  create string with original file name + ".rpl" extension    */
    changeWordOrderFileName = (char*) malloc ((strlen(argv[1])
                                              +strlen(REVERSED_ORDER_EXTENSION)+1)*sizeof(char));
    strcpy(changeWordOrderFileName,argv[1]);
    strcat(changeWordOrderFileName,REVERSED_ORDER_EXTENSION);


    compressedFile = compressFile(changeWordOrderFileName);

    fclose(file);
    fclose(changeWordOrderFile);
    fclose(blendedFile);
    fclose(compressedFile);
    return 0;
}

