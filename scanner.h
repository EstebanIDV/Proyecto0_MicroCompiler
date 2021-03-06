//
// Created by eidur on 2/25/2022.
//

#ifndef MICROCOMPILER_SCANNER_H
#define MICROCOMPILER_SCANNER_H


#include "types.h"

extern char token_buffer[MAXIDLEN];
extern token scanner(void);
extern void clear_buffer(void);
extern void buffer_char(int c);
extern void lexical_error(int c);
extern token check_reserved(void);
extern int is_equal(char* temp, char* token);

#endif //MICROCOMPILER_SCANNER_H