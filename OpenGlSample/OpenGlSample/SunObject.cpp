#pragma once
#include "SunObject.h"

void SunObject::Init()
{
	SetScale(3.0f, 3.0f, 3.0f);

	AddObject::instance()->Add(this, "지구");

	SetPosition(0.0f, 3.0f, 0.0f);
}

void SunObject::Update(RenderableObject* src)
{
	printf("태양 위치 :: %f, %f :: 로컬 위치 :: %f, %f\n", world_pos.x, world_pos.y, object_pos.x, object_pos.y);

	IsGliter(this, 0.01f);
}
