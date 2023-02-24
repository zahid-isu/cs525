#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "node.h"

void Pop(node** top, int* stuid, char *firstname, char *lastname)
{
    node* temp = *top;

    if (temp==NULL)
    { return; }
    else
    { temp = temp->next; }
    *stuid = (*top)->stuid;
    strcpy(firstname, (*top)->firstname);
    strcpy(lastname, (*top)->lastname);
    free(*top);
    *top = temp;

    node* ptr = *top;
    while (ptr!=NULL)
    {
    ptr->position = ptr->position -1;
    ptr = ptr->next;
    }
}