#pragma once
#include "RenderableObject.h"
#include "AddObject.h"

#include <stdlib.h>
#include <time.h>

RenderableObject::RenderableObject()
{
	Trans_Model = glm::scale(Trans_Model, glm::vec3(0.3,0.3,0.3));

	SetTranslate(3.0f, 0.0f, 0.0f);

	AddObject::instance()->init(this, "지구.DDS", "sphere.obj");
	AddObject::instance()->render(this);

	//다 만들어 지고서 넣어야 함 생성될 때가 아니라.
}

void RenderableObject::SetTranslate(float x, float y, float z)
{

	object_pos.x += x;
	object_pos.y += y;
	object_pos.z += z;

	if (object_pos.x >= area_min_x && object_pos.x <= area_max_x && object_pos.y >= area_min_y && object_pos.y <= area_max_y)
	{
		Trans_Model = glm::translate(Trans_Model, glm::vec3(x, y, z));
	}
	else if (object_pos.x < area_min_x)
	{
		object_pos.x = area_min_x;
	}
	else if (object_pos.x > area_max_x)
	{
		object_pos.x = area_max_x;
	}
	else if (object_pos.y < area_min_y)
	{
		object_pos.y = area_min_y;
	}
	else if (object_pos.y > area_max_y)
	{
		object_pos.y = area_max_y;
	}
	else
	{
		//다른 경우의 수 확인
		delete this;
	}
}

void RenderableObject::IsPatrol(float x, float y, float z)
{
	srand((unsigned int)time(NULL));

	object_pos.x += x;
	object_pos.y += y;
	object_pos.z += z;

	if (object_pos.x > area_min_x && object_pos.x < area_max_x && object_pos.y > area_min_y && object_pos.y < area_max_y)
	{
		Trans_Model = glm::translate(Trans_Model, glm::vec3(x, y, z));
	}
	else if (object_pos.x >= area_max_x)
	{
		object_pos.x = area_min_x + 1;
		Trans_Model = glm::translate(Trans_Model, glm::vec3(-(area_max_x - area_min_x) + 1, 0, z));
	}
	else if (object_pos.y >= area_max_y)
	{
		object_pos.y = area_min_y + 1;
		Trans_Model = glm::translate(Trans_Model, glm::vec3(0, -(area_max_y - area_min_y) + 1, z));
	}
	//else if (object_pos.y <= area_min_y)
	//{
	//	object_pos.y = area_min_y;
	//	Trans_Model = glm::translate(Trans_Model, glm::vec3(x, -y, z));
	//}
	//else if (object_pos.y >= area_max_y)
	//{
	//	object_pos.y = area_max_y;
	//	Trans_Model = glm::translate(Trans_Model, glm::vec3(x, -y, z));
	//}
	//else
	//{
	//	//다른 경우의 수 확인
	//	delete this;
	//}
}

void RenderableObject::SetObjectRange(double min_x, double max_x, double min_y, double max_y)
{
	area_min_x = min_x;
	area_max_x = max_x;

	area_min_y = min_y;
	area_max_y = max_y;
}

void RenderableObject::SetAlpha(float a)
{
	alpha = a;
}

void RenderableObject::IsGliter(RenderableObject* src, bool isgliter, double speed)
{
	if (src->isGliter)
	{
		if (src->gliter_speed <= 0)
		{
			gliter_speed = 0;
		}

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
			src->alpha += src->gliter_speed;
		}
		else
		{
			src->alpha -= src->gliter_speed;
		}
	}
}