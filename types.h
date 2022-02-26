//
// Created by eidur on 2/25/2022.
//

#ifndef MICROCOMPILER_TYPES_H
#define MICROCOMPILER_TYPES_H

#endif //MICROCOMPILER_TYPES_H


typedef enum  token_types{
    BEGIN, END, READ, WRITE, ID, INTLITERAL,
    LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
    PLUSOP, MINUSOP, SCANEOF
} token;