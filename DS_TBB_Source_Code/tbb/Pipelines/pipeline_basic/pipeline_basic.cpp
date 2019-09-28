#include "tbb/tbb.h"
#include "siminput.h"
#include "output_filter.h"

void pipeline_basic_example() {
    tbb::pipeline pipeline;

    simulated_data_input_filter input(1, 10000);
    output_filter output;

    pipeline.add_filter(input);
    pipeline.add_filter(output);
    pipeline.run(8);
}