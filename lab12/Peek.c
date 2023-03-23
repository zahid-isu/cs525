#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Peek(node* top)
{
    if (top==NULL)
    { return 0; }
    else
    {

        return top->stuid ;
    }
}
