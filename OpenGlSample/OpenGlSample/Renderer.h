#pragma once
#include "FileManager.h"
#include "RenderableObject.h"
#include "SunObject.h"
#include "SphereObject.h"
#include "EnemyObject.h"
#include "IRender.h"

#include "AddObject.h"

#include <fstream>
#include <sstream>
#include <Windows.h>

class Renderer : public RenderableObject, public IRender {

private:
	glm::vec3 cam_World = glm::vec3(0, 0, 20);
	glm::vec3 cam_Lookat = glm::vec3(0, 0, 0);
	glm::vec3 cam_Headup = glm::vec3(0, 1, 0);

	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint TextureID;
	GLuint LightID;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

	// Initial position : on +Z
	glm::vec3 position = glm::vec3(2, 2, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	bool isRender = false;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;
	
	int _targetFrame;
	LARGE_INTEGER _frameInfo;
	LARGE_INTEGER _prevFrameCounter;
	LARGE_INTEGER _nowFrameCounter;
	LONGLONG _perFrame;

public:

	GLFWwindow* window;
	bool isStart = false;
	int Frame = 0;

	static Renderer* instance()
	{
		static Renderer _instance;

		return &_instance;
	}

	bool isEND();
	bool isRenderTiming();
	void SetWindow();
	void GameStart();
	void isPhysicRender(Object* src);
	void SetCamera_World(int x, int y, int z);
	void SetCamera_Lookat(int x, int y, int z);
	void SetCamera_Headup(int x, int y, int z);
	void DrawObject(Object* src);
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	void SetShader(const char* vs, const char* fs);

	virtual void Init() override
	{
		for (int i = 0; i < AddObject::instance()->All_obj.size(); i++)
		{
			AddObject::instance()->All_obj.at(i)->Init();
		}

		for (int i = 0; i < AddObject::instance()->Nonrender_obj.size(); i++)
		{
			if (AddObject::instance()->Nonrender_obj.at(i)->vertices.empty())
			{
				FileManager::instance()->GetData(AddObject::instance()->Nonrender_obj.at(i));
			}
		}

		for (int i = 0; i < AddObject::instance()->Render_obj.size(); i++)
		{
			if (AddObject::instance()->Render_obj.at(i)->vertices.empty())
			{
				//해당 객체의 버텍스가 비어있다면 데이터가 없는 것이므로 파일매니저에서 데이터를 받아와서 저장
				//렌더링 하지 않을 객체는? 업데이트만 할 객체는?
				FileManager::instance()->GetData(AddObject::instance()->Render_obj.at(i));
			}
		}
	}

	virtual void Update(RenderableObject* src) override
	{
		AddObject::instance()->update(src);
	}

	virtual void shutDown() override
	{
		Object::shutDown();

		glfwTerminate();
	}

	//화면 렌더링 부분과 객체 출력 부분을 나누기 >> 게임의 시작과 끝을 정할 수 있을 것 같음
	virtual void render() override
	{
		SetWindow();

		Init();

		do
		{
			glfwSwapBuffers(window);
			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(programID);

			if (!isStart)
			{
				GameStart();
			}

			for (int i = 0; i < AddObject::instance()->Render_obj.size(); i++)
			{
				if (!AddObject::instance()->Render_obj.at(i)->vertices.empty())
				{
					DrawObject(AddObject::instance()->Render_obj.at(i));
				}
			}

			if (isStart)
			{
				if (isRenderTiming())
				{
					for (int i = 0; i < AddObject::instance()->All_obj.size(); i++)
					{
						if (!AddObject::instance()->Render_obj.at(i)->vertices.empty())
						{
							isPhysicRender(AddObject::instance()->All_obj.at(i));
							Update(AddObject::instance()->All_obj.at(i));
						}
					}
				}
			}

		} while (isEND());

		for (int i = 0; i < AddObject::instance()->Nonrender_obj.size(); i++)
		{
			AddObject::instance()->Nonrender_obj.at(i)->shutDown();
		}

		for (int i = 0; i < AddObject::instance()->Render_obj.size(); i++)
		{
			AddObject::instance()->Render_obj.at(i)->shutDown();
		}

		shutDown();
	}
};