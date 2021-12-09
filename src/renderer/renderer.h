#pragma once

#include "vertexarray.h"
#include "buffer.h"
#include "shader.h"

class Renderer
{
public:
	Renderer(const Renderer&) = delete; // copy-constructor
	inline static Renderer& Get()
	{
		static Renderer m_Instance;
		return m_Instance;
	}
	void Clear() const;
	void SetClearColor(float red, float green, float blue, float alpha) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
protected:
	Renderer() = default; // default constructor
};