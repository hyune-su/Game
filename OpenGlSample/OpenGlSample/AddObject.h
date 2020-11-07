#pragma once
#include "RenderableObject.h"
#include "FileManager.h"

using namespace std;

class AddObject
{
public:
	std::vector<RenderableObject*> a;
	std::vector<const char*> b;
	std::vector<const char*> c;

	static AddObject* instance();

	void init(RenderableObject* src, const char* dds, const char* obj);
	void render(RenderableObject* src);
};