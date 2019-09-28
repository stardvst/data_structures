#pragma once

#include "tbb/tbb.h"
#include "dirent.h"
#include "file_enumerator.h"
#include "image_data.h"

#include <string>
using std::string;

class load_images : public tbb::filter {
    file_enumerator file_enum;
    string root;
public:
    load_images(string source_path) 
        : filter(tbb::filter::mode::serial),
        file_enum(source_path), root(source_path) {}

    void* operator()(void*) {
        if (file_enum.good()) {
            return new image_data(root, file_enum.next_file());
        }
        return nullptr;
    }
};