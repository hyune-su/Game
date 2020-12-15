#pragma once
#include "AddObject.h"

void AddObject::init(RenderableObject* src, const char* dds, const char* obj)
{
	src->dds = dds;
	src->obj = obj;
}

void AddObject::Add(RenderableObject* me, const char* name)
{
	for (int i = 0; i < All_obj.size(); i++)
	{
		if (All_obj.at(i)->name == name)
		{
			me->isAdded = true;

			me->parent = All_obj.at(i);

			me->object_pos += All_obj.at(i)->object_pos;
		}
	}
}

//해당 객체의 dds와 obj를 저장함
void AddObject::render(RenderableObject* src)
{
	All_obj.push_back(src);

	if (src->isRender)
	{
		Render_obj.push_back(src);
	}
	else
	{
		Nonrender_obj.push_back(src);
	}
}
//해당 객체를 렌더링 할 수 있도록 추가해줌

void AddObject::update(RenderableObject* src)
{
	src->Update(src);
}
//업데이트를 만들어야 함. 업데이트는 객체의 움직임 관련한 기능들을 관리하는 것

void AddObject::shutDown(RenderableObject* src)
{
	src->shutDown();
}
//셧 다운은 esc키가 입력이 되었을 때 해줄 수 있는 것