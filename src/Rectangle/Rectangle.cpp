#include "Rectangle.hpp"

const unsigned int Rectangle::indices[6]
{
    0, 1, 2,
    2, 3, 0,
};

const unsigned int Rectangle::layout_descriptor[3]
{
    2, // vertex coord
    4, // rgba
    2, // center position
};

Rectangle::Rectangle(glm::vec2 origin, float width, float height, glm::vec4 color)
    : m_origin { origin }
    , m_width { width }
    , m_height { height }
    , m_color { color }
{
    unsigned int m_layout_total { 0 };
    for (const unsigned int val : Rectangle::layout_descriptor) { m_layout_total += val; }

    m_vertices.reserve(4 * m_layout_total);
    fillVertices();
}

void Rectangle::fillVertices()
{
    for (unsigned int i = 0; i < 4; ++i)
    {
        // bottom left is origin/location
        switch (i)
        {
        case 0:
            m_vertices.push_back(0.0f);
            m_vertices.push_back(m_height);
            break;
        case 1:
            m_vertices.push_back(m_width);
            m_vertices.push_back(m_height);
            break;
        case 2:
            m_vertices.push_back(m_width);
            m_vertices.push_back(0.0f);
            break;
        case 3:
            m_vertices.push_back(0.0f);
            m_vertices.push_back(0.0f);
            break;
        }
        
        // color
        m_vertices.push_back(m_color[0]);
        m_vertices.push_back(m_color[1]);
        m_vertices.push_back(m_color[2]);
        m_vertices.push_back(m_color[3]);

        // rectangle center/location
        m_vertices.push_back(m_origin[0]);
        m_vertices.push_back(m_origin[1]);
    }
}
