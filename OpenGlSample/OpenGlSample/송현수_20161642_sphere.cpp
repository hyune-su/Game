#pragma once
#include <stdlib.h>
#include <time.h>

#include "FileManager.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

int main(void)
{
	FileManager* Mgr = new FileManager();

	Renderer* Render = new Renderer();

	RenderableObject* Mecury = new RenderableObject();

	//SphereObject* src = new SphereObject();

	//Mgr->GetData(Mecury, "태양.DDS", "sphere.obj");
	//Mgr->GetData(Cube, "태양.DDS", "cube.obj");

	//Mgr->SetObjectRange(Mecury, -35, 35, -26, 26);

	//Mgr->SetObject(Mecury, 3.0f, 0.0f, 0.0f);

	/*for (int i = 0; i < size; i++)
	{
		Mgr->RandomSetObject(fast[i], -35, 35, -26, 26);

		Mgr->RandomSetObject(slow[i], -35, 35, -26, 26);

		Mgr->SetObjectRange(slow[i], -35, 35, -26, 26);
	}*/

	//Mgr->IsGliter(Mecury, true, 0.001);

	//Mgr->SetCharacter(Mecury);

	//Render->addObject(Mecury);

	/*for (int i = 0; i < size; i++)
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
	}*/

	do
	{
		Render->render();

		//if (Render->isRenderTiming())
		//{
			//Render->Update(Cube);
			//Render->isPhysicRender();

			////충돌체크 반짝이 속도 증가용 지구 및 속도 감소용 달과 태양의 충돌 체크
			//for (int i = 0; i < size; i++)
			//{
			//	if (fast[i]->collision_check)
			//	{
			//		//셧다운 시 어떻게 하면 객체를 지워줄 수 있는지 확인하기, 현재는 제대로 지워지지 않고 있음
			//		fast[i]->shutDown();

			//		Mecury->gliter_speed += 0.01;

			//		printf("%f", Mecury->gliter_speed);
			//	}

			//	if (slow[i]->collision_check)
			//	{
			//		slow[i]->shutDown();

			//		Mecury->gliter_speed -= 0.01;
			//	}
			//}
		//}
	} while (Render->isEND());

	Render->shutDown();

	//delete fast[i];
	//delete slow[i];
	//delete Cube;
	//delete Mecury;

	return 0;
}