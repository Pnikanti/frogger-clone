#include <glew/glew.h>
#include <glfw/glfw3.h>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include "context.h"
#include "camera.h"
#include "game.h"
#include "log.h"
#include "entity.h"
#include "entitymanager.h"
#include "gui.h"
#include "guimanager.h"
#include "renderer.h"
#include "instrumentor.h"

unsigned int Context::SCR_WIDTH = 800;
unsigned int Context::SCR_HEIGHT = 600;
glm::mat4 Context::ViewProjectionMatrix = glm::mat4(0.0f);
glm::vec2 Context::Resolution = glm::vec2(0.0f);
OrthographicCamera* Context::m_Camera = nullptr;
GLFWwindow* Context::Window = nullptr;

void Context::Start(const char* windowName, int width, int height)
{
	PROFILE_FUNCTION();

	Alive = 1;
	SCR_WIDTH = width;
	SCR_HEIGHT = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, windowName, NULL, NULL);

	if (!Window)
	{
		glfwTerminate();
	}

	glfwMakeContextCurrent(Window);
	glfwSetFramebufferSizeCallback(Window, FrameBufferSizeCb);
	GLenum glewInitialized = glewInit();

	if (glewInitialized == GLEW_OK)
	{
		LOGGER_INFO("Glew version: {0}", glewGetString(GLEW_VERSION));
	}
	else
	{
		LOGGER_ERROR("Glew error: {0}", glewGetErrorString(glewInitialized));
	}

	glfwSwapInterval(1); // Enable vsync
	glEnable(GL_BLEND); // Enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	FrameBufferSizeCb(Window, SCR_WIDTH, SCR_HEIGHT);

	LOGGER_INFO("Context initialized!");
}

void Context::End()
{
	ImGui::DestroyContext();
	glfwTerminate();
}

void Context::FrameBufferSizeCb(GLFWwindow* window, int width, int height)
{
	LOGGER_TRACE("Framebuffer resize!");
	SCR_WIDTH = width;
	SCR_HEIGHT = height;

	if (m_Camera != nullptr)
	{
		delete m_Camera;
		m_Camera = nullptr;
	}

	m_Camera = CreateCamera((float)SCR_WIDTH, (float)SCR_HEIGHT);
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	Resolution = glm::vec2(SCR_WIDTH, SCR_HEIGHT);
	ViewProjectionMatrix = m_Camera->viewProjectionMatrix;
}

void Context::UpdateAllRenderTargets()
{
	EntityManager::Get().Draw();
	GuiManager::Get().Draw();
}

OrthographicCamera* Context::CreateCamera(float width, float height)
{
	float aspectRatio = width / height;
	float cameraDimensions = 20.0f;
	float bottom = -cameraDimensions;
	float top = cameraDimensions;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;

	LOGGER_TRACE("aspectRatio: {0}", aspectRatio);
	LOGGER_TRACE("bottom: {0}", bottom);
	LOGGER_TRACE("top: {0}", top);
	LOGGER_TRACE("left: {0}", left);
	LOGGER_TRACE("right: {0}", right);

	return new OrthographicCamera(left, right, bottom, top);
}

void Context::RenderOneFrame()
{
	PROFILE_FUNCTION();

	Alive = !glfwWindowShouldClose(Window);
	Renderer::Get().Clear();
	Renderer::Get().SetClearColor(1.0f, 0.0f, 1.0f, 1.0f);
	UpdateAllRenderTargets();
	glfwSwapBuffers(Window);
	glfwPollEvents();
}
