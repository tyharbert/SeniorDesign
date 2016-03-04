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

   U.lu();

   std::cout << "U:\n";
   U.print();

    return 0;
}