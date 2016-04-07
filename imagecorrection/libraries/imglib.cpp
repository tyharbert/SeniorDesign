#include "imglib.hpp"

// this runs the complete image transformation process
void transformGusset(const char* source_file, const char* destination_file) {
    printf("\nReading %s\n", source_file);
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

    printf("Writing %s\n\n", destination_file);
    final->write(destination_file);
}

// this converts an image from JPEG to BMP
void JPEG_to_BMP(std::string j_image_path, std::string b_image_path) {
    printf("Converting %s to %s.\n", j_image_path.c_str(), b_image_path.c_str());

    std::string command = "djpeg -BMP " + j_image_path + " > " + b_image_path;
    system(command.c_str());
    sleep(2);

    printf("Conversion complete.\n\n");
}

// this converts an image from BMP to JPEG
void BMP_to_JPEG(std::string b_image_path, std::string j_image_path) {
    printf("Converting %s to %s.\n", j_image_path.c_str(), b_image_path.c_str());

    std::string command = "cjpeg " + b_image_path + " > " + j_image_path;
    system(command.c_str());
    sleep(2);

    printf("Conversion complete.\n\n");
}
