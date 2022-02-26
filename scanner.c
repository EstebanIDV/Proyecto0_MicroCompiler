//
// Created by eidur on 2/25/2022.
//

#include <stdio.h>
#include <ctype.h>
#include "types.h"
#include "scanner.h"
#include <stdlib.h>
#include <string.h>

extern char token_buffer[];

token scanner(void){
    int in_char, c;
    clear_buffer();
    if(feof(stdin)){
        return SCANEOF;
    }
    while((in_char=getchar())!=EOF){
        if(isspace(in_char))
            continue;
        else if(isalpha(in_char)){
            buffer_char(in_char);
            for(c=getchar(); isalnum(c) || c=='_';c=getchar())
                buffer_char(c);
            ungetc(c,stdin);
            return check_reserved();
        } else if (isdigit(in_char)){
            buffer_char(in_char);
            for(c=getchar(); isdigit(c); c=getchar())
                buffer_char(c);
            ungetc(c, stdin);
            return INTLITERAL;
        } else if(in_char=='(')
            return  LPAREN;
        else if (in_char==')')
            return RPAREN;
        else if (in_char==';')
            return SEMICOLON;
        else if (in_char==',')
            return COMMA;
        else if (in_char=='+')
            return PLUSOP;
        else if (in_char==':'){
            c=getchar();
            if(c=='=')
                return ASSIGNOP;
            else{
                ungetc(c, stdin);
                lexical_error(in_char);
            }

        } else if (in_char=='-'){
            c=getchar();
            if(c=='-'){
                do
                    in_char = getchar();
                while (in_char!='\n');
            } else{
                ungetc(c, stdin);
                return MINUSOP;
            }
        } else
            lexical_error(in_char);
    }

}

extern void buffer_char(int c){
    token_buffer[strlen(token_buffer)] = c;
};

extern token check_reserved(void){
    char *write = "write";
    char *read  = "read";
    char *end   = "end";
    char *begin = "begin";
    char *temp  =  token_buffer;

    if(is_equal(temp, write)){
        return WRITE;
    } else if (is_equal(temp, read)){
        return READ;
    } else if (is_equal(temp, end)){
        return END;
    } else if (is_equal(temp, begin)){
        return BEGIN;
    } else{
        return ID;
    }
}

extern void clear_buffer(void){
    for (int i = strlen(token_buffer); i >= 0; --i) {
        token_buffer[i] = 0;
    }
}

int is_equal(char* temp, char* token)
{
    int is_equal = 1; // True
    if (strlen(temp)!=strlen(token)){
        is_equal = 0; // False
        return is_equal;
    }
    for (int i = 0; i < strlen(token); i++)
    {
        if(tolower(temp[i]) != token[i])
        {
            is_equal = 0; // False
            break;
        }
    }
    return is_equal;
}

void lexical_error(int in_char){
    printf(stderr, "Lexical Error located in: %c", in_char);
    exit(1);
}
