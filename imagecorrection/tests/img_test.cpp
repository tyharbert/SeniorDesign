#include "imglib.hpp"

int main()
{   
    transformGusset("../../images/test_3.bmp", "../../images/test_3_out.bmp");

	JPEG_to_BMP("../../images/foo.jpeg", "../../images/foo.bmp");
	BMP_to_JPEG("../../images/foo.bmp", "../../images/foo.jpeg");

    return 0;
}