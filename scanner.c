//
// Created by eidur on 2/25/2022.
//

#include <stdio.h>
#include <ctype.h>
#include "types.h"
#include "scanner.h"
#include <stdlib.h>
#include <string.h>

FILE *fptr;
char filename[MAXIDLEN];
char token_buffer[];

token scanner(void){
    int in_char, c;
    clear_buffer();
    if(feof(fptr)){
        return SCANEOF;
    }
    while((in_char=fgetc(fptr))!=EOF){
        if(isspace(in_char))
            continue;
        else if(isalpha(in_char)){
            buffer_char(in_char);
            for(c=fgetc(fptr); isalnum(c) || c=='_';c=fgetc(fptr))
                buffer_char(c);
            ungetc(c,fptr);
            return check_reserved();
        } else if (isdigit(in_char)){
            buffer_char(in_char);
            for(c=fgetc(fptr); isdigit(c); c=fgetc(fptr))
                buffer_char(c);
            ungetc(c, fptr);
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
            c=fgetc(fptr);
            if(c=='=')
                return ASSIGNOP;
            else{
                ungetc(c, fptr);
                lexical_error(in_char);
            }

        } else if (in_char=='-'){
            c=fgetc(fptr);
            if(c=='-'){
                do
                    in_char = fgetc(fptr);
                while (in_char!='\n');
            } else{
                ungetc(c, fptr);
                return MINUSOP;
            }
        } else
            lexical_error(in_char);
    }
    return SCANEOF;
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
        token_buffer[i] = '\0';
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
    fprintf(stderr, "Lexical Error located in: %c", in_char);
    if (remove(filename) == 0)
        printf("Deleted successfully");
    else
        printf("Unable to delete the file");
    exit(1);
}
