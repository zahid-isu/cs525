#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"


void DisplayStack(node* top)
{
    if (top==NULL)
    { printf(" Stack is emtpy.\n"); return; }

    printf(" ---------------------------------------------------------------------------\n");
    printf("| Pos: | StuID: | Firstname: | Lastname: |    Address:    |      Next:       |\n");
    printf(" ----------------------------------------------------------------------------\n");
    PrintNode(top);
    printf(" ----------------------------------------------------------------------------\n");
}

void PrintNode(node* top)
{
    printf("| %3i  |   %3i  |   %s   |   %s    | %15p | %15p |\n", 
    top->position ,top->stuid, top->firstname, top->lastname,top,top->next);
    if (top->next == NULL)
    { return; }
    PrintNode(top->next);
}