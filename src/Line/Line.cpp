#include "Line.hpp"

const unsigned int Line::layout_descriptor[2]
{
    2, // vertex coord
    4, // rgba
};

Line::Line(glm::vec2 first_endpoint, glm::vec2 second_endpoint, glm::vec4 color)
    : m_first_endpoint { first_endpoint }
    , m_second_endpoint { second_endpoint }
    , m_color { color }
{
    unsigned int m_layout_total { 0 };
    for (const unsigned int val : Line::layout_descriptor) { m_layout_total += val; }

    m_vertices.reserve(2 * m_layout_total);
    fillVertices();
}

void Line::fillVertices()
{
    // 1st endpoint
    m_vertices.push_back(m_first_endpoint[0]);
    m_vertices.push_back(m_first_endpoint[1]);
    
    // color
    m_vertices.push_back(m_color[0]);
    m_vertices.push_back(m_color[1]);
    m_vertices.push_back(m_color[2]);
    m_vertices.push_back(m_color[3]);
    
    // 2nd endpoint
    m_vertices.push_back(m_second_endpoint[0]);
    m_vertices.push_back(m_second_endpoint[1]);
    
    // color
    m_vertices.push_back(m_color[0]);
    m_vertices.push_back(m_color[1]);
    m_vertices.push_back(m_color[2]);
    m_vertices.push_back(m_color[3]);
}
