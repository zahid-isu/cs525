#include <stdio.h>
#include <stdlib.h>
#include "node.h"
void SearchList(const node* head, char key)
{ // Search list for key
    if (key==(char)head->value)
    {
        printf(" Key found at Position: %i\n", head->position);
    }
    if (head->next==NULL)
    {
        printf("\n"); return;
    }
    SearchList(head->next,key);
}