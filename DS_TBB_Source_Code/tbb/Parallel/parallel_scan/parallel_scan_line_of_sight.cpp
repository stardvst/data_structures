#define NOMINMAX

#include "tbb/tbb.h"
#include <iostream>
#include <algorithm>
#include <cmath>

struct point
{
    point()
        : altitude(0), angle(0), max_angle(0), visible(false)
    { }

    int altitude;
    double angle;
    double max_angle;
    bool visible;
};

class LineOfSightCalc {
    int scale;
    point* const points;
public:
    LineOfSightCalc(point points_[], int _scale)
        : points(points_), scale(_scale) {}

    LineOfSightCalc(LineOfSightCalc& b, tbb::split)
        : points(b.points), scale(b.scale) {}

    template<typename Tag>
    void operator()(const tbb::blocked_range<int>& r, Tag) {
        for (int i = r.begin(); i < r.end(); ++i) {
            if (i > 0) {
                points[i].angle = atan(scale * (points[i].altitude - points[0].altitude) / i);
                points[i].max_angle = std::max(points[i].angle, points[i - 1].max_angle);
            }

            if (Tag::is_final_scan()) {
                points[i].visible = points[i].angle >= points[i].max_angle;
            }
        }
    }

    void reverse_join(LineOfSightCalc& a) {}

    void assign(LineOfSightCalc& b) {}
};

void print_csv_data(point *points, const int length)
{
    std::cout << "distance,altitude,angle,max_angle,visible" << std::endl;

    for (int distance = 0; distance < length; distance++)
    {
        std::cout
            << distance << ","
            << points[distance].altitude << ","
            << points[distance].angle << ","
            << points[distance].max_angle << ","
            << points[distance].visible
            << std::endl;
    }
}

void parallel_scan_line_of_sight(point *points, const int length)
{         
    tbb::parallel_scan(tbb::blocked_range<int>(0, length), 
                       LineOfSightCalc(points, length));

    print_csv_data(points, length);
}

void parallel_scan_line_of_sight()
{
    int altitudes[] = {
        // flats
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        // small hill
        1, 2, 3, 4, 4, 4, 4, 4, 3,
        // plateau
        2, 2, 2, 2, 2, 2, 2,
        // second hill
        3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
        //plateau
        16, 16, 16, 16, 16, 16 };

    const int length = sizeof(altitudes) / sizeof(altitudes[0]);

    point points[length];

    for (int i = 0; i < length; i++)
    {
        points[i].altitude = altitudes[i];
        points[i].angle = 0;
        points[i].max_angle = 0;
    }

    parallel_scan_line_of_sight(points, length);
}

