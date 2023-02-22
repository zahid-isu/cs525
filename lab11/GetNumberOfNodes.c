#include <stdio.h>
#include "node.h"

int GetNumberOfNodes(node* head) 
{
    int count = 0;
    node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}