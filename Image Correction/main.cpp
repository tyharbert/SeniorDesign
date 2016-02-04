#include "libraries/bmp.hpp"

int main()
{   
    BMP bmp("../images/2.bmp");
    bmp.w2b(); // makes everything not WHITE to BLACK for testing
    bmp.write("../images/3.bmp");
    
    return 0;
}