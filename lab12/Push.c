#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "node.h"


void Push(const int stuid, const char *firstname, const char *lastname, node** top)
{
    if (*top == NULL)
    {
        *top =(node*)malloc(sizeof(struct node));
        (*top)->next = NULL;
        (*top)->stuid = stuid;
        strcpy((*top)->firstname, firstname); 
        strcpy((*top)->lastname, lastname);
        (*top)->position = 1;
    }

    else
    {
        node* temp;
        temp =(node*)malloc(sizeof(struct node));
        temp->next = *top;
        temp->stuid = stuid;
        strcpy (temp->firstname, firstname); 
        strcpy (temp->lastname, lastname);
        temp->position = 1;
        *top = temp;
        node* ptr = (*top)->next;
        while (ptr!=NULL)
        {
            ptr->position = ptr->position+1;
            ptr = ptr->next;
        }
    }
}