#include "libraries/bmp.hpp"
#include "libraries/matrix.hpp"

typedef Matrix<double> DMatrix;

int main()
{   
   BMP bmp("../images/5.bmp");
   Corners original = bmp.fast();

   Corners destination = original.findDest();

   original.print();
   destination.print();

   DMatrix U(original, destination);
   DMatrix L(U);
   DMatrix B(destination);

   DMatrix P = U.lu();
   L.lu(false);

   DMatrix Y = L.forward_sub(P*B);
   DMatrix H = U.back_sub(Y);

   H.reshape(3, 3);

   std::cout << "H:\n" << H << std::endl;

   DMatrix p(3044.0f, 2542.0f);

   std::cout << "p:\n" << p << "\np':\n" << H*p << std::endl;

    return 0;
}