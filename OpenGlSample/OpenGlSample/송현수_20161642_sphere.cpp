#pragma once
#include <stdlib.h>
#include <time.h>

#include "FileManager.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

int main(void)
{
	const int size = 20;

	srand((unsigned int)time(NULL));

	FileManager* Mgr = new FileManager();

	Renderer* Render = new Renderer();
	Render->SetCamera_World(0, 0, 20);

	makeObject* Mecury = new makeObject();
	NonRenderObject* Cube = new NonRenderObject();

	makeObject* fast[size];
	makeObject* slow[size];

	for (int i = 0; i < size; i++)
	{
		fast[i] = new makeObject();
		Mgr->GetData(fast[i], "지구.DDS", "sphere.obj");
		slow[i] = new makeObject();
		Mgr->GetData(slow[i], "달.DDS", "sphere.obj");
	}

	Render->SetShader("송현수_20161642_vs.shader", "송현수_20161642_fs.shader");


	Mgr->GetData(Mecury, "태양.DDS", "sphere.obj");
	Mgr->GetData(Cube, "태양.DDS", "cube.obj");

	Mgr->SetObjectRange(Mecury, -35, 35, -26, 26);

	Mgr->SetObject(Mecury, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < size; i++)
	{
		Mgr->RandomSetObject(fast[i], -35, 35, -26, 26);

		Mgr->RandomSetObject(slow[i], -35, 35, -26, 26);

		Mgr->SetObjectRange(slow[i], -35, 35, -26, 26);
	}

	Mgr->IsGliter(Mecury, true, 0.001);

	Mgr->SetCharacter(Mecury);

	Render->addObject(Mecury);

	for (int i = 0; i < size; i++)
	{
		Render->addObject(fast[i]);
	}

	for (int i = 0; i < size; i++)
	{
		Render->addObject(slow[i]);

		if (i % 2 == 0)
		{
			Mgr->Moving(slow[i], 0, 0.15);
		}
		else
		{
			Mgr->Moving(slow[i], 0.1, 0.2);
		}
	}

	do
	{
		Render->render();

		if (Render->isRenderTiming())
		{
			Render->Update(Cube);

			Render->isPhysicRender();

			//충돌체크 반짝이 속도 증가용 지구 및 속도 감소용 달과 태양의 충돌 체크
			for (int i = 0; i < size; i++)
			{
				if (fast[i]->collision_check)
				{
					//셧다운 시 어떻게 하면 객체를 지워줄 수 있는지 확인하기, 현재는 제대로 지워지지 않고 있음
					fast[i]->shutDown();

					Mecury->gliter_speed += 0.01;
				}

				if (slow[i]->collision_check)
				{
					slow[i]->shutDown();

					Mecury->gliter_speed -= 0.01;
				}
			}
		}
	} while (Render->isEND());

	Render->shutDown();

	for (int i = 0; i < size; i++)
	{
		delete fast[i];
		delete slow[i];
	}
	delete Cube;
	delete Mecury;

	return 0;
}