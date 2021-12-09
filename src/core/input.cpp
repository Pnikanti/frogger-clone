#include <glfw/glfw3.h>
#include "input.h"
#include "context.h"
#include "entity.h"
#include "game.h"
#include "log.h"
#include "physics.h"
#include "entitymanager.h"

void InputComponent::Update(Entity& entity)
{
	LOGGER_INFO("inputcomponent called!");
}

void InputComponent::Update(Game& application)
{

}

void InputComponent::Update()
{

}

void PlayerInputComponent::Update(Entity& entity)
{
	LOGGER_INFO("playerinputcomponent called!");
	if (glfwGetKey(Context::Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		LOGGER_INFO("Upwards!");
	}
	else if (glfwGetKey(Context::Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		LOGGER_INFO("Downwards!");
	}
}

void ComputerInputComponent::Update(Entity& entity)
{
}


void GameInputComponent::Update(Game& gameInstance)
{
	CurrentTime = (float)glfwGetTime();
	if (CurrentTime > PreviousTime + 0.3f)
	{
		switch (Game::State)
		{
		case GameState::Play:
		{
			if (glfwGetKey(Context::Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				LOGGER_INFO("Main menu");
				PreviousTime = CurrentTime;
			}
			else if (glfwGetKey(Context::Window, GLFW_KEY_P) == GLFW_PRESS)
			{
				LOGGER_INFO("Pause");
				PreviousTime = CurrentTime;
			}
			break;
		}
		case GameState::MainMenu:
		{
			if (glfwGetKey(Context::Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				LOGGER_INFO("Exit");
				gameInstance.Exit();
				PreviousTime = CurrentTime;
			}
			else if (glfwGetKey(Context::Window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				LOGGER_INFO("Start");
				gameInstance.Start();
				PreviousTime = CurrentTime;
			}
			break;
		}
		case GameState::GameOver:
		{
			if (glfwGetKey(Context::Window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				LOGGER_INFO("Start");
				PreviousTime = CurrentTime;
			}
			else if (glfwGetKey(Context::Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				LOGGER_INFO("Main menu");
				PreviousTime = CurrentTime;
			}
			break;
		}
		case GameState::Pause:
		{
			if (glfwGetKey(Context::Window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				LOGGER_INFO("Play");
				PreviousTime = CurrentTime;
			}
			else if (glfwGetKey(Context::Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				LOGGER_INFO("Main menu");
				PreviousTime = CurrentTime;
			}
			break;
		}
		}
	}
}