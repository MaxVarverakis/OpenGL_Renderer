#include "VertexBuffer.hpp"
#include "../Renderer/Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, const unsigned int draw_type)
    : m_size { size }
{
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, draw_type));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::rebuffer(const void* data, const unsigned int size, const unsigned int draw_type)
{
    m_size = size;

    bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, draw_type));
    unbind();
}

void VertexBuffer::updateBuffer(const void* data)
{
    bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, m_size, data));
    unbind();
}
