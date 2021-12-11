#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>
#include "graphics.h"
#include "renderer.h"
#include "shader.h"
#include "shadermanager.h"
#include "context.h"
#include "entity.h"
#include "log.h"

void GraphicsComponent::Draw(Entity& entity) {}

QuadComponent::QuadComponent()
	: quad(Quad()), va(VertexArray()), vb(VertexBuffer()), ib(IndexBuffer()), shader(nullptr)
{
	LOGGER_TRACE("QuadComponent constructor called");
	va.Bind();
	vb.Set(quad.vertices, sizeof(quad.vertices));
	ib.Set(quad.indices, 6);

	shader = new Shader(std::string("res/shaders/vertex.shader"), std::string("res/shaders/fragment.shader"));
	ShaderManager::Get().GetShaders().emplace_back(shader);

	layout = VertexBufferLayout();
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
  	shader->Unbind();
}
QuadComponent::~QuadComponent()
{
	LOGGER_TRACE("QuadComponent destructor called");
}

void QuadComponent::Draw(Entity& entity)
{
	shader->Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(entity.GetPosition(), 0.0f))
		* glm::rotate(glm::mat4(1.0f), entity.GetRotationRadians(), {0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), glm::vec3(entity.GetSize(), 1.0f));

	shader->SetUniformMatrix4fv("u_Model", model);
	shader->SetUniform3fv("u_Color", entity.Color);

	Renderer::Get().Draw(va, ib, *shader);
}

TexturedQuadComponent::TexturedQuadComponent(const char* textureFilePath) :
	tQuad(TexturedQuad()),
	va(VertexArray()),
	vb(VertexBuffer()),
	ib(IndexBuffer()),
	texture(Texture(textureFilePath)),
	shader(nullptr)
{
	LOGGER_TRACE("TexturedQuadComponent constructor called");
	va.Bind();
	vb.Set(tQuad.vertices, sizeof(tQuad.vertices));
	ib.Set(tQuad.indices, 6);

	shader = new Shader(std::string("res/shaders/texturedvertex.shader"), std::string("res/shaders/texturedfragment.shader"));
	ShaderManager::Get().GetShaders().emplace_back(shader);
	
	texture.Bind();
	shader->SetUniform1i("u_Texture", 0);

	layout = VertexBufferLayout();
	layout.Push<float>(3); // vertex positions
	layout.Push<float>(2); // texture positions
	va.AddBuffer(vb, layout);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader->Unbind();
}

TexturedQuadComponent::~TexturedQuadComponent()
{
	LOGGER_TRACE("TexturedQuadComponent destructor called");
}

void TexturedQuadComponent::Draw(Entity& entity)
{
	shader->Bind();
	texture.Bind(0);

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(entity.GetPosition(), 0.0f))
		* glm::rotate(glm::mat4(1.0f), entity.GetRotationRadians(), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), glm::vec3(entity.GetSize(), 1.0f));

	shader->SetUniformMatrix4fv("u_Model", model);
	shader->SetUniform3fv("u_Color", entity.Color);
	shader->SetUniform1i("u_Texture", 0);
	Renderer::Get().Draw(va, ib, *shader);
}
