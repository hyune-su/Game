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
		Mgr->GetData(fast[i], "����.DDS", "sphere.obj");
		slow[i] = new makeObject();
		Mgr->GetData(slow[i], "��.DDS", "sphere.obj");
	}

	Render->SetShader("������_20161642_vs.shader", "������_20161642_fs.shader");


	Mgr->GetData(Mecury, "�¾�.DDS", "sphere.obj");
	Mgr->GetData(Cube, "�¾�.DDS", "cube.obj");

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

			//�浹üũ ��¦�� �ӵ� ������ ���� �� �ӵ� ���ҿ� �ް� �¾��� �浹 üũ
			for (int i = 0; i < size; i++)
			{
				if (fast[i]->collision_check)
				{
					//�˴ٿ� �� ��� �ϸ� ��ü�� ������ �� �ִ��� Ȯ���ϱ�, ����� ����� �������� �ʰ� ����
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