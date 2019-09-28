#include "tbb/tbb.h"
#include <string>
#include <sstream>
using std::string;
using std::stringstream;

string int_to_string(int value) {
    stringstream ss;
    ss << value;

    return ss.str();
}

int string_to_int(string value) {
    int i;
    stringstream(value) >> i;
    return i;
}

void pipeline_convert(int *start, int *end, int *output) {
    tbb::parallel_pipeline(8,
        tbb::make_filter<void, int*>(
            tbb::filter::mode::serial_in_order,
            [&](tbb::flow_control &fc) {
                if (start < end) {
                    return start++;
                }
                fc.stop();
                return static_cast<int*>(nullptr);
            }) &
        tbb::make_filter<int*, string>(
            tbb::filter::mode::parallel,
            [](int *ptr) {
                return int_to_string(*ptr);
            }) &
        tbb::make_filter<string, int>(
                tbb::filter::mode::parallel,
                [](const string& value) {
                    return string_to_int(value);
            }) &
        tbb::make_filter<int, void>(
                tbb::filter::mode::serial_in_order,
                [&](int value) {
                *output++ = value;
            }));
}

void parallel_pipeline_example() {

    const int size = 1000;
    int input[size];
    for (int i = 0; i < size; i++) {
        input[i] = i;
    }

    int output[size];

    pipeline_convert(input, input + size, output);
}