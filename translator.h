//
// Created by esteban on 25/2/22.
//

#ifndef MICROCOMPILER_TRANSLATOR_H
#define MICROCOMPILER_TRANSLATOR_H

#include "types.h"

extern expr_rec process_literal(void);
extern void  write_expr(expr_rec out_expr);
extern expr_rec process_id(void);
extern op_rec process_op(void);
extern void read_id(expr_rec in_var);
extern void assign(expr_rec target, expr_rec source);
extern void generate(char *opcode, char *operand1, char *operand2);
extern string* extract(expr_rec expr); // Returns a pointer
extern void finish(void);
extern void start(void);
extern expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2);
extern expr_rec gen_conditional(expr_rec e1,expr_rec e2, expr_rec e3);


#endif //MICROCOMPILER_TRANSLATOR_H