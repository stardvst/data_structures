#pragma once

class Image {
    unsigned char* bytes;
    size_t length;
public:
    Image() {
        length = 120 * 480 * 4; // 4 bytes per pixel
        bytes = new unsigned char[length];
    }

    Image(Image&& other) 
        : length(other.length), bytes(other.bytes)
    {
        other.bytes = nullptr;
    }

    Image(const Image& other)
        : length(other.length)
    {
        bytes = new unsigned char[length];
    }

    ~Image() {
        if (bytes != nullptr) {
            delete[] bytes;
        }
    }

    unsigned char* get_bytes() {
        return bytes;
    }

    size_t size() {
        return length;
    }
};