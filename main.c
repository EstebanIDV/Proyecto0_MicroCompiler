#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "parser.h"
#include "string.h"

// gcc -Wall scanner.c translator.c parser.c symbols_table.c main.c types.h -o micro
FILE *fptr;
char filename[MAXIDLEN];

int main(int argc, char** argv) {
    if (argc <= 1){
        printf("Error, no program given to compile.\n");
        exit(1);
    }
    if (strlen(argv[1])>MAXIDLEN){
        printf("Error, the name of the file must be 32 characters long of lower.\n");
    }
    char temp[MAXIDLEN];
    strcpy(temp, argv[1]);
    int i = 0;
    while (temp[i] != *"."){
        //printf("%s", &argv[1][i]);
        strcat(filename, &temp[i]);
        i++;
    }
    temp[i+1] = *"a";
    temp[i+2] = *"s";
    temp[i+3] = *"m";
    i += 4;
    while (i<MAXIDLEN){
        temp[i] = *"\0";
        i++;
    }
    // COLOCAR EN FUNCION DE RENOMBRAR

    strcpy(filename, temp);
    // printf("Nombre del archivo> %s\n", filename);
    if ((fptr= fopen(argv[1],"r")) == NULL){
        printf("Error! opening file %s\n", argv[1]);
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    system_goal();
    fclose(fptr);
    return 0;
}
