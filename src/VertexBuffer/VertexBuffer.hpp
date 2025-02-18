#pragma once

#include <GL/glew.h>

class VertexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_size;

public:
    VertexBuffer(const void* data, unsigned int size, const unsigned int draw_type = GL_STATIC_DRAW);
    ~VertexBuffer();

    unsigned int size() const { return m_size; }

    void bind() const;
    void unbind() const;
    void rebuffer(const void* data, const unsigned int size, const unsigned int draw_type = GL_STATIC_DRAW);
    void updateBuffer(const void* data);
};
