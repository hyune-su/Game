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