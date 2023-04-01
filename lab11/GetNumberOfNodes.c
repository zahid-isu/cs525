#include <stdio.h>
#include "node.h"
int GetNumberOfNodes(node* head) // Get number of nodes from user
{
    int num_nodes = 0;
    printf("Enter the number of nodes you want to generate: ");
    scanf("%d",&num_nodes);
    return num_nodes;
}