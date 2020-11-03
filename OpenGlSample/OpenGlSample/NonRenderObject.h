#pragma once
#include "Object.h"
#include "IUpdater.h"


class NonRenderObject : public Object, public IUpdater {

public:
	void SetTranslate(float x, float y, float z);

	virtual void shutDown() override
	{
		Object::shutDown();
	}

	virtual void Update() override
	{
		int a = 0;
	}

};