#include "shadermanager.h"

void ShaderManager::Init(size_t size)
{
	Shaders.reserve(size);
}

void ShaderManager::UpdateUniform(const std::string& uniformName, glm::mat4 v0) const
{
	for (auto i : Shaders)
	{
		if (i != nullptr)
		{
			i->Bind();
			i->SetUniformMatrix4fv(uniformName, v0);
		}
	}
}
void ShaderManager::UpdateUniform(const std::string& uniformName, glm::vec2 v0) const
{
	for (auto i : Shaders)
	{
		if (i != nullptr)
		{
			i->Bind();
			i->SetUniform2fv(uniformName, v0);
		}
	}
}