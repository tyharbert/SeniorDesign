#include "libraries/bmp.hpp"
#include "libraries/matrix.hpp"

int main()
{   
   BMP bmp("../images/5.bmp");
   Corners original = bmp.fast();

   Corners destination = original.findDest();
   
   original.print();
   destination.print();

   Matrix A(original, destination);
   Matrix U(A);
  
   A.print();
   U.print();
  
   //U.gausianOP();
   //U.print();
    
    return 0;
}