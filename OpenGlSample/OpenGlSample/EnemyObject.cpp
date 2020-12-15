#pragma once
#include "EnemyObject.h"

#include <time.h>

void EnemyObject::Init()
{
	name = "적_가로";

	int plus_minus = rand() % 2;

	int rand_pos = rand() % 8;

	if (plus_minus == 1)
	{
		SetPosition(-5 - rand_pos, rand_pos, object_pos.z);
	}
	else
	{
		SetPosition(-5 - rand_pos, -rand_pos, object_pos.z);
	}
}

void EnemyObject::Update(RenderableObject* src)
{
	IsGliter(this, 0.02f);

	int rand_move = rand() % 20;

	SetTranslate(0.01f * rand_move, 0.0f, 0.0f);

	if (world_pos.x > 8)
	{
		int plus_minus = rand() % 2;

		int rand_pos = rand() % 8;

		if (plus_minus == 1)
		{
			SetPosition(-5 - rand_pos, rand_pos, object_pos.z);
		}
		else
		{
			SetPosition(-5 - rand_pos, -rand_pos, object_pos.z);
		}
	}

	if (collision_check)
	{
		if (collision_name == "지구" || collision_name == "태양")
		{
			shutDown();
		}
	}

	printf("적 위치 :: %f, %f\n", world_pos.x, world_pos.y);
}
