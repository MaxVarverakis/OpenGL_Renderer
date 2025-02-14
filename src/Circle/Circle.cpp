#include "Circle.hpp"

const unsigned int Circle::indices[3]
{
    0, 1, 2,
};

const float Circle::vertex_positions[6]
{
    0.0f, 2.0f,
    1.7321f, -1.0f, // sqrt(3) ~ 1.7321
    -1.7321f, -1.0f,
};

const unsigned int Circle::layout_descriptor[5]
{
    2, // vertex coord
    4, // rgba
    2, // circle position
    1, // radius
    1, // inner radius
};

Circle::Circle(glm::vec2 origin, float radius, glm::vec4 color, float inner_radius)
    : m_origin { origin }
    , m_radius { radius }
    , m_color { color }
    , m_inner_radius { inner_radius }
{
    unsigned int sum { 0 };
    for (const unsigned int val : Circle::layout_descriptor) { sum += val; }

    m_vertices.reserve(3 * sum);
    fillVertices();
}

void Circle::fillVertices()
{
    for (unsigned int i = 0; i < 3; ++i)
    {
        m_vertices.push_back(vertex_positions[2*i  ]);
        m_vertices.push_back(vertex_positions[2*i+1]);
        
        // color
        m_vertices.push_back(m_color[0]);
        m_vertices.push_back(m_color[1]);
        m_vertices.push_back(m_color[2]);
        m_vertices.push_back(m_color[3]);

        // circle center/location
        m_vertices.push_back(m_origin[0]);
        m_vertices.push_back(m_origin[1]);

        // radius
        m_vertices.push_back(m_radius);
        
        // inner radius
        m_vertices.push_back(m_inner_radius);
        
        
        // unsigned int start_idx { 9 * i };

        // vertex position for quad
        // m_vertices[start_idx    ] = vertex_positions[i  ];
        // m_vertices[start_idx + 1] = vertex_positions[i+1];
        
        // color
        // m_vertices[start_idx + 2] = m_color[0];
        // m_vertices[start_idx + 3] = m_color[1];
        // m_vertices[start_idx + 4] = m_color[2];
        // m_vertices[start_idx + 5] = m_color[3];

        // circle center/location
        // m_vertices[start_idx + 6] = m_origin[0];
        // m_vertices[start_idx + 7] = m_origin[1];

        // radius
        // m_vertices[start_idx + 8] = m_radius;
    }
}
