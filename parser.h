//
// Created by eidur on 2/25/2022.
//

#ifndef MICROCOMPILER_PARSER_H
#define MICROCOMPILER_PARSER_H

extern void match(token t);
extern void syntax_error(token t);
extern token next_token();
extern void primary (expr_rec *nextexpr);
extern void add_op(op_rec *operator);
extern void expression(expr_rec *result);
extern void expressionParen(expr_rec *result);
extern void expr_list(void);
extern void id_list(void);
extern void statement_list(void);
extern void program(void);
extern void system_goal(void);
extern void statement(void);

#endif //MICROCOMPILER_PARSER_H