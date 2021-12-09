#pragma once

#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

enum class ShaderType
{
	NONE = -1,
	VERTEX = 0,
	FRAGMENT = 1
};

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& vertexFile, const std::string& fragmentFile);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniform4fv(const std::string& name, const glm::vec4& v0);
	void SetUniform3fv(const std::string& name, const glm::vec3& v0);
	void SetUniform2fv(const std::string& name, const glm::vec2& v0);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& v0);

private:
	int GetUniformLocation(const std::string& name);
	unsigned int Create(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int Compile(unsigned int type, const std::string& source);
	ShaderProgramSource Parse(const std::string& vertexFile, const std::string& fragmentFile);

private:
	std::unordered_map<std::string, int> m_UniformLocationCache;
	std::string m_FragmentFile;
	std::string m_VertexFile;
	unsigned int m_RendererId;
};