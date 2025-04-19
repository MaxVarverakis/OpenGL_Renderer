# pragma once

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

class Rectangle
{
private:
    glm::vec2 m_origin;
    float m_width, m_height;
    glm::vec4 m_color;
    
    std::vector<float> m_vertices;
    
    void fillVertices();
public:
    static const unsigned int indices[6];
    static const unsigned int layout_descriptor[3];

    Rectangle(glm::vec2 origin, float width, float height, glm::vec4 color);
    const std::vector<float> vertices() const { return m_vertices; }
    void setColor(glm::vec4 col) { m_color = col; }
};

struct Rectangles
{
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    Rectangles() : m_vertices(), m_indices() {}
    
    Rectangles(std::vector<Rectangle>& rectangles)
    {
        combineVertices(rectangles);
    }

    void combineVertices(std::vector<Rectangle>& rectangles)
    {
        for (Rectangle& rectangle : rectangles)
        {
            addVertices(rectangle);
        }
    }

    void addVertices(Rectangle& rectangle)
    {
        const std::vector<float>& verts { rectangle.vertices() };
        m_vertices.insert(m_vertices.end(), verts.begin(), verts.end());
        
        // also adds to index buffer
        const unsigned int vertex_offset = static_cast<unsigned int>(m_indices.size() * 2 / 3);
        for (unsigned int i = 0; i < 6; ++i)
        {
            m_indices.emplace_back(vertex_offset + Rectangle::indices[i]);
        }
    }

    void udpateColors(const std::vector<glm::vec4>& colors)
    {
        // can only be run after a `Rectangle` is initialized
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const glm::vec4& color { colors[i/32] };
            for (unsigned int j = 0; j < 4; ++j)
            {
                // since 4 vertices per rectangle
                unsigned int start_idx { i + 8 * j + 2 };
                m_vertices[start_idx    ] = color[0];
                m_vertices[start_idx + 1] = color[1];
                m_vertices[start_idx + 2] = color[2];
                m_vertices[start_idx + 3] = color[3];
            }
            
            i += 4 * 8;
        }
    }
    
    void udpateColors(const std::vector<float>& colors)
    {
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const float& color { colors[i/32] };
            for (unsigned int j = 0; j < 4; ++j)
            {
                // since 4 vertices per rectangle
                unsigned int start_idx { i + 8 * j + 2 };
                
                m_vertices[start_idx    ] = color;
                m_vertices[start_idx + 1] = color;
                m_vertices[start_idx + 2] = color;
            }
            
            i += 4 * 8;
        }
    }
};
