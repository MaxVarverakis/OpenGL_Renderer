#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource
{
    std::string VertexSourceStr;
    std::string FragmentSourceStr;
};

class Shader
{
private:
    std::string m_filepath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_uniform_location_cache;

    ShaderProgramSource parseShader(const std::string& filepath, const std::string& prefix);

    unsigned int compileShader(unsigned int type, const std::string& source);

    unsigned int createShader(const ShaderProgramSource& shader_source);

    int getUniformLocation(const std::string& name);

public:
    Shader(const std::string& filepath, const std::string& prefix = "");
    
    ~Shader();

    void bind() const;

    void unbind() const;
    
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    void setUniform4f(const std::string& name, float val);
    
    void setUniform1i(const std::string& name, int value);
    
    void setUniform1f(const std::string& name, float value);
    
    void setUniformMatrix4fv(const std::string& name, const glm::mat4 matrix);
};
