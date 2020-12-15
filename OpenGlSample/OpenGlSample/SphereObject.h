#pragma once
#include "RenderableObject.h"
#include "AddObject.h"
#include "Renderer.h"

#include <string>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class SphereObject : public RenderableObject {

public:

	SphereObject()
	{
		name = "지구";
		AddObject::instance()->init(this, "지구.DDS", "sphere.obj");
		AddObject::instance()->render(this);
	}

	virtual void Init() override;

	virtual void Update(RenderableObject* src) override;

	virtual void shutDown() override
	{
		RenderableObject::shutDown();

		
	}
};