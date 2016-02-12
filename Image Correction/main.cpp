#include "libraries/bmp.hpp"

int main()
{   
    BMP bmp("../images/5.bmp");
    bmp.fast();
    bmp.write("../images/6.bmp");
    
    return 0;
}