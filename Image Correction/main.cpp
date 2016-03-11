#include "libraries/bmp.hpp"
#include "libraries/matrix.hpp"

int main()
{   
   BMP* bmp = new BMP("../images/1.bmp");
   Corners original = bmp->fast();

   Corners destination = original.findDest();

   original.print();
   destination.print();

   Matrix<float> U(original, destination);
   Matrix<float> L(U);
   Matrix<float> B(destination);

   Matrix<float> P = U.lu();
   L.lu(false);

   Matrix<float> Y = L.forward_sub(P*B);
   Matrix<float> H = U.back_sub(Y);

   H.reshape(3, 3);

   BMP* final = new BMP(bmp, H, original, destination);
   final->write("../images/2.bmp");

    return 0;
}