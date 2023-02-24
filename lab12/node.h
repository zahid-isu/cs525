#ifndef __NODE_H__
#define __NODE_H__

typedef struct node node;
struct node
{
    int position; // node position in stack
    int stuid; //student id #
    char firstname[20]; // student's first name 
    char lastname [20];// student's last name
    node* next;
};

// Functions associated with struct node
void DeleteStack(node** top);
void GetStackSize(node* top, int* stack_size);
void Push(const int stuid, const char *firstname, const char *lastime, node** top);
void Pop(node** top, int* stuid, char *firstname, char *lastname);
int Peek(node* top);
void DisplayStack(node* top);
void PrintNode(node* top);
void ExecuteOption(const int option, node** top);
int QueryOption();
void DisplayOptions();


#endif