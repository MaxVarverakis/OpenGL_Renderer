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

    void bind() const;
    void unbind() const;
};
