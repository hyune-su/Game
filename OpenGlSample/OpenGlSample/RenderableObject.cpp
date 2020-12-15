#pragma once
#include "RenderableObject.h"
#include "AddObject.h"

#include <stdlib.h>
#include <time.h>

RenderableObject::RenderableObject()
{
	Scale_Model = glm::scale(Scale_Model, glm::vec3(0.3, 0.3, 0.3));
}

void RenderableObject::SetScale(float x, float y, float z)
{
	Scale_Model = glm::scale(Scale_Model, glm::vec3(x, y, z));
}

void RenderableObject::SetPosition(float x, float y, float z)
{
	float abs_x = abs(world_pos.x - x);
	float abs_y = abs(world_pos.y - y);

	//2d이므로 z 사용 안할 것임
	float abs_z = abs(world_pos.z - z);

	if (x < world_pos.x)
	{
		Move_Model = glm::translate(Move_Model, glm::vec3(-abs_x, 0,0));
		object_pos.x = world_pos.x - abs_x;
	}
	else
	{
		Move_Model = glm::translate(Move_Model, glm::vec3(abs_x, 0, 0));
		object_pos.x = world_pos.x + abs_x;
	}

	if (y < world_pos.y)
	{
		Move_Model = glm::translate(Move_Model, glm::vec3(0, -abs_y, 0));
		object_pos.y = world_pos.y - abs_y;
	}
	else
	{
		Move_Model = glm::translate(Move_Model, glm::vec3(0, abs_y, 0));
		object_pos.y = world_pos.y + abs_y;
	}
}

void RenderableObject::SetTranslate(float x, float y, float z)
{
	Move_Model = glm::translate(Move_Model, glm::vec3(x, y, z));
	object_pos += glm::vec3(x, y, z);
	//world_pos += glm::vec3(x, y, z);
}

void RenderableObject::SetRotate(float rad, float _x, float _y, float _z)
{
	//가만히 있을 경우 좌표 값은 제대로 구해지지만 이동할 경우가 문제..

	//Rotate_Model = glm::rotate(Rotate_Model, glm::radians(rad), glm::vec3(_x, _y, _z));

	Theta += glm::radians(rad);

	if (Theta >= glm::radians(360.0f))
	{
		Theta -= glm::radians(360.0f);
	}

	object_pos.x = object_x * cos(Theta);
	object_pos.y = object_x * sin(Theta);
}

void RenderableObject::IsPatrol(float x, float y, float z)
{
	srand((unsigned int)time(NULL));

	object_pos.x += x;
	object_pos.y += y;
	object_pos.z += z;
}

void RenderableObject::SetAlpha(float a)
{
	alpha = a;
}

void RenderableObject::IsGliter(RenderableObject* src, double speed)
{
	if (src->alpha >= 1)
	{
		src->isPlus = false;
	}
	else if (src->alpha <= 0.5)
	{
		src->isPlus = true;
	}

	if (src->isPlus)
	{
		src->alpha += speed;
	}
	else
	{
		src->alpha -= speed;
	}
}