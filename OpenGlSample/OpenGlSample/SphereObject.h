#pragma once
#include "RenderableObject.h"
#include "AddObject.h"

#include <string>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class SphereObject : public RenderableObject {

public : 

	SphereObject() 
	{
		SetTranslate(0.0f, 0.0f, 0.0f);

		isRender = false;

		AddObject::instance()->init(this, "Áö±¸.DDS", "sphere.obj");
		AddObject::instance()->render(this);
	}

	virtual void Update(RenderableObject* src) override
	{
		static int i = 0;
		i++;
		printf("Nonrender :: %d \n", i);
	}

	virtual void shutDown() override
	{
		RenderableObject::shutDown();
	}
};