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
   Matrix B(destination);

   Matrix P = U.lu();
   L.lu(false);

   Matrix Y = L.forward_sub(P*B);
   Matrix H = U.back_sub(Y);

   std::cout << "H:\n" << H << std::endl;

   H.reshape(3, 3);

   std::cout << "H:\n" << H << std::endl;

    return 0;
}