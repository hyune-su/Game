#pragma once
#include <stdlib.h>
#include <time.h>

#include "FileManager.h"
#include "Renderer.h"

using namespace glm;
using namespace std;

Renderer* Render = Renderer::instance();
AddObject* AddObj = AddObject::instance();

int main(void)
{
	FileManager* Mgr = new FileManager();


	SphereObject* Sphere = new SphereObject();
	SunObject* Sun = new SunObject();
	EnemyObject* Enemy = new EnemyObject[10];

	Render->render();

	delete Sun;
	delete Sphere;
	delete Mgr;

	return 0;
}