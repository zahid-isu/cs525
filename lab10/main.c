#include <stdio.h>
#include "quad.h"

int main()
{
    printf("I am in the **main** function.\n");
    
    // declare a structure variable for the quadrilateral area and perimeter
    quad q, area, perim;
    // input the coordinates of the 4 nodes
    q.node1.x = 1;
    q.node1.y = 0;
    q.node2.x = 1;  
    q.node2.y = 2;
    q.node3.x = -1;
    q.node3.y = 3;
    q.node4.x = -1;
    q.node4.y = 0;
    
    // call the function to compute the area of the quadrilateral
    void compute_area(quad* q);
    compute_area(&q);

    // call the function to compute the perimeter of the quadrilateral
    void compute_perimeter(quad* q);
    compute_perimeter(&q);

    // print the coordinates of the 4 nodes
    printf("\n The coordinates of the 4 nodes are:");
    printf("\n node #1: ( %12.5e, %12.5e )",q.node1.x,q.node1.y);
    printf("\n node #2: ( %12.5e, %12.5e )",q.node2.x,q.node2.y);
    printf("\n node #3: ( %12.5e, %12.5e )",q.node3.x,q.node3.y);
    printf("\n node #4: ( %12.5e, %12.5e )",q.node4.x,q.node4.y);

    printf("\n\n The area of quadrilateral = %12.5e\n", q.area);
    printf("\n The perimeter of quadrilateral = %12.5e\n\n", q.perim);


}