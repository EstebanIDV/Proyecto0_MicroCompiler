//
// Created by eidur on 2/25/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "parser.h"
#include "scanner.h"
#include "translator.h"

FILE *fptr;
extern token nxt_token;
char filename[MAXIDLEN];
token current_token;
token nxt_token;
char token_buffer[];

void primary (expr_rec *nextexpr){
    token tok = next_token();

    switch (tok) {
        case LPAREN:
            match(LPAREN);
            expression(nextexpr);
            match(RPAREN);
            break;
        case ID:
            *nextexpr = process_id();
            match(ID);
            break;

        case INTLITERAL:
            *nextexpr=process_literal();
            match(INTLITERAL);

            break;
        default:
            syntax_error(tok);
            break;
    }
}

void add_op(op_rec *oper){
    token tok = next_token();
    if (tok == PLUSOP || tok == MINUSOP)
        match(tok);
    else
        syntax_error(tok);
    *oper = process_op();

}

/*
 *
 *
 *
 void expression(void){
    token t;
    primary();
    for (t = next_token();  t ==PLUSOP || t== MINUSOP; t=next_token()) {
        add_op();
        primary();
    }
}
 *
 *
 */

void expression(expr_rec *result){
    expr_rec left_operand, right_operand;
    op_rec op;

    primary(& left_operand);
    while (next_token()==PLUSOP|| next_token()==MINUSOP){
        add_op(& op);
        primary(& right_operand);
        left_operand= gen_infix(left_operand,op,right_operand);
    }
    *result=left_operand;
}

void expr_list(void){
    /* <exp list> ::= <expression> { , <expression>} */

    expr_rec tempExpr;
    expression(&tempExpr);
    //Write expression in file?
    write_expr(tempExpr);
    while (next_token() == COMMA) {
        match(COMMA);
        expression(&tempExpr);
        write_expr(tempExpr);
    }
}

// This is used to read function
void id_list(void)
{
    /* <id list> ::= ID ( , ID) */
    expr_rec tempId = process_id();
    match(ID);
    read_expr(tempId);
    while (next_token()==COMMA){
        match(COMMA);
        expr_rec tempId = process_id();
        read_expr(tempId);
        match(ID);
    }
}

void statement(void){
    token tok = next_token();
    expr_rec tempIDEXPR;
    switch (tok) {
        case ID:
            tempIDEXPR = process_id();
            match(ID);
            match(ASSIGNOP);
            expr_rec tempExpr;
            expression(&tempExpr);
            assign(tempIDEXPR, tempExpr); //Write expression in file
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
        case COMMENT:
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
            case COMMENT:
                nxt_token=scanner();
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

void system_goal(void){
    start();
    nxt_token=scanner();
    program();
    match(SCANEOF);
    finish();
}
token next_token(){
    return nxt_token;
};

void match(token t) {
    current_token = next_token();
    if (current_token != SCANEOF) {
        nxt_token = scanner();
    }
    if (t != current_token) {
        syntax_error(t);
    }
}
/*
token next_token(){
    current_token = scanner();
    return current_token;
};

void match(token t){
    if (t == scanner()){
        current_token = t;
    } else{
        syntax_error(t);
    }


    current_token = next_token();
    if (t != current_token) {
        syntax_error(t);;
    } else if (current_token != SCANEOF) {
        nxt_token = scanner();
    }
}
*/
extern void syntax_error(token t){
    fprintf(stdout, "Syntax Error in %s token. Expected %i instead. ", token_buffer, t);
    if (remove(filename) == 0)
        printf("Deleted successfully\n");
    else
        printf("Unable to delete the file\n");
    exit(1);
};