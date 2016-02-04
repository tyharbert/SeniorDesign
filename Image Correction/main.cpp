#include "libraries/bmp.hpp"

int main()
{   
    BMP bmp("../images/2.bmp");
    bmp.invert(); // inverts
    bmp.write("../images/3.bmp");
    
    return 0;
}