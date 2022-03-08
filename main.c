#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "translator.h"
#include "scanner.h"
#include "types.h"


int main(int argc, char** argv) {
    *filename = *argv[1];
    printf("Nombre del archivo> %s\n", argv[1]);
    if ((fptr= fopen(argv[1],"r+")) == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    system_goal();
    fclose(fptr);
    return 0;
}
