#pragma once

#include "tbb/tbb.h"

#include "load_images.h"
#include "normalize_size.h"
#include "apply_watermark.h"
#include "save_as.h"

#include <string>
using std::string;

class image_processor {
    string source_path;
    string output_path;
public:
    image_processor(string source, string output)
        : source_path(source), output_path(output)
    {  }

    void run() {
        tbb::pipeline pipeline;

        load_images load(source_path);
        normalize_size normalize(1024, 1024);
        apply_watermark watermark("Sample Watermark");
        save_as save(output_path, "bmp");

        pipeline.add_filter(load);
        pipeline.add_filter(normalize);
        pipeline.add_filter(watermark);
        pipeline.add_filter(save);

        pipeline.run(4);
    }
};