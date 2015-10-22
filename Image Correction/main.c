#include "Libraries/my_lib.h"

/*
This function is used to realixe the h vector below from the 8 equations shown:

(x0 y0 1  0   0  0  -x0*x'0 -y0*x'0)   (x'0)   (h11)
(x1 y1 1  0   0  0  -x1*x'1 -y1*x'1)   (x'1)   (h12)
(x2 y2 1  0   0  0  -x2*x'2 -y2*x'2)   (x'2)   (h13)
(x3 y3 1  0   0  0  -x3*x'3 -y3*x'3) \ (x'3) = (h21)
(0  0  0  x0  y0 1  -x0*y'0 -y0*y'0)   (y'0)   (h22)
(0  0  0  x1  y1 1  -x1*y'1 -y1*y'1)   (y'1)   (h23)
(0  0  0  x2  y2 1  -x2*y'2 -y2*y'2)   (y'2)   (h31)
(0  0  0  x3  y3 1  -x3*y'3 -y3*y'3)   (y'3)   (h32)

*/

int main()
{   
    int rows = 4;
    int cols = 4;
    
    double** m;
    zeros(&m,rows,cols);
    determinate(m,rows,cols);
    dalloc(&m,rows);
    
    if(m==NULL)
        printf("dalloc success\n");

    return 0;
}
