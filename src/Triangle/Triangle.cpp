#include "Triangle.hpp"

const unsigned int Triangle::indices[3]
{
    0, 1, 2,
};

const unsigned int Triangle::layout_descriptor[2]
{
    2, // vertex coord
    4, // rgba
};

Triangle::Triangle(glm::vec2 v2, glm::vec2 v3, glm::vec4 color)
    : m_v2 { v2 }
    , m_v3 { v3 }
    , m_color { color }
{
    unsigned int m_layout_total { 0 };
    for (const unsigned int val : Triangle::layout_descriptor) { m_layout_total += val; }

    m_vertices.reserve(3 * m_layout_total);
    fillVertices();
}

void Triangle::fillVertices()
{
    for (unsigned int i = 0; i < 3; ++i)
    {
        // bottom left is origin/location
        switch (i)
        {
        case 0:
            m_vertices.push_back(0.0f);
            m_vertices.push_back(0.0f);
            break;
        case 1:
            m_vertices.push_back(m_v2.x);
            m_vertices.push_back(m_v2.y);
            break;
        case 2:
            m_vertices.push_back(m_v3.x);
            m_vertices.push_back(m_v3.y);
            break;
        }
        
        // color
        m_vertices.push_back(m_color[0]);
        m_vertices.push_back(m_color[1]);
        m_vertices.push_back(m_color[2]);
        m_vertices.push_back(m_color[3]);
    }
}
