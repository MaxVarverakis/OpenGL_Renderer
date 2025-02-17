#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_count;

public:
    IndexBuffer(const void* data, unsigned int count, const unsigned int draw_type = GL_STATIC_DRAW);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    inline unsigned int getCount() const { return m_count; }
};
