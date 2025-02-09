#include "VertexArray.hpp"
#include "../VertexBufferLayout/VertexBufferLayout.hpp"
#include "../Renderer/Renderer.hpp"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::addBuffer(const VertexBuffer& VBO, const VertexBufferLayout& layout)
{
    bind();
    VBO.bind();

    const std::vector<VertexBufferElement>& elements { layout.getElements() };
    uintptr_t offset { 0 };

    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        const VertexBufferElement& element { elements[i] };

        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, static_cast<int>(element.count), element.type, element.normalized, static_cast<int>(layout.getStride()), (const void*) offset));

        offset += element.count * VertexBufferElement::getSizeOfType(element.type);

    }
}

void VertexArray::bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::unbind() const
{
    GLCall(glBindVertexArray(0));
}
