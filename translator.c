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
    string temp;
    switch (exp.kind) {
        case IDEXPR:
        case TEMPEXPR:
            strcpy(temp, "[");
            strcat(temp, exp.name);
            strcat(temp, "]");
            sprintf(tostring, "%s", temp);
            return tostring;
        case LITERALEXPR:
            sprintf(tostring, "%d", exp.val);
            return tostring;
    }
    return "";
}

// This function extracts the expression without add "[" "]"
char *extractRawExpression(expr_rec exp) {
    static string tostring = "";
    string temp;
    switch (exp.kind) {
        case IDEXPR:
        case TEMPEXPR:
            strcpy(temp, exp.name);
            sprintf(tostring, "%s", temp);
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
    sprintf(tempname, "Temp_%d", max_temp);
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
    fputs("\nsection .data \n", fileOutput);
    fputs("inputFormat: db \"%d\",0 \n"
          "eol: db \"\", 10,0 \n", fileOutput);
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
    // Generate nasm code
    if (e1.kind == LITERALEXPR && e2.kind == LITERALEXPR){
        char str[30];
        if (op.operator==MINUS)
            sprintf(str, "%d",(atoi(extractexpression(e1)) - atoi(extractexpression(e2))));
        else
            sprintf(str, "%d",(atoi(extractexpression(e1)) + atoi(extractexpression(e2))));

        if(next_token()==MINUSOP || next_token()==PLUSOP){
            e_rec.kind = LITERALEXPR;
            (void) sscanf(str,"%d",& e_rec.val);
        } else {
            strcpy(e_rec.name, get_temp());
            generate("mov", "eax", str);
            generate("mov", extractexpression(e_rec), "eax"); // TEMP&# = e1 OP e2
        }
    } else {
        strcpy(e_rec.name, get_temp());
        generate("mov", "eax", extractexpression(e1));
        generate("mov", "ebx", extractexpression(e2));
        generate(extractoperator(op), "eax", "ebx");
        generate("mov", extractexpression(e_rec), "eax"); // TEMP&# = e1 OP e2
        //generate(extractoperator(op), extractexpression(e1), extractexpression(e2));
    }

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
    FILE *fileOutput;
    fileOutput = fopen(filename, "a+");
    if (fileOutput == NULL) {
        printf("Error opening file. Start in translator.c");
        exit(1);
    }else
    {


        char command[50] = "\t push dword ";
        strcat(command, extractexpression(out_expr));

        fputs(command, fileOutput);
        fputs("\n\tpush inputFormat \n"
              "\t call printf \n"
              "\tpop eax \n"
              "\tpop eax \n"
              "\n\n;Printing end of line\n"
              "\tpush eol \n"
              "\tcall printf \n"
              "\tpop eax \n\n", fileOutput);

//    generate("mov", "eax", extractexpression(out_expr));
        fclose(fileOutput);
    }
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

        fputs(strcat(command, extractRawExpression(out_expr)), fileOutput);
        fputs("\n\t push inputFormat\n"
              "\t call scanf\n"
              "\t pop eax \n"
              "\t pop eax \n\n", fileOutput);
    };

    fclose(fileOutput);
}
