#include "Shader.hpp"
#include "../Renderer/Renderer.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string& filepath)
    : m_filepath { filepath } // keep `filepath` as member for debugging purposes
    , m_RendererID { 0 }
{
    ShaderProgramSource shader_source { parseShader(filepath) };
    m_RendererID = createShader(shader_source);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::parseShader(const std::string& filepath)
{
    
    std::stringstream VertexSource, FragmentSource;

    std::string line;
    
    std::ifstream vfile(filepath + "/vertex.shader");
    while (std::getline(vfile, line))
    {
        VertexSource << line << '\n';
    }
    vfile.close();
    
    std::ifstream ffile(filepath + "/fragment.shader");
    while (std::getline(ffile, line))
    {
        FragmentSource << line << '\n';
    }
    ffile.close();

    return { VertexSource.str(), FragmentSource.str() };
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int shader_id { glCreateShader(type) });
    
    const char* source_c = source.c_str();
    GLCall(glShaderSource(shader_id, 1, &source_c, nullptr));
    GLCall(glCompileShader(shader_id));
    printShaderInfoLog(shader_id);

    return shader_id;
}

unsigned int Shader::createShader(const ShaderProgramSource& shader_source)
{
    GLCall(unsigned int shader_program { glCreateProgram() });
    unsigned int vertex_shader { compileShader(GL_VERTEX_SHADER, shader_source.VertexSourceStr) };
    unsigned int fragment_shader { compileShader(GL_FRAGMENT_SHADER, shader_source.FragmentSourceStr) };

    GLCall(glAttachShader(shader_program, vertex_shader));
    GLCall(glAttachShader(shader_program, fragment_shader));
    GLCall(glLinkProgram(shader_program));
    printProgramInfoLog(shader_program);
    GLCall(glValidateProgram(shader_program));

    GLCall(glDeleteShader(vertex_shader));
    GLCall(glDeleteShader(fragment_shader));

    return shader_program;
}

void Shader::bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4 matrix)
{
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
    // GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end()) { return m_uniform_location_cache[name]; }

    GLCall(int location { glGetUniformLocation(m_RendererID, name.c_str()) });
    if (location == -1)
    {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    
    m_uniform_location_cache[name] = location;
    
    return location;
}
