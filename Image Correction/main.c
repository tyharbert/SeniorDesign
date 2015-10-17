#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 256


/*
This function is used to realixe the h vector below from the 8 equations shown:

(x0 y0 1  0   0  0  -x0*x'0 -y0*x'0)   (h11)   (x'0)
(x1 y1 1  0   0  0  -x1*x'1 -y1*x'1)   (h12)   (x'1)
(x2 y2 1  0   0  0  -x2*x'2 -y2*x'2)   (h13)   (x'2)
(x3 y3 1  0   0  0  -x3*x'3 -y3*x'3) * (h21) = (x'3)
(0  0  0  x0  y0 1  -x0*y'0 -y0*y'0)   (h22)   (y'0)
(0  0  0  x1  y1 1  -x1*y'1 -y1*y'1)   (h23)   (y'1)
(0  0  0  x2  y2 1  -x2*y'2 -y2*y'2)   (h31)   (y'2)
(0  0  0  x3  y3 1  -x3*y'3 -y3*y'3)   (h32)   (y'3)

*/
//double* realize_H(double* x, double* y, double* x_p, double* y_p){
//    
//}

int main()
{
    // variable declarations and initializations
    FILE* in_f;
    unsigned char buffer[BUFFER_SIZE];
    int bytes_read = 0;

    // open image file
    // TODO: when using CMAKE change this to read from a relative path...
    in_f = fopen("/Users/harbertt11/_The University Of Akron/General/Senior Design Trunk/Image Correction/Images/QR2.jpg","r");
    if (!in_f){
        printf("Error opening file...");
        return 1;
    }

    // read a buffer of binary data of max size BUFFER_SIZE
    while ((bytes_read = fread(buffer, sizeof(unsigned char), BUFFER_SIZE, in_f)) > 0){
        // print buffer as hex
        for (int i = 0; i < bytes_read; i++){
            printf("%x ", buffer[i]);
        }
        printf("\b\n");
    }

    return 0;
}
