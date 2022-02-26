//
// Created by eidur on 2/25/2022.
//

#ifndef MICROCOMPILER_PARSER_H
#define MICROCOMPILER_PARSER_H

#endif //MICROCOMPILER_PARSER_H


#include "types.h"

void match(token t);
void syntax_error(token t);
token next_token();