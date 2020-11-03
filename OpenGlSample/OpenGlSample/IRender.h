#pragma once

class IRender
{
public:
	virtual void render() = 0;
	virtual void addObject(RenderableObject* src) = 0;
};