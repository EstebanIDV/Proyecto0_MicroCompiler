//
// Created by esteban on 25/2/22.
//

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "string.h"
#include "translator.h"
#include "parser.h"
#include "symbols_table.h"
#include "scanner.h"

//FILE *fptr;
//char filename[MAXIDLEN];
//token current_token;
//char token_buffer[];
int writeAmount;

// For sym table
//extern int lookup(string s); // Check variable already exists
//extern void enter(string s); // Declare variable

char *extractoperator(op_rec op) {
    switch (op.operator) {
        case PLUS:
            return "add";
        case MINUS:
            return "sub";
    }
    return "";
}

char *extractexpression(expr_rec exp) {
    static string tostring = "";
    switch (exp.kind) {
        case IDEXPR:
        case TEMPEXPR:
            sprintf(tostring, "%s", exp.name);
            return tostring;
        case LITERALEXPR:
            sprintf(tostring, "%d", exp.val);
            return tostring;
    }
    return "";
}

void generate(char *opcode, char *operand1, char *operand2) {
    char instruction[200];

    FILE *fileOutput;
    fileOutput = fopen(filename, "a+");
    strcpy(instruction, "\t");
    strcat(instruction, opcode);
    if (strcmp(operand1, "") != 0) {
        strcat(instruction, " ");
        strcat(instruction, operand1);
    }
    if (strcmp(operand2, "") != 0) {
        strcat(instruction, ", ");
        strcat(instruction, operand2);
    }

    strcat(instruction, "\n");
    strcat(instruction, "\0");

    fputs(instruction, fileOutput);

    fclose(fileOutput);
}


void check_id(string s) {
    if (!lookup(s)) {
        enter(s);
        //generate("Declare", s, "Integer");
        //El generate de aca se hace al final con todos los ids
    }
}

char *get_temp() {
    static int max_temp = 0;
    static char tempname[MAXIDLEN];

    max_temp++;
    sprintf(tempname, "Temp&%d", max_temp);
    check_id(tempname);
    return tempname;
};

void start(void) {
    FILE *fileOutput;
    fileOutput = fopen(filename, "w");
    if (fileOutput == NULL) {
        printf("Error opening file. Start in translator.c");
        exit(1);
    }
    fputs("extern scanf \n extern printf \n global main \n section .text \n main: \n", fileOutput);
    fclose(fileOutput);

}

void finish(void) {
    //declare data section
    FILE *fileOutput;
    fileOutput = fopen(filename, "a+");
    if (fileOutput == NULL) {
        printf("Error opening file. Start in translator.c");
        exit(1);
    }
    fputs("\nret\n\n", fileOutput);
    // Creating data section
    fputs("\n section .data \n", fileOutput);
    fputs("inputFormat: db \"%d\",0 \n", fileOutput);
    fputs("inputVariableAux: db \"Por favor ingrese el valor de la variable:  \",0 \n", fileOutput);

    // Writing each variable to data section an initializing each with 0
    for (int i = 0; i < len(); ++i) {
        fputs(symbolByIndex(i), fileOutput);
        fputs(": dd 0 \n", fileOutput);
    }
    fclose(fileOutput);
}

void assign(expr_rec target, expr_rec source) {
    generate("mov", "eax", extractexpression(source));
    generate("mov", extractexpression(target), "eax");
    // variable = TEMP&#
    //generate("Store", extractexpression(source), extractexpression(target));
}


op_rec process_op(void) {
    op_rec o;
    if (current_token == PLUSOP) {
        o.operator = PLUS;
    } else {
        o.operator = MINUS;
    }
    return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2) {
    expr_rec e_rec;
    e_rec.kind = TEMPEXPR;

    strcpy(e_rec.name, get_temp());
    // Generate nasm code
    generate("mov", "eax", extractexpression(e2));
    generate("mov", "ebx", extractexpression(e1));
    generate(extractoperator(op), "eax",
             "ebx");
    generate("mov", extractexpression(e_rec), "eax"); // TEMP&# = e1 OP e2
    //generate(extractoperator(op), extractexpression(e1), extractexpression(e2));

    return e_rec;
}


void read_id(expr_rec in_var) {
    generate("Read", in_var.name, "Integer");
}

expr_rec process_id(void) {
    expr_rec t;
    check_id(token_buffer);
    t.kind = IDEXPR;
    strcpy(t.name, token_buffer);
    return t;
}

expr_rec process_literal(void) {
    expr_rec t;
    t.kind = LITERALEXPR;
    (void) sscanf(token_buffer, "%d", &t.val);
    return t;
}

void write_expr(expr_rec out_expr) {
    //generate("Write", extract(out_expr), "Integer");
    writeAmount++;
    FILE *fileOutput;
    char printax[600];
    fileOutput = fopen(filename, "a+");
    if (fileOutput == NULL) {
        printf("Error opening file. Start in translator.c");
        exit(1);
    }
    strcpy(printax, "");
    sprintf(printax, "\t\tpush EAX\n"
                     "        push EBX\n"
                     "        push ECX\n"
                     "        push EDX\n"
                     "    \n"
                     "        xor edx, edx\n"
                     "        xor ecx, ecx\n"
                     "        mov ebx, 10\n"
                     "\n"
                     "        c1PAX%d: xor edx, edx\n"
                     "            div ebx\n"
                     "            push edx\n"
                     "            inc ecx\n"
                     "            cmp eax, 0\n"
                     "            jne c1PAX%d\n"
                     "            mov ah, 02h\n"
                     "        c2PAX%d: \n"
                     "            pop edx\n"
                     "            add dl, 30h\n"
                     "            int 21h\n"
                     "            loop c2PAX%d\n"
                     "    \n"
                     "        mov ah, 02h \n"
                     "\n"
                     "        mov dl, 10 \n"
                     "        int 21h   \n"
                     "        mov dl, 13 \n"
                     "        int 21h"
                     "\n"
                     "        pop EDX\n"
                     "        pop ECX\n"
                     "        pop EBX\n"
                     "        pop EAX\n", writeAmount, writeAmount, writeAmount, writeAmount);

    generate("mov", "eax", extractexpression(out_expr));
    fputs(printax, fileOutput);
    fclose(fileOutput);
}


// This function create an interruption to read a given variable from assembly
void read_expr(expr_rec out_expr) {

    FILE *fileOutput;
    fileOutput = fopen(filename, "a+");
    if (fileOutput == NULL) {
        printf("Error opening file. Start in translator.c");
        exit(1);
    } else {
        // This is a Nasm section to get a value fom user

        fputs("; This is a section to get user input\n", fileOutput);

        // Printing code to show user has to five a variable value
        fputs(";Telling user to enter a variable value \n"
              "\t push inputVariableAux \n"
              "\t call printf \n"
              "\t pop eax \n\n", fileOutput);

        // Generating code to get user input add move that value to variable
        char command[20] = "\t push ";
//        generate("push", extractexpression(out_expr), "");

        fputs(strcat(command, extractexpression(out_expr)), fileOutput);
        fputs("\n\t push inputFormat\n"
              "\t call scanf\n"
              "\t pop eax \n"
              "\t pop eax \n\n", fileOutput);
    };

    fclose(fileOutput);
}

//    ToDo: Cambiar el main para quitar _
//    ToDo: extract expre quitar devuelva nombre de variable con tmp y parentesís cuadrados y cambiar a _
//    ToDo: Agregar lo de sistem
