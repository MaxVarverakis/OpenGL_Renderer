#pragma once

class VertexBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_size;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    unsigned int size() const { return m_size; }

    void bind() const;
    void unbind() const;
};
