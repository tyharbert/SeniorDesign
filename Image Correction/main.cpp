#include "libraries/bmp.hpp"

int main()
{   
    BMP bmp("../images/2.bmp");
    bmp.fast();
    bmp.write("../images/4.bmp");
    return 0;
}