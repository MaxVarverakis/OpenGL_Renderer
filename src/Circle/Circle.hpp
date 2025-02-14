#pragma once

#include <vector>
#include <glm/glm.hpp>

class Circle
{
private:
    glm::vec2 m_origin;
    float m_radius;
    glm::vec4 m_color;
    float m_inner_radius; // NOTE: inner radius is a percent of total radius, so 0.5 corresponds to inner radius = 0.5 * radius for annulus
    
    std::vector<float> m_vertices;

    // vertex layout (3 per triangle, which is all that's needed for a circle):
    // quad vertex x, quad vertex y, r, g, b, a, center x, center y, radius
    //                               ^  ^  ^  ^  ^         ^         ^
    // these are the same for all 3 vertices that make up the quad

    static const float vertex_positions[6];

    void fillVertices();
public:
    static const unsigned int indices[3];
    static const unsigned int layout_descriptor[5];
    Circle(glm::vec2 origin, float radius, glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), float inner_radius = 0.0f);

    const std::vector<float> vertices() const { return m_vertices; }
};

struct Circles
{
    // std::vector<Circle>& m_circles;
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    Circles() : m_vertices(), m_indices() {}
    
    Circles(std::vector<Circle>& circles) // : m_circles(circles)
    {
        combineVertices(circles);
    }

    void combineVertices(std::vector<Circle>& circles)
    {
        for (Circle& circle : circles)
        {
            addVertices(circle);
        }
    }

    void addVertices(Circle& circle)
    {
        const std::vector<float>& verts { circle.vertices() };
        m_vertices.insert(m_vertices.end(), verts.begin(), verts.end());
        
        // also adds to index buffer
        const unsigned int vertex_offset = static_cast<unsigned int>(m_indices.size());
        for (unsigned int i = 0; i < 3; ++i) { m_indices.emplace_back(vertex_offset + i); }
    }

};
