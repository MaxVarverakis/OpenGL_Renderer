# pragma once

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

class Triangle
{
private:
    glm::vec2 m_v2, m_v3;
    glm::vec4 m_color;
    
    std::vector<float> m_vertices;
    
    void fillVertices();
public:
    static const unsigned int indices[3];
    static const unsigned int layout_descriptor[2];

    Triangle(glm::vec2 v2, glm::vec2 v3, glm::vec4 color);
    const std::vector<float> vertices() const { return m_vertices; }
    void setColor(glm::vec4 col) { m_color = col; }
};

struct Triangles
{
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

    Triangles() : m_vertices(), m_indices() {}
    
    Triangles(std::vector<Triangle>& triangles)
    {
        combineVertices(triangles);
    }

    void combineVertices(std::vector<Triangle>& triangles)
    {
        for (Triangle& triangle : triangles)
        {
            addVertices(triangle);
        }
    }

    void addVertices(Triangle& triangle)
    {
        const std::vector<float>& verts { triangle.vertices() };
        m_vertices.insert(m_vertices.end(), verts.begin(), verts.end());
        
        // also adds to index buffer
        const unsigned int vertex_offset = static_cast<unsigned int>(m_indices.size());
        for (unsigned int i = 0; i < 3; ++i)
        {
            m_indices.emplace_back(vertex_offset + Triangle::indices[i]);
        }
    }

    void udpateColors(const std::vector<glm::vec4>& colors)
    {
        // can only be run after a `Triangle` is initialized
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const glm::vec4& color { colors[i/18] };
            for (unsigned int j = 0; j < 3; ++j)
            {
                // since 3 vertices per triangle
                unsigned int start_idx { i + 6 * j + 2 };
                m_vertices[start_idx    ] = color[0];
                m_vertices[start_idx + 1] = color[1];
                m_vertices[start_idx + 2] = color[2];
                m_vertices[start_idx + 3] = color[3];
            }
            
            i += 3 * 6;
        }
    }
    
    void udpateColors(const std::vector<float>& colors)
    {
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const float& color { colors[i/18] };
            for (unsigned int j = 0; j < 3; ++j)
            {
                // since 3 vertices per triangle
                unsigned int start_idx { i + 6 * j + 2 };
                
                m_vertices[start_idx    ] = color;
                m_vertices[start_idx + 1] = color;
                m_vertices[start_idx + 2] = color;
            }
            
            i += 3 * 6;
        }
    }

    void updateAlpha(unsigned int idx, float alpha)
    {
        for (unsigned int j = 0; j < 3; ++j)
        {
            // since 3 vertices per triangle
            unsigned int start_idx { 18 * idx + 6 * j + 5 };
            
            m_vertices[start_idx] = alpha;
        }
    }
    
    void updateColor(unsigned int idx, const glm::vec3& color)
    {
        for (unsigned int j = 0; j < 3; ++j)
        {
            // since 3 vertices per triangle
            unsigned int start_idx { 18 * idx + 6 * j + 2 };
            
            m_vertices[start_idx    ] = color.r;
            m_vertices[start_idx + 1] = color.g;
            m_vertices[start_idx + 2] = color.b;
        }
    }
    
    void updateColor(unsigned int idx, const glm::vec4& color)
    {
        for (unsigned int j = 0; j < 3; ++j)
        {
            // since 3 vertices per triangle
            unsigned int start_idx { 18 * idx + 6 * j + 2 };
            
            m_vertices[start_idx    ] = color.r;
            m_vertices[start_idx + 1] = color.g;
            m_vertices[start_idx + 2] = color.b;
            m_vertices[start_idx + 3] = color.a;
        }
    }

    void updatePositions(const std::vector<glm::vec2>& positions)
    {
        // can only be run after a `Triangle` is initialized
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const glm::vec2& position { positions[i/18] };
            for (unsigned int j = 0; j < 3; ++j)
            {
                // since 3 vertices per triangle
                unsigned int start_idx { i + 6 * j + 3 };
                m_vertices[start_idx    ] = position[0];
                m_vertices[start_idx + 1] = position[1];
            }
            
            i += 3 * 6;
        }
    }
    
    void updatePosition(unsigned int idx, const glm::vec2& position)
    {
        // can only be run after a `Triangle` is initialized
        for (unsigned int j = 0; j < 3; ++j)
        {
            // since 3 vertices per triangle
            unsigned int start_idx { 18 * idx + 6 * j + 3 };
            m_vertices[start_idx    ] = position[0];
            m_vertices[start_idx + 1] = position[1];
        }
    }
};
