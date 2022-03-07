//
// Created by diegomv on 6/3/22.
//

#include "types.h"

#ifndef MICROCOMPILER_SYMBOLS_TABLE_H
#define MICROCOMPILER_SYMBOLS_TABLE_H
#include "types.h"
#include <stdio.h>
extern int lookup(string sym);
extern void enter(string sym);
extern void printAll();
extern int len();
extern char * symbolByIndex(int index);

#endif //MICROCOMPILER_SYMBOLS_TABLE_H
