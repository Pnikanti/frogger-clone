#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "shader.h"

class ShaderManager {
public:
	ShaderManager(const ShaderManager&) = delete;

	inline static ShaderManager& Get() {
		static ShaderManager m_Instance;
		return m_Instance;
	}

	void Init(size_t size);

	void UpdateUniform(const std::string& uniformName, glm::mat4 v0) const;
	void UpdateUniform(const std::string& uniformName, glm::vec2 v0) const;

	inline std::vector<Shader*>& GetShaders() { return Shaders; }
protected:
	ShaderManager::ShaderManager() = default;
private:
	std::vector<Shader*> Shaders;
};
