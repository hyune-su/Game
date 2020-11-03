#pragma once
#include "RenderableObject.h"

class makeObject : public RenderableObject {

public :
	void SetTranslate(float x, float y, float z);

	virtual void shutDown() override
	{
		RenderableObject::shutDown();
	}
};