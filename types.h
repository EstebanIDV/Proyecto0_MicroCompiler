//
// Created by eidur on 2/25/2022.
//

#ifndef MICROCOMPILER_TYPES_H
#define MICROCOMPILER_TYPES_H

#endif //MICROCOMPILER_TYPES_H
#include "stdbool.h"

typedef enum  token_types{
    BEGIN, END, READ, WRITE, ID, INTLITERAL,
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
    PLUSOP, MINUSOP, SCANEOF
} token;


#define MAXIDLEN 33
typedef  char string[MAXIDLEN];

typedef struct operator{
    enum op { PLUS, MINUS} operator;
} op_rec;


enum expr { IDEXPR, LITERALEXPR, TEMPEXPR};

typedef  struct  expression{
    enum expr kind;
    union{
        string name;
        int val;
    };
} expr_rec;
