#include <glew/glew.h>
#include "renderer.h"
#include "instrumentor.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	PROFILE_FUNCTION();
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
	PROFILE_FUNCTION();
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetClearColor(float red, float green, float blue, float alpha) const
{
	PROFILE_FUNCTION();
	glClearColor(red, green, blue, alpha);
}