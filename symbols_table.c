//
// Created by diegomv on 6/3/22.
//

#include "symbols_table.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

// A simple node to use a linked symbol list as a symbol table, not another info needed
struct node {
    string name;
    struct node *next;
};

struct node *headNode = NULL;
struct node *actualNode = NULL;
int listLen = -1;

// Function to check if the given symbol exists into the symbol table
// The function returns 1 if the symbol already exits or 0 if not
int lookup(string sym) {
    struct node *tmp = headNode;

    while (tmp != NULL) {
        // strcmp(x, y) = 0 means both strings are the same
        if (strcmp(tmp->name, sym) == 0) {
            return 1;
        }
        tmp = tmp->next;
    }
//    printf("%s", #include "symbols_table.c"s);
    return 0;
}

// Function to insert a new symbol into the table giving the symbol to insert, should execute after lookup
void enter(string sym) {
    struct node *newSymNode = malloc(sizeof(struct node));
    strcpy(newSymNode->name, sym);
    newSymNode->next = NULL;

    // This is the first insertion where list if full empty
    if (headNode == NULL) {
        headNode = newSymNode;
        actualNode = newSymNode;
    } else {
        // When the list is not empty just update the last pointer to point to the new node and update the actual node
        actualNode->next = newSymNode;
        actualNode = newSymNode;
    }
    listLen++;
}

void printAll() {
    struct node *tmp = headNode;
    while (tmp != NULL) {
        printf("Name: %s \n", tmp->name);
        tmp = (struct node *) tmp->next;
    }
}

char *symbolByIndex(int index) {
    struct node *tmp = headNode;
    int tmpIndex = 0;
    while (tmp != NULL) {
        if (tmpIndex == index) {
            return tmp->name;
        }
        tmp = tmp->next;
        tmpIndex++;
    }
    return NULL;
}

int len() {
    return listLen + 1;
}

//int main() {
//    string var = "hola";
//    enter(var);
//    enter(strcat(var, "1"));
//    enter(strcat(var, "2"));
//    enter(strcat(var, "3"));
//
//    if (lookup(var) == 0) {
//        enter(var);
//    }
//
////    printf("\n");
////    string var1 = "hol";
////    printf("Exists: %d \n", lookup(var1));
////    printf("Len: %d \n", len());
////    printf("By index: %s", symbolByIndex(3));
//
////    printAll();
////    lookup(var);
//
////    printf("section .data");
////    printf("\n");
////    for (int i = 0; i < len(); ++i) {
////        printf("%s: dd 0 \n", symbolByIndex(i));
////    }
//
//string file = "out.txt";
////declare data section
//    FILE *fileOutput;
//    fileOutput = fopen (file, "w");
//    if(fileOutput==NULL){
//        printf("Error opening file. Start in translator.c");
//        exit(1);
//    }
//
//    // Creating data section
//    fputs("section .data \n", fileOutput);
//
//    // Writing each variable to data section an initializing each with 0
//    for (int i = 0; i < len(); ++i) {
//        fputs(symbolByIndex(i), fileOutput);
//        fputs(": dd 0 \n", fileOutput);
//    }
//    fclose(fileOutput);
//    return 0;
//}