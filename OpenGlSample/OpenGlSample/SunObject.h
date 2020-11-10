#pragma once
#include "RenderableObject.h"
#include "AddObject.h"
#include "FileManager.h"

#include <string>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class SunObject : public RenderableObject {

public:

	SunObject()
	{
		SetTranslate(3.0f, 0.0f, 0.0f);

		FileManager::instance()->SetCharacter(this);

		AddObject::instance()->init(this, "еб╬Г.DDS", "sphere.obj");
		AddObject::instance()->render(this);
	}

	virtual void Update(RenderableObject* src) override
	{
		static int i = 0;
		i++;
		printf("Render :: %d \n", i);
	}

	virtual void shutDown() override
	{
		RenderableObject::shutDown();
	}
};