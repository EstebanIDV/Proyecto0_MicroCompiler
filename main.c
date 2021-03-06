#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "parser.h"
#include "string.h"

// gcc -Wall scanner.c translator.c parser.c symbols_table.c main.c types.h -o micro
//FILE *fptr;
//char filename[MAXIDLEN];

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("Error, no program given to compile.\n");
        exit(1);
    } else if (argc > 2) {
        printf("Error, 2 or more program2 given to compile. Expected 1.\n");
        exit(1);
    }
    if (strlen(argv[1]) > MAXIDLEN) {
        printf("Error, the name of the file must be 32 characters long of lower.\n");
    }
    char temp[MAXIDLEN];
    char rawname[MAXIDLEN];
    strcpy(temp, argv[1]);
    int flag = 0;
    int i = 0;
    while (i < strlen(temp)) {
        if (temp[i] == *".") {
            if (strncmp(&temp[i+1], "t", 1)!=0 || strncmp(&temp[i+2], "x", 1)!=0 || strncmp(&temp[i+3], "t", 1)!=0 || strncmp(&temp[i+4],"\000", 1)!=0){
                printf("Error, the file extension is not .txt!\n");
                exit(1);
            }
            strcat(filename, &temp[i]);
            flag = 1;
            break;
        }
        i++;
    }

    strcpy(filename, temp);



    if (flag == 1) {
        filename[i + 1] = *"a";
        filename[i + 2] = *"s";
        filename[i + 3] = *"m";
        i += 4;
        while (i < MAXIDLEN) {
            temp[i] = *"\0";
            filename[i] = *"\0";
            i++;
        }
    }
    else {

        strcat(temp, ".txt");
        strcat(filename, ".asm");
    }
    // COLOCAR EN FUNCION DE RENOMBRAR
    // printf("Nombre del archivo> %s\n", filename);
    if ((fptr= fopen(temp,"r")) == NULL){
        printf("Error! when opening file %s\n", argv[1]);
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    system_goal();
    fclose(fptr);

    // Calling system to translate and run nasm code

    //char command[200] = "nasm -f elf32 entrada.asm && gcc -m32 -static entrada.o -o entrada && ./entrada";
    char command[200];
    strcpy(rawname,"");
    strcpy(rawname,filename);
    rawname[strlen(rawname)-4] = *"\0";
    sprintf(command,"nasm -f elf32 %s && gcc -m32 -static %s.o -o %s && ./%s", filename, rawname, rawname,rawname);
    system(command);
    return 0;
}


// push dword variable
// push inputFormat
// call printf
// pop eax
// pop eax