#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

class Gui;
struct GLFWwindow;
class OrthographicCamera;

class Context {
public:
	Context(const Context&) = delete;
	inline static Context& Get()
	{
		static Context m_Instance;
		return m_Instance;
	}
	void RenderOneFrame();
	void Start(const char* windowName, int width, int height);
	void End();
public:
	static GLFWwindow* Window;
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;
	static glm::vec2 Resolution;
	static glm::mat4 ViewProjectionMatrix;

	bool Alive;
protected:
	Context() = default;
private:
	static void FrameBufferSizeCb(GLFWwindow* window, int width, int height);
	static OrthographicCamera* CreateCamera(float width, float height);
	void UpdateAllRenderTargets();
private:
	static OrthographicCamera* m_Camera;
};
