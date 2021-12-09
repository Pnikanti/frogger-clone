#include <glfw/glfw3.h>
#include <box2d/b2_body.h>
#include <string.h>
#include "context.h"
#include "game.h"
#include "log.h"
#include "camera.h"
#include "graphics.h"
#include "physics.h"
#include "entity.h"
#include "entitymanager.h"
#include "gui.h"
#include "guimanager.h"
#include "shader.h"
#include "shadermanager.h"
#include "input.h"
#include "instrumentor.h"

float Game::TimeStep = 1.0f / 60.0f;
GameState Game::State = GameState::MainMenu;

Game::Game(const char* appName, int width, int height)
{
	Logger::Init(appName);
	EntityManager::Get().Init(3);
	GuiManager::Get().Init(2);
	ShaderManager::Get().Init(2);

	CreateGameGui();

	m_PhysicsWorld = new PhysicsWorld();
	m_PhysicsListener = new ContactListener();
	m_Input = new GameInputComponent();

	Context::Get().Start(appName, width, height);
	Loop();
}

Game::~Game()
{
	for (auto i : GuiManager::Get().GetContexts())
	{
		if (i != nullptr)
			delete i;
	}
	GuiManager::Get().GetContexts().clear();
	EntityManager::Get().GetEntities().clear();
	EntityManager::Get().GetEntityMap().clear();
}

void Game::Start()
{
	LOGGER_INFO("Creating entity!");

	CreateEntity(
		new PlayerInputComponent(),
		new PhysicsPolygonComponent(),
		new QuadComponent(), 
		glm::vec2(5.0f),
		glm::vec2(1.0f),
		0.0f, 
		glm::vec3(1.0f, 1.0f, 0.0f), 
		b2_kinematicBody, 
		1.0f,
		0.5f,
		0.2f
	);
	ShaderManager::Get().UpdateUniform("viewProjection", Context::ViewProjectionMatrix);
	State = GameState::Play;
}

void Game::End()
{
	EntityManager::Get().GetEntities().clear();
	EntityManager::Get().GetEntityMap().clear();
}

void Game::Exit()
{
	glfwSetWindowShouldClose(Context::Window, true);
}

void Game::Loop()
{
	double previous, current, elapsed, lag;
	previous = current = elapsed = lag = 0.0;

	while (Context::Get().Alive)
	{
		current = glfwGetTime();
		elapsed = current - previous;
		previous = current;
		lag += elapsed;

		ProcessInput();
		while (lag >= TimeStep)
		{
			if (State == GameState::Play)
			{
				m_PhysicsWorld->Update();
				UpdateAllEntities();
			}
			lag -= TimeStep;
		}
		Context::Get().RenderOneFrame();
	}
}

void Game::ProcessInput()
{
	m_Input->Update(*this);

	for (auto e : EntityManager::Get().GetEntities())
	{
		if (e != nullptr)
			e->ProcessInput();
	}
}

void Game::CreateEntity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics, glm::vec2 size, glm::vec2 position, float rotation, glm::vec3 color, b2BodyType bodytype, float density, float friction, float restitution)
{
	EntityManager::Get().GetEntities().emplace_back(
		new Entity(input, physics, graphics, position, size, rotation, color, bodytype, density, friction, restitution)
	);
}

void Game::UpdateAllEntities()
{
	for (auto i = EntityManager::Get().GetEntities().begin(); i != EntityManager::Get().GetEntities().end(); i++)
	{
		Entity* e = (*i);
		if (e != nullptr)
			e->Advance();
	}
}

void Game::CreateGameGui()
{
	GuiManager::Get().GetContexts().push_back(new GameGuiContext());
#ifdef DEBUG
	GuiManager::Get().GetContexts().push_back(new DebugGuiContext());
#endif
}

int main()
{
	Instrumentor::Get().BeginSession("Frogger statistics");
	auto x = Game("Frogger-clone", 1200, 800);
	Instrumentor::Get().EndSession();
	return 0;
}