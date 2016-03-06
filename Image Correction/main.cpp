#include "libraries/bmp.hpp"
#include "libraries/matrix.hpp"

typedef Matrix<float> FMatrix;

int main()
{   
   BMP* bmp = new BMP("../images/5.bmp");
   Corners original = bmp->fast();

   Corners destination = original.findDest();

   original.print();
   destination.print();

   FMatrix U(original, destination);
   FMatrix L(U);
   FMatrix B(destination);

   FMatrix P = U.lu();
   L.lu(false);

   FMatrix Y = L.forward_sub(P*B);
   FMatrix H = U.back_sub(Y);

   H.reshape(3, 3);

   BMP* final = new BMP(bmp, H, original, destination);

    return 0;
}