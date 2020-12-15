#pragma once
#include "RenderableObject.h"

using namespace std;

class AddObject
{
public:
	std::vector<RenderableObject*> All_obj;
	std::vector<RenderableObject*> Render_obj;
	std::vector<RenderableObject*> Nonrender_obj;

	static AddObject* instance()
	{
		static AddObject _instance;
		
		return &_instance;
	}

	void init(RenderableObject* src, const char* dds, const char* obj);
	void Add(RenderableObject* me, const char* name);
	void render(RenderableObject* src);
	void update(RenderableObject* src);
	void shutDown(RenderableObject* src);
};