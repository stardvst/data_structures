#pragma once

#include <algorithm>
#include "tbb/tbb.h"

class normalize_size : public tbb::filter {
    const int max_x;
    const int max_y;
public:
    normalize_size(int x, int y)
        : filter(tbb::filter::mode::parallel), max_x(x), max_y(y) {}

    void* operator()(void *img_data) {
        image_data* img = static_cast<image_data*>(img_data);

        // determine the possible multiplers to normalize the size
        double mul_x = (double)max_x / (double)img->image->width();
        double mul_y = (double)max_y / (double)img->image->height();

        // figure out which multiple to use
        double mul = std::min<double>(mul_x, mul_y);

        // if the image is larger than our normalized size
        // then apply the resize transform
        if (mul <= 1.0) {
            int new_x = static_cast<int>(img->image->width() * mul);
            int new_y = static_cast<int>(img->image->height() * mul);
            img->image->resize(new_x, new_y);
        }

        // pass the correctly sized image to the next filter
        return img;
    }
};