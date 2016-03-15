#include "imglib.hpp"

// this runs the complete image transformation process
void transformGusset(const char* source_file, const char* destination_file) {
    printf("Reading %s\n", source_file);
    BMP* bmp = new BMP(source_file);
    
    printf("Finding Corners\n");
    Corners original = bmp->fast();
    Corners destination = original.findDest();

    printf("Finding Transformation Matrix\n");
    Matrix<float> U(original, destination);
    Matrix<float> L(U);
    Matrix<float> B(destination);

    Matrix<float> P = U.lu();
    L.lu(false);

    Matrix<float> Y = L.forward_sub(P*B);
    Matrix<float> H = U.back_sub(Y);

    H.reshape(3, 3);

    printf("Performing Transformation\n");
    BMP* final = new BMP(bmp, H, original, destination);

    printf("Writing %s\n", destination_file);
    final->write(destination_file);
}
