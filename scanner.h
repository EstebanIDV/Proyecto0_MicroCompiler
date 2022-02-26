//
// Created by eidur on 2/25/2022.
//

#ifndef MICROCOMPILER_SCANNER_H
#define MICROCOMPILER_SCANNER_H

#endif //MICROCOMPILER_SCANNER_H
#include "types.h"
void clear_buffer();
void buffer_char(char c);
void lexical_error(char c);
token check_reserved(char c);