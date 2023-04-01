#include <stdio.h>
#include "node.h"
int GetKey()
{
    char key;
    printf("\n Enter key to search: ");
    scanf(" %c",&key);
    //convert char to int
    int k = (int)key;
    return k;
}