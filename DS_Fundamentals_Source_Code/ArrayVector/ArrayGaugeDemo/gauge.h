#include "gauge_reading.h"

class gauge
{
public:
    virtual gauge_reading* current() = 0;
};