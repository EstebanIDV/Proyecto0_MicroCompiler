//
// Created by eidur on 2/25/2022.
//
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "types.h"
#include "parser.h"
void primary (void){
    token tok = next_token();

    switch (tok) {
        case LPAREN:
            match(LPAREN);
            match(RPAREN);
            break;
        case ID:
            match(ID);
            break;

        case INTLITERAL:
            match(INTLITERAL);
            break;
        default:
            syntax_error(tok);
            break;
        
    }
}

void add_op(void){
    token tok = next_token();
    if (tok == PLUSOP || tok == MINUSOP)
        match(tok);
    else
        syntax_error(tok);
}


void expression(void){
    token t;
    primary();
    for (t = next_token();  t ==PLUSOP || t== MINUSOP; t=next_token()) {
        add_op();
        primary();
    }
}

void expr_list(void){
    expression();
}
void id_list(void)
{
    match(ID);
    while (next_token()==COMMA){
        match(COMMA);
        match(ID);
    }
}

void statement(void){
    token tok = next_token();
    switch (tok) {
        case ID:
            match(ID);
            match(ASSIGNOP);
            expression();
            match(SEMICOLON);
            break;
        case READ:
            match(READ); match(LPAREN);
            id_list(); 
            match(RPAREN);
            match(SEMICOLON);
            break;
        case WRITE:
            match(WRITE); 
            match(LPAREN);
            expr_list();
            match(RPAREN);
            match(SEMICOLON);
            break;
        default:
            syntax_error(tok);
            break;
    }
}

void statement_list(void){
    statement();
    while (true){
        switch(next_token()){
            case ID:
            case READ:
            case WRITE:
                statement();
                break;
            default:
                return;
        }
    }
}

void program(void)
{
    match(BEGIN);
    statement_list();
    match(END);
}

void system_goal(void ){
    program();
    match(SCANEOF);
}