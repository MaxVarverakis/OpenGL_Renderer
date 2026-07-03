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

void VertexArray::addInstancedBuffer(const VertexBuffer& VBO, unsigned int startLocation)
{
    bind();
    VBO.bind();

    // mat4 has 4 vec4s
    unsigned int vec4Size = 4 * sizeof(float);
    unsigned int mat4Size = 4 * sizeof(glm::mat4);

    for (unsigned int i = 0; i < 4; ++i)
    {
        unsigned int location = startLocation + i;
        uintptr_t offset = i * vec4Size;

        GLCall(glEnableVertexAttribArray(location));
        GLCall(glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, static_cast<int>(mat4Size), (const void*) offset));

        // only draw once per instance, not per vertex
        GLCall(glVertexAttribDivisor(location, 1));
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
