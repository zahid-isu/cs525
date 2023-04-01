#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "node.h"
void GenerateList(node** head, const int num_nodes)
{
    node* temp; srand( time(NULL) );
    for (int i=0; i<num_nodes; i++)
    {
        temp = (node*)malloc(sizeof(node));
        int random_int = rand()%num_nodes;
        char random_char = (char)random_int + 65 ;
        //print the value of the node as char
        temp->value = random_char; temp->position = 0;
        // temp->value = rand()%num_nodes; temp->position = 0;
        printf("%4c",temp->value);
        if (*head == NULL)
        {
            *head = temp;
            (*head)->next = NULL;
        }
        else
        {
            temp->next = *head;
            *head = temp;
        }
    }
    printf("\n");
    node* ptr = *head; int pos = 1;
    while(ptr!=NULL)
    {
        ptr->position = pos;
        pos = pos+1;
        ptr = ptr->next;
    }
}