#pragma once

#include <cstdint>
#include "../VertexBuffer/VertexBuffer.hpp"

// forward declare class so it doesn't go into cyclical include with Renderer
class VertexBufferLayout;

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout);
    
    void addInstancedBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout, unsigned int startLocation = 0);
    void addInstancedBuffer(const VertexBuffer& VBO, unsigned int componentCount, unsigned int startLocation = 0);

    void bind() const;
    void unbind() const;
};
