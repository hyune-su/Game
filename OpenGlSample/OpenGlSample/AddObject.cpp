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

//�ش� ��ü�� dds�� obj�� ������
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
//�ش� ��ü�� ������ �� �� �ֵ��� �߰�����

void AddObject::update(RenderableObject* src)
{
	src->Update(src);
}
//������Ʈ�� ������ ��. ������Ʈ�� ��ü�� ������ ������ ��ɵ��� �����ϴ� ��

void AddObject::shutDown(RenderableObject* src)
{
	src->shutDown();
}
//�� �ٿ��� escŰ�� �Է��� �Ǿ��� �� ���� �� �ִ� ��