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

FILE *fptr;
char filename[MAXIDLEN];
token current_token;
char token_buffer[];

// For sym table
//extern int lookup(string s); // Check variable already exists
//extern void enter(string s); // Declare variable

char * extractoperator(op_rec op){
    switch (op.operator) {
        case PLUS:
            return "add";
        case MINUS:
            return "sub";
    }
    return "";
}
char * extractexpression(expr_rec exp){
    static string tostring = "";
    switch (exp.kind) {
        case IDEXPR:
        case TEMPEXPR:
            sprintf(tostring, "%s",exp.name);
            return tostring;
        case LITERALEXPR:
            sprintf(tostring, "%d", exp.val);
            return tostring;
    }
    return "";
}

void generate(char *opcode, char *operand1, char *operand2){
    char instruction[200];

    FILE *fileOutput;
    fileOutput = fopen (filename, "a+");
    strcpy(instruction, "\t");
    strcat(instruction, opcode);
    if(strcmp(operand1,"")!=0){
        strcat(instruction, " ");
        strcat(instruction, operand1);
    }
    if(strcmp(operand2,"")!=0){
            strcat(instruction, ", ");
            strcat(instruction, operand2);
    }

    strcat(instruction, "\n");
    strcat(instruction, "\0");

    fputs(instruction, fileOutput);

    fclose(fileOutput);
}


void check_id(string s){
    if(! lookup(s)){
        enter(s);
        //generate("Declare", s, "Integer");
        //El generate de aca se hace al final con todos los ids
    }
}

char *get_temp()
{
    static int max_temp=0;
    static char tempname[MAXIDLEN];

    max_temp++;
    sprintf(tempname, "Temp&%d", max_temp);
    check_id(tempname);
    return tempname;
};

void start(void)
{
    FILE *fileOutput;
    fileOutput = fopen (filename, "w");
    if(fileOutput==NULL){
        printf("Error opening file. Start in translator.c");
        exit(1);
    }
    fputs("global _main \n section .text \n _main: \n", fileOutput);
    fclose(fileOutput);

}

void finish(void)
{
    //declare data section
    FILE *fileOutput;
    fileOutput = fopen (filename, "a+");
    if(fileOutput==NULL){
        printf("Error opening file. Start in translator.c");
        exit(1);
    }

    // Creating data section
    fputs("section .data \n", fileOutput);

    // Writing each variable to data section an initializing each with 0
    for (int i = 0; i < len(); ++i) {
        fputs(symbolByIndex(i), fileOutput);
        fputs(": dd 0 \n", fileOutput);
    }
    fclose(fileOutput);
}

void assign(expr_rec target, expr_rec source)
{
    generate("mov", "eax", extractexpression(source));
    generate("mov", extractexpression(target), "eax");
    // variable = TEMP&#
    //generate("Store", extractexpression(source), extractexpression(target));
}


op_rec process_op(void)
{
    op_rec o;
    if(current_token  == PLUSOP){
        o.operator= PLUS;
    } else{
        o.operator=MINUS;
    }
    return o;
}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2){
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


void read_id(expr_rec in_var)
{
    generate("Read", in_var.name, "Integer");
}

expr_rec process_id(void)
{
    expr_rec t;
    check_id(token_buffer);
    t.kind = IDEXPR;
    strcpy(t.name, token_buffer);
    return t;
}

expr_rec process_literal(void){
    expr_rec t;
    t.kind=LITERALEXPR;
    (void) sscanf(token_buffer,"%d",& t.val);
    return t;
}

void  write_expr(expr_rec out_expr){
    //generate("Write", extract(out_expr), "Integer");
}

