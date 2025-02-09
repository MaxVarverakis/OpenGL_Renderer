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

void Renderer::draw(const VertexArray& VAO, const IndexBuffer& IBO, const Shader& shader) const
{
    shader.bind();
    VAO.bind();
    IBO.bind();

    // GLCall(glDrawElements(GL_LINES, static_cast<int>(IBO.getCount()), GL_UNSIGNED_INT, nullptr));
    GLCall(glDrawElements(GL_TRIANGLES, static_cast<int>(IBO.getCount()), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
    GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    GLCall(glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT));
}
