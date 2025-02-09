#include "Surface.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

Surface::Surface(float (*f)(float, float), std::size_t PointsPerDim)
{
    // x,y,z array is flattened
    const std::size_t num_points { PointsPerDim * PointsPerDim * 7 };
    
    // PointsPerDim - 1 segments of length L ==> L = total distance / (PointsPerDim - 1)
    // note that screen coords range from [-1, 1]
    const float step { 2.0f / (PointsPerDim - 1) };

    coordinates.resize(num_points);
    line_indices.resize(2 * 2 * (PointsPerDim * PointsPerDim - 1));

    for (std::size_t row = 0; row < PointsPerDim; ++row)
    {
        // x += step;
        const float x = -1.0f + static_cast<float>(row) * step;

        for (std::size_t col = 0; col < PointsPerDim; ++col)
        {
            // y += step;
            const float y = -1.0f + static_cast<float>(col) * step;
            // z = 0.0f

            std::size_t vertexStartIdx = (row * PointsPerDim + col) * 7;
            coordinates[vertexStartIdx    ] = x;
            coordinates[vertexStartIdx + 1] = y;
            coordinates[vertexStartIdx + 2] = f(x, y);

            float distance { sqrt(x*x + y*y) };
            float maxDistance { static_cast<float>(sqrt(2.0)) };

            // Add color based on distance to origin
            coordinates[vertexStartIdx + 3] = std::max(0.0f, 1.0f - distance/maxDistance * 2.0f); // R component
            coordinates[vertexStartIdx + 4] = std::max(0.0f, distance/maxDistance * 2.0f - 1.0f); // G component
            coordinates[vertexStartIdx + 5] = (1.0f - fabs(0.5f - distance/maxDistance) * 2.0f);  // B component
            coordinates[vertexStartIdx + 6] = 1.0f;                                               // Alpha component
        }
    }

    // vertical lines
    std::size_t lineEndPointIdx { 0 };
    for (std::size_t row = 0; row < PointsPerDim; ++row)
    {
        for (std::size_t col = 0; col < PointsPerDim - 1; ++col)
        {
            // ++ after lineEndPointIdx so that line_indices is correctly indexed
            line_indices[lineEndPointIdx++] = static_cast<unsigned int>(row * PointsPerDim + col);
            line_indices[lineEndPointIdx++] = static_cast<unsigned int>(row * PointsPerDim + col + 1);
        }
    }

    // horizontal lines
    for (std::size_t row = 0; row < PointsPerDim - 1; ++row)
    {
        for (std::size_t col = 0; col < PointsPerDim; ++col)
        {
            // ++ after lineEndPointIdx so that line_indices is correctly indexed
            line_indices[lineEndPointIdx++] = static_cast<unsigned int>(row * PointsPerDim + col);
            line_indices[lineEndPointIdx++] = static_cast<unsigned int>((row + 1) * PointsPerDim + col);
        }
    }

}
