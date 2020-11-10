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

	SunObject* src2 = new SunObject();
	SphereObject* src = new SphereObject();

	Render->render();

	delete src;
	delete src2;
	delete Render;
	delete Mgr;

	return 0;
}