#include <stdio.h>
// #include <stdlib.h>
#include <math.h>
#include "quad.h"


// calculate the area of a quadrilateral using structure and pointers

void compute_perimeter(struct quad *q)
{
    printf("I am in the **compute_perimeter** function.\n");

    double a, b, c, d, s, perim;

    // calculate the length of the 4 sides
    a = sqrt(pow(q->node2.x - q->node1.x, 2) + pow(q->node2.y - q->node1.y, 2));
    b = sqrt(pow(q->node3.x - q->node2.x, 2) + pow(q->node3.y - q->node2.y, 2));
    c = sqrt(pow(q->node4.x - q->node3.x, 2) + pow(q->node4.y - q->node3.y, 2));
    d = sqrt(pow(q->node1.x - q->node4.x, 2) + pow(q->node1.y - q->node4.y, 2));

    perim = (a + b + c + d);
    q->perim = perim;

}
   


 