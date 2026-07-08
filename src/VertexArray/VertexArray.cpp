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

void VertexArray::addInstancedBuffer(const VertexBuffer& VBO, unsigned int startLocation, unsigned int componentCount)
{
    bind();
    VBO.bind();

    // Use ceiling division so 6 components properly results in 2 slots (6 + 3) / 4 = 2
    unsigned int numSlots = (componentCount + 3) / 4;
    int totalStride = static_cast<int>(componentCount * sizeof(float));

    for (unsigned int i = 0; i < numSlots; ++i)
    {
        unsigned int location = startLocation + i;
        uintptr_t offset = i * 4 * sizeof(float);

        // how many elements are left for this specific slot channel
        // For i=0 (components=6): min(4, 6 - 0) -> 4
        // For i=1 (components=6): min(4, 6 - 4) -> 2
        int remainingComponents = static_cast<int>(componentCount) - static_cast<int>(i * 4);
        int slotSize = std::min<int>(4, remainingComponents);

        GLCall(glEnableVertexAttribArray(location));
        GLCall(glVertexAttribPointer(location, slotSize, GL_FLOAT, GL_FALSE, totalStride, (const void*) offset));

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
