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

	//�ش� ��ü�� dds�� obj�� ������
}

void AddObject::render(RenderableObject* src)
{
	a.push_back(src);
	//�ش� ��ü�� ������ �� �� �ֵ��� �߰�����
}

//������Ʈ�� ������ ��. ������Ʈ�� ��ü�� ������ ������ ��ɵ��� �����ϴ� ��

//�� �ٿ��� escŰ�� �Է��� �Ǿ��� �� ���� �� �ִ� ��