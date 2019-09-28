#include "image_processor.h"

int main(int argc, char **argv)
{
    // argv[1] = image source path
    // argv[2] = image output path
    image_processor processor(argv[1], argv[2]);

    processor.run();
}