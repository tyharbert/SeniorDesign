#include "libraries/bmp.hpp"
#include "libraries/matrix.hpp"

int main()
{   
   BMP bmp("../images/5.bmp");
   Corners original = bmp.fast();

   Corners destination = original.findDest();

   original.print();
   destination.print();

   Matrix U(original, destination);
   Matrix L(U);

   U.lu();
   L.lu(false);

   std::cout << "U:\n";
   U.print();
   std::cout << "L:\n";
   L.print();

    return 0;
}