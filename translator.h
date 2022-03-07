//
// Created by esteban on 25/2/22.
//

#ifndef MICROCOMPILER_TRANSLATOR_H
#define MICROCOMPILER_TRANSLATOR_H

#include "types.h"


extern void generate(char *opcode, char *operand1, char *operand2, char *operand3);
extern string* extract(expr_rec expr); // Returns a pointer
extern void finish(void);
extern void start(void);

#endif //MICROCOMPILER_TRANSLATOR_H