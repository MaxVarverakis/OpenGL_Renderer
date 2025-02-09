#pragma once

#include <vector>

struct Surface
{
    std::vector<float> coordinates;
    std::vector<unsigned int> line_indices;

    Surface(float (*f)(float, float), std::size_t PointsPerDim);
};
