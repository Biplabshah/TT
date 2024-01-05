#include <stdio.h>
#include "lodepng.h"
#include <stdlib.h>

int main() {
    unsigned char *image;
    unsigned int width, height;
    unsigned char red, green, blue, alpha;

    if (lodepng_decode32_file(&image, &width, &height, "xyz.png") != 0) {
        fprintf(stderr, "Error decoding PNG file\n");
        return 1;
    }

    printf("%d %d\n", width, height);

    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            red = image[4 * width * i + 4 * j + 0];
            green = image[4 * width * i + 4 * j + 1];
            blue = 255; // Corrected: Set blue to 255
            alpha = image[4 * width * i + 4 * j + 3];
            
            image[4 * width * i + 4 * j + 2] = blue; // Corrected: Fixed the assignment

            printf("[%d %d %d %d]\n", red, green, blue, alpha);
        }
    }

    unsigned char *output;
    size_t outputsize;
    unsigned error; // Corrected: Declare error variable

    error = lodepng_encode32(&output, &outputsize, image, width, height);
    if (error) {
        lodepng_save_file(output, outputsize, "output.png");
    }

    free(image);
    free(output);

    return 0;
}

