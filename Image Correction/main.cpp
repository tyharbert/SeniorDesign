#include "libraries/imglib.hpp"

int main()
{   
    FILE* f = openFile("../images/1.bmp");
    readBMP(f);

    return 0;
}