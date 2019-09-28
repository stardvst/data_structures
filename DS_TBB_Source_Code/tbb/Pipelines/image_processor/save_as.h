#pragma once

#include "tbb/tbb.h"
#include <string>
#include <sstream>
using std::string;
using std::stringstream;

#include <direct.h>


class save_as : public tbb::filter {
    string path;
    string extension;
public:
    save_as(const string& output_path, const string& file_type) 
        : filter(tbb::filter::mode::serial_out_of_order),
        path(output_path), extension(file_type) {}

    string strip_root_path(string root, string file) {
        return file.substr(root.length() + 1);
    }

    void ensure_paths_exists(string root, string file) {
        size_t pos = file.find_first_of("\\/");
        while (pos != string::npos) {
            string dir = file.substr(0, pos);
            root = root + "/" + dir;
            mkdir(root.c_str());
            file = file.substr(pos + 1);

            pos = file.find_first_of("\\/");
        }
    }

    string strip_extension(string file) {
        size_t pos = file.rfind(".");
        if (pos != string::npos && pos != 0) {
            return file.substr(0, pos);
        }

        return file;
    }

    string build_output_path(image_data *img) {
        string base_filename = strip_extension(strip_root_path(img->root, img->path));

        ensure_paths_exists(path, base_filename);

        stringstream ss;
        ss << path << "/" << base_filename << "_" 
           << img->image->width() << "x" 
           << img->image->height() << "." << extension;

        return ss.str();
    }

    void* operator()(void *img_data) {
        image_data* img = static_cast<image_data*>(img_data);

        // <path>/<image relative path>/image_DimXxDimY.<ext>
        // e.g., /images/input/sub/folder/image.bmp ->
        //       /images/output/sub/folder/image_1024x768.bmp
        string save_as_name = build_output_path(img);

        img->image->save(save_as_name.c_str());

        delete img;

        return nullptr;
    }
};