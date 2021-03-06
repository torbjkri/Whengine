#include "Shader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
namespace fs = std::filesystem;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string& filepath)
    : m_FilePath(filepath)
    , m_RendererID()
{
    ShaderProgramSource source = ParseShader(m_FilePath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

ShaderProgramSource Shader::ParseShader(const std::string& filePath)
{
    std::string projDir = (fs::current_path()).string() + "\\";
    std::ifstream stream(projDir + filePath);
    std::stringstream ss[2];

    std::cout << projDir + filePath << std::endl;

    enum class ShaderType
    {
        NONE = 0, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("vertex") != std::string::npos)
            type = ShaderType::VERTEX;
        else if (line.find("fragment") != std::string::npos)
            type = ShaderType::FRAGMENT;
        else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " <<
            (GL_VERTEX_SHADER ? "vertex" : "fragment") <<
            " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}



int Shader::GetUniformLocation(const std::string& name) const
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1)
        m_UniformLocationCache[name] = location;
    else
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR,
            1, GL_DEBUG_SEVERITY_LOW, -1, ("Warning: Uniform " + name + " doesn't exist!").c_str());

    return location;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::Delete() const
{
    glDeleteProgram(m_RendererID);
}

void Shader::SetUniform1i(const std::string& name, const int value) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform1i(m_RendererID, location, value);
}

void Shader::SetUniform1f(const std::string& name, const float value) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform1f(m_RendererID, location, value);
}

void Shader::SetUniform3f(const std::string& name, const float v1, const float v2, const float v3) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform3f(m_RendererID, location, v1, v2, v3);
}

void Shader::SetUniform3f(const std::string& name, const glm::vec3& data) const
{
    SetUniform3f(name, data.x, data.y, data.z);
}

void Shader::SetUniform3fv(const std::string& name, const int count, const float * data) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform3fv(m_RendererID, location, count, data);
}

void Shader::SetUniform3fv(const std::string& name, const std::vector<glm::vec3>& data) const
{
    SetUniform3fv(name, data.size(), &data[0].x);
}

void Shader::SetUniform4f(const std::string& name, const float v1, const float v2, const float v3, const float v4) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform4f(m_RendererID, location, v1, v2, v3, v4);
}

void Shader::SetUniform4fv(const std::string& name, const int count, glm::vec4 data) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform4fv(m_RendererID, location, count, &data.x);
}

void Shader::SetUniform4fv(const std::string& name, const int count, const std::vector<float> data) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform4fv(m_RendererID, location, count, &data[0]);
}

void Shader::SetUniform4fv(const std::string& name, const int count, const float * data) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniform4fv(m_RendererID, location, count, data);
}

void Shader::SetUniformMatrix4fv(const std::string& name, const int count, glm::mat4 matrix) const
{
    int location = GetUniformLocation(name);
    if (location != -1)
        glProgramUniformMatrix4fv(m_RendererID, location, count, false, glm::value_ptr(matrix));
}
