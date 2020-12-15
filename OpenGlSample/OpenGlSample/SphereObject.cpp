#pragma once
#include "SphereObject.h"

void SphereObject::Init()
{
	SetPosition(10.0f, 0.0f, 0.0f);
}

void SphereObject::Update(RenderableObject* src)
{
	if (glfwGetKey(Renderer::instance()->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		SetTranslate(0.0f, 0.3f * Renderer::instance()->Frame, 0.0f);
	}
	if (glfwGetKey(Renderer::instance()->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		SetTranslate(0.0f, -0.3f * Renderer::instance()->Frame, 0.0f);
	}
	if (glfwGetKey(Renderer::instance()->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		SetTranslate(-0.3f * Renderer::instance()->Frame, 0.0f, 0.0f);
	}
	if (glfwGetKey(Renderer::instance()->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		SetTranslate(0.3f * Renderer::instance()->Frame, 0.0f, 0.0f);
	}

	printf("지구 위치 :: %f, %f\n", world_pos.x, world_pos.y);
}