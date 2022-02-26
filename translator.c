//
// Created by esteban on 25/2/22.
//

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "types.h"
#include "string.h"
#include "translator.h"


extern int lookup(string s);
extern void enter(string s);


void check_id(string s){
    if(! lookup(s)){
        enter(s);
        generate("Declare", s, "Integer", "");
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

}

void finish(void)
{

}

void assign(expr_rec target, expr_rec source)
{
    generate("Store", extract(source), target, target.name, "");
}


op_rec process_op(void)
{
    op_rec o;
    if(current_token  == PLUSOP){
        o.operator= PLUS;
    } else{
        o.operator=MINUS;
    }

}

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2){
    expr_rec e_rec;
    e_rec.kind = TEMPEXPR;

    strcpy(e_rec.name, get_temp());
    generate(extract(op), extract(e1),
             extract(e2), e_rec.name);

    return e_rec;
}


void read_id(expr_rec in_var)
{
    generate("Read", in_var.name, "Integer", "");

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
    generate("Write", extract(out_expr), "Integer", "");

}
