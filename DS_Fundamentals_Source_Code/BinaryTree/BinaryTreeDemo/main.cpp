#include "tree.h"
#include "treetests.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

void main()
{
    treetests::run_tests();

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
}