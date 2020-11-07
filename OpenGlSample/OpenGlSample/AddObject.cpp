#pragma once
#include "AddObject.h"

AddObject* AddObject::instance()
{
	static AddObject _instance;

	return &_instance;
}

void AddObject::init(RenderableObject* src, const char* dds, const char* obj)
{
	src->dds = dds;
	src->obj = obj;

	//해당 객체의 dds와 obj를 저장함
}

void AddObject::render(RenderableObject* src)
{
	a.push_back(src);
	//해당 객체를 렌더링 할 수 있도록 추가해줌
}

//업데이트를 만들어야 함. 업데이트는 객체의 움직임 관련한 기능들을 관리하는 것

//셧 다운은 esc키가 입력이 되었을 때 해줄 수 있는 것