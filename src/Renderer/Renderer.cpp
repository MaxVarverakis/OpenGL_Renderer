#include <iostream>
#include "Renderer.hpp"

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
        {
            std::cout << "[OpenGL Error] (" << error << "): " << function << " " <<
            file << ":" << line << std::endl;
            return false;
        }

        return true;
}


void printShaderInfoLog(unsigned int shader)
{
    int success;
    char infoLog[512];
    GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if (!success)
    {
        GLCall(glGetShaderInfoLog(shader, 512, NULL, infoLog));
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void printProgramInfoLog(unsigned int program)
{
    int success;
    char infoLog[512];
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if (!success)
    {
        GLCall(glGetProgramInfoLog(program, 512, NULL, infoLog));
        std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
}

void Renderer::drawTriangles(const VertexArray& VAO, const Shader& shader) const
{
    shader.bind();
    VAO.bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, 3));
}

void Renderer::drawTriangles(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const
{
    shader.bind();
    VAO.bind();
    IBO.bind();

    GLCall(glDrawElements(GL_TRIANGLES, static_cast<int>(IBO.getCount()), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawCircles(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const
{
    // just a wrapper for drawTriangles
    drawTriangles(VAO, IBO, shader);
}

void Renderer::drawRectangles(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const
{
    // just a wrapper for drawTriangles
    drawTriangles(VAO, IBO, shader);
}

void Renderer::drawLines(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const
{
    shader.bind();
    VAO.bind();
    IBO.bind();

    GLCall(glDrawElements(GL_LINES, static_cast<int>(IBO.getCount()), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawLines(const VertexArray& VAO, const VertexBuffer& VBO, const Shader& shader) const
{
    shader.bind();
    VAO.bind();

    GLCall(glDrawArrays(GL_LINES, 0, static_cast<int>(VBO.size() / (2 * sizeof(float)))));
}

void Renderer::drawLineStrip(const VertexArray& VAO, const VertexBuffer& VBO, const Shader& shader) const
{
    shader.bind();
    VAO.bind();

    GLCall(glDrawArrays(GL_LINE_STRIP, 0, static_cast<int>(VBO.size() / (2 * sizeof(float)))));
}

void Renderer::clear() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}
