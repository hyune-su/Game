#pragma once
#include "Object.h"

class RenderableObject : public Object {

public:
	RenderableObject();

	void SetScale(float x, float y, float z);

	void SetPosition(float x, float y, float z);

	void SetTranslate(float x, float y, float z);
	void SetRotate(float rad, float _x, float _y, float _z);
	void IsPatrol(float x, float y, float z);
	void SetAlpha(float a);
	void IsGliter(RenderableObject* src, double speed);

	virtual void Init() = 0;

	virtual void Update(RenderableObject* src) = 0;

	virtual void shutDown() override
	{
		Object::shutDown();
	}
};