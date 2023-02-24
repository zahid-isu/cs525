#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "node.h"


int QueryOption()
{
    int option;
    printf(" ENTER CHOICE : ");
    scanf("%i", &option);
    return option;
}

void ExecuteOption(const int option, node** top)
{
    int value;
    int stuid; //student id #
    char firstname[20]; // student's first name 
    char lastname [20];// student's last name

    switch(option)
    {
    case 0: // Display available options
        DisplayOptions();
        break;
    case 1: // Enter a new value then push new node to stack
        printf(" Enter Stuid : ");
        scanf("%i", &stuid);
        printf(" Enter Firstname : \n");
        scanf("%s", firstname);
        printf(" Enter Lastname : \n");
        scanf("%s", lastname);
        Push(stuid, firstname, lastname, top);
        break;
    case 2: // Pop top value off of stack
        if (*top!=NULL)
        {
            Pop(top, &stuid, firstname, lastname);
            printf(" Pop StuID = %i\n", stuid);
            printf(" Pop Firstname = %s\n", firstname);
            printf(" Pop Lastname = %s\n", lastname);
        }
        else
        { printf(" Stack is empty.\n"); }
        break;
    case 3: // Peek at top value on stack
        if((*top)!=NULL)
        {
            value = Peek(*top);
            printf(" Top StuID is %i\n",value);

        }
        else
        { printf(" Stack is empty.\n"); }
        break;

    case 4: // Display the entire stack
        DisplayStack(*top);
        break;
    case 5: // Print stack size
        GetStackSize(*top,&value);
        printf(" Stack size is %i\n",value);
        break;
    case 6: // Do nothing here, but this causes code to end
        break;
    default:
        printf("Error: incorrect option. Try again.\n");
        break;
    }
}