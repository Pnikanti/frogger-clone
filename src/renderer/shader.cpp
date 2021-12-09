#include <sstream>
#include <fstream>
#include <glew/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "log.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	: m_RendererId(0), m_VertexFile(vertexPath), m_FragmentFile(fragmentPath)
{
	LOGGER_INFO("Using shaders: {0}, {1}", vertexPath, fragmentPath);
	ShaderProgramSource source = Parse(vertexPath, fragmentPath);
	m_RendererId = Create(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererId);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::Create(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = Compile(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = Compile(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	int result;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetProgramInfoLog(program, length, &length, message);
		LOGGER_WARN("Failed to link shader program: {0}", message);
	}

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

ShaderProgramSource Shader::Parse(const std::string& vertexFile, const std::string& fragmentFile)
{
	std::ifstream vertexStream(vertexFile);
	std::ifstream fragmentStream(fragmentFile);

	std::string line;
	std::stringstream stringStream[2];

	while (getline(vertexStream, line))
	{
		stringStream[(int)ShaderType::VERTEX] << line << '\n';
	}
	while (getline(fragmentStream, line))
	{
		stringStream[(int)ShaderType::FRAGMENT] << line << '\n';
	}

	return { stringStream[0].str(), stringStream[1].str() };
}

unsigned int Shader::Compile(unsigned int type, const std::string& source)
{
	unsigned int shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		LOGGER_WARN("Failed to compile {0} shader: {1}", type == GL_VERTEX_SHADER ? "vertex" : "fragment", message);
		glDeleteShader(shader);
		return 0;
	}
	return shader;
}

void Shader::SetUniform4fv(const std::string& name, const glm::vec4& v0)
{
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(v0));
}

void Shader::SetUniform3fv(const std::string& name, const glm::vec3& v0)
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(v0));
}

void Shader::SetUniform2fv(const std::string& name, const glm::vec2& v0)
{
	glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(v0));
}

void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& v0)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(v0));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererId, name.c_str());

	if (location == -1)
		LOGGER_WARN("Uniform name does not exist: {0} ", name);

	m_UniformLocationCache[name] = location;
	return location;
}