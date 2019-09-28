#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "complexity_funcs.h"

typedef double (*complexityTest)(unsigned int);
void run_print_iters(complexityTest test, char *complexity, unsigned int iterations);

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Usage:    demo1 <complexity> <iterations>\n");
        printf("Example:  demo1 On 1000\n");
        printf("Complexities:\n");
        printf("    linear\n");
        printf("    sq\n");
        printf("    cube\n");
        printf("    logn\n");
        printf("    nlogn\n");
        return -1;
    }

    unsigned int iterations = atol(argv[2]);

    if(0 == strcmp("linear", argv[1]))
    {
        run_print_iters(O_n, argv[1], iterations);
        return 0;
    }

    if(0 == strcmp("sq", argv[1]))
    {
        run_print_iters(O_n_2, argv[1], iterations);
        return 0;
    }

    if(0 == strcmp("cube", argv[1]))
    {
        run_print_iters(O_n_3, argv[1], iterations);
        return 0;
    }    

    if(0 == strcmp("logn", argv[1]))
    {
        run_print_iters(O_log_n, argv[1], iterations);
        return 0;
    }

    if(0 == strcmp("nlogn", argv[1]))
    {
        run_print_iters(O_n_log_n, argv[1], iterations);
        return 0;
    }    

    printf("UNKNOWN COMPLEXITY\n");

    return 1;
}

void run_print_iters(complexityTest test, char *complexity, unsigned int iterations)
{
    double iters = test(iterations);
    printf("%s,%g\n", complexity, iters);
}

