#pragma once

#include "CImg.h"
#include <string>

using std::string;
using namespace cimg_library;

struct image_data {
    CImg<float> *image;
    string path;
    string root;

    image_data(string root_path, string image_path) 
        : path(image_path), root(root_path) {
        image = new CImg<float>(image_path.c_str());
    }
};