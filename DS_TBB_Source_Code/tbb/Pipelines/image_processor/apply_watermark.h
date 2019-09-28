#pragma once

#include "tbb/tbb.h"
#include <string>
using std::string;

class apply_watermark : public tbb::filter {
    CImg<char> watermark_text;
    CImg<char> watermark_mask;

public:
    apply_watermark(const string& text)
        : filter(tbb::filter::mode::parallel) {
        unsigned char white[] = { 255, 255, 255 };

        // create a waermark image, white background, opaque, 103pt font
        watermark_text.draw_text(0, 0, text.c_str(), white, 0, 1.0, 103U);
        
        // rotate -45 degrees
        watermark_text.rotate(-45);

        // negate the watermark to create the mask image
        watermark_mask = -watermark_text;
    }

    void* operator()(void *img_data) {
        image_data* img = static_cast<image_data*>(img_data);

        // center the watermark on the image
        int center_x = (img->image->width() - watermark_text.width()) / 2;
        int center_y = (img->image->height() - watermark_text.height()) / 2;

        // and apply the watermark
        img->image->draw_image(center_x, center_y, watermark_text, watermark_mask, 1.0, 1.0);

        // pass image to the next filter
        return img;
    }
};