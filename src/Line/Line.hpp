#pragma once

#include <vector>
#include <glm/glm.hpp>

class Line
{
private:
    glm::vec2 m_first_endpoint;
    glm::vec2 m_second_endpoint;
    glm::vec4 m_color;
    
    std::vector<float> m_vertices;
    
    void fillVertices();
public:
    static const unsigned int layout_descriptor[2];

    Line(glm::vec2 first_endpoint, glm::vec2 second_endpoint, glm::vec4 color);
    const std::vector<float> vertices() const { return m_vertices; }
    void setColor(glm::vec4 col) { m_color = col; }
};

struct Lines
{
    std::vector<float> m_vertices;

    Lines() : m_vertices() {}
    
    Lines(std::vector<Line>& lines)
    {
        combineVertices(lines);
    }

    void combineVertices(std::vector<Line>& lines)
    {
        for (Line& line : lines)
        {
            addVertices(line);
        }
    }

    void addVertices(Line& line)
    {
        const std::vector<float>& verts { line.vertices() };
        m_vertices.insert(m_vertices.end(), verts.begin(), verts.end());
        
        // IBO unnecessary for single lines (only if using linestrip but that would require a different hpp/cpp file)
        // also adds to index buffer
        // const unsigned int vertex_offset = static_cast<unsigned int>(m_indices.size());
        // for (unsigned int i = 0; i < 4; ++i) { m_indices.emplace_back(vertex_offset + i); }
    }

    void udpateColors(const std::vector<glm::vec4>& colors)
    {
        // can only be run after a `Line` is initialized
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const glm::vec4& color { colors[i/12] };
            for (unsigned int j = 0; j < 2; ++j)
            {
                // since 2 vertices per line
                unsigned int start_idx { i + 6 * j + 2 };
                m_vertices[start_idx    ] = color[0];
                m_vertices[start_idx + 1] = color[1];
                m_vertices[start_idx + 2] = color[2];
                m_vertices[start_idx + 3] = color[3];
            }
            
            i += 2 * 6;
        }
    }
    
    void udpateColors(const std::vector<float>& colors)
    {
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const float& color { colors[i/12] };
            for (unsigned int j = 0; j < 2; ++j)
            {
                // since 2 vertices per line
                unsigned int start_idx { i + 6 * j + 2 };
                
                m_vertices[start_idx    ] = color;
                m_vertices[start_idx + 1] = color;
                m_vertices[start_idx + 2] = color;
            }
            
            i += 2 * 6;
        }
    }

    void updateColor(unsigned int idx, float color)
    {
        for (unsigned int j = 0; j < 2; ++j)
        {
            // since 2 vertices per line
            unsigned int start_idx { 12 * idx + 6 * j + 2 };
            
            m_vertices[start_idx    ] = color;
            m_vertices[start_idx + 1] = color;
            m_vertices[start_idx + 2] = color;
        }
    }

    void updateColor(unsigned int idx, float r, float g, float b)
    {
        for (unsigned int j = 0; j < 2; ++j)
        {
            // since 2 vertices per line
            unsigned int start_idx { 12 * idx + 6 * j + 2 };
            
            m_vertices[start_idx    ] = r;
            m_vertices[start_idx + 1] = g;
            m_vertices[start_idx + 2] = b;
        }
    }

    void updateColor(unsigned int idx, float r, float g, float b, float a)
    {
        for (unsigned int j = 0; j < 2; ++j)
        {
            // since 2 vertices per line
            unsigned int start_idx { 12 * idx + 6 * j + 2 };
            
            m_vertices[start_idx    ] = r;
            m_vertices[start_idx + 1] = g;
            m_vertices[start_idx + 2] = b;
            m_vertices[start_idx + 3] = a;
        }
    }
    
    void updateAlpha(unsigned int idx, float alpha)
    {
        for (unsigned int j = 0; j < 2; ++j)
        {
            // since 2 vertices per line
            unsigned int start_idx { 12 * idx + 6 * j + 5 };
            
            m_vertices[start_idx] = alpha;
        }
    }
    
    void updateColor(unsigned int idx, const glm::vec3& color)
    {
        for (unsigned int j = 0; j < 2; ++j)
        {
            // since 2 vertices per line
            unsigned int start_idx { 12 * idx + 6 * j + 2 };
            
            m_vertices[start_idx    ] = color.r;
            m_vertices[start_idx + 1] = color.g;
            m_vertices[start_idx + 2] = color.b;
        }
    }
    
    void updateColor(unsigned int idx, const glm::vec4& color)
    {
        for (unsigned int j = 0; j < 2; ++j)
        {
            // since 2 vertices per line
            unsigned int start_idx { 12 * idx + 6 * j + 2 };
            
            m_vertices[start_idx    ] = color.r;
            m_vertices[start_idx + 1] = color.g;
            m_vertices[start_idx + 2] = color.b;
            m_vertices[start_idx + 3] = color.a;
        }
    }

    void updatePositions(const std::vector<glm::vec2>& positions)
    {
        // can only be run after a `Line` is initialized
        unsigned int i { 0 };
        while (i < m_vertices.size())
        {
            const glm::vec2& position { positions[i/12] };
            for (unsigned int j = 0; j < 2; ++j)
            {
                // since 2 vertices per line
                unsigned int start_idx { i + 6 * j };
                m_vertices[start_idx    ] = position[0];
                m_vertices[start_idx + 1] = position[1];
            }
            
            i += 2 * 6;
        }
    }
    
    void updatePosition(unsigned int idx, const glm::vec2& position)
    {
        // can only be run after a `Line` is initialized
        for (unsigned int j = 0; j < 2; ++j)
        {
            // since 2 vertices per line
            unsigned int start_idx { 12 * idx + 6 * j };
            m_vertices[start_idx    ] = position[0];
            m_vertices[start_idx + 1] = position[1];
        }
    }
};
