//
// Created by esteban on 25/2/22.
//

#ifndef MICROCOMPILER_TRANSLATOR_H
#define MICROCOMPILER_TRANSLATOR_H

#include "types.h"


extern void generate(char *opcode, char *operand1, char *operand2, char *operand3);
extern void extract(); // HAY QUE PONER STRING EN VEZ DE VOID
extern void finish(void);

#endif //MICROCOMPILER_TRANSLATOR_H