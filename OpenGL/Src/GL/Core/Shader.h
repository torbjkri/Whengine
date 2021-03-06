#pragma once
#include <glm/glm.hpp>
#include <string>
#include <unordered_map>


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	mutable std::unordered_map<std::string, int> m_UniformLocationCache;

	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(const unsigned int type, const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& name) const;

public:
	Shader() = default;
	Shader(const std::string& filename);

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	// Set uniforms
	void SetUniform1i(const std::string& name, const int value) const;
	void SetUniform1f(const std::string& name, const float value) const;
	void SetUniform3f(const std::string& name, const float v1, const float v2, const float v3) const;
	void SetUniform3f(const std::string& name, const glm::vec3& data) const;
	void SetUniform3fv(const std::string& name, const int count, const float* data) const;
	void SetUniform3fv(const std::string& name, const std::vector<glm::vec3>& data) const;
	void SetUniform4f(const std::string& name, const float v1, const float v2, const float v3, const float v4) const;

	void SetUniform4fv(const std::string& name, const int count, glm::vec4 data) const;
	void SetUniform4fv(const std::string& name, const int count, const std::vector<float> data) const;
	void SetUniform4fv(const std::string& name, const int count, const float * data) const;

	void SetUniformMatrix4fv(const std::string& name, const int count, glm::mat4 mat) const;
};

