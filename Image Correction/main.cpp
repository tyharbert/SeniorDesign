#include "libraries/bmp.hpp"
#include "libraries/matrix.hpp"

int main()
{   
//    BMP bmp("../images/5.bmp");
//    bmp.fast();
//    bmp.write("../images/6.bmp");
    
    Matrix m1(3);
    Matrix m2(m1);
    
    m1.print();
    m2.print();
    
    m2.gausianOP();
    m2.print();
    
    return 0;
}