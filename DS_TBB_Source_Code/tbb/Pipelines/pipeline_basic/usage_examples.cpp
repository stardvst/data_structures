#include "tbb/tbb.h"
#include <iostream>

struct token {
    int value;

    token(int val) : value(val)
    { }
};

class input_filter : public tbb::filter {
    int count;

public:
    input_filter()
        : filter(tbb::filter::mode::serial_in_order),
          count(0)
    { }

    void* operator()(void*) {
        if (count++ < 1000) {
            // this token will be passed to the 
            // next filter in the pipeline
            return new token(count);
        }

        // returning null ends the input stream
        return nullptr;
    }
};

class pass_through_filter : public tbb::filter {
public:
    pass_through_filter()
        : filter(tbb::filter::mode::parallel)
    { }

    void* operator()(void* ptr) {
        return ptr;
    }
};

class output_filter : public tbb::filter {
    int count;

public:
    output_filter()
        : filter(tbb::filter::mode::serial_in_order),
        count(0)
    { }

    void* operator()(void* ptr) {
        token* token_ptr = static_cast<token*>(ptr);

        std::cout << token_ptr->value << std::endl;

        delete token_ptr;

        // output filters return null
        return nullptr;
    }
};


void use_pipeline() {
    tbb::pipeline pipeline;

    input_filter input;
    pass_through_filter passthrough;
    output_filter output;

    pipeline.add_filter(input);
    pipeline.add_filter(passthrough);
    pipeline.add_filter(output);

    pipeline.run(4);
}

void use_parallel_pipeline() {
    int count = 0;

    tbb::parallel_pipeline(8,
        tbb::make_filter<void, token*>(
            tbb::filter::mode::serial_in_order,
            [&](tbb::flow_control &fc) {
                if (count++ < 1000) {
                    return new token(count);
                }
                fc.stop();
                return static_cast<token*>(nullptr);
            }) &
        tbb::make_filter<token*, token*>(
            tbb::filter::mode::parallel,
            [](token* tok) {
                return tok;
            }) &
        tbb::make_filter<token*, void>(
            tbb::filter::mode::serial_in_order,
            [&](token* tok) {
                std::cout << tok->value << std::endl;
                delete tok;
            }));
}