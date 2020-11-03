#pragma once
#include "Object.h"

class RenderableObject : public Object {

public:
	RenderableObject();

	void SetTranslate(double x, double y, double z);
	void IsPatrol(float x, float y, float z);
	void SetObjectRange(double min_x, double max_x, double min_y, double max_y);
	void SetAlpha(float a);
	void IsGliter(RenderableObject* src, bool isgliter, double speed);

	virtual void shutDown() override 
	{
		Object::shutDown();
	}
};