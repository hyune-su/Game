#pragma once
#include "RenderableObject.h"
#include "IRender.h"
#include "IUpdater.h"

#include "AddObject.h"

#include <fstream>
#include <sstream>
#include <Windows.h>

class Renderer : public RenderableObject, public IRender {

private:
	glm::vec3 cam_World = glm::vec3(0, 0, 20);
	glm::vec3 cam_Lookat = glm::vec3(0, 0, 0);
	glm::vec3 cam_Headup = glm::vec3(0, 1, 0);

	GLFWwindow* window;
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

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	bool isStart = false;	
	int _targetFrame;
	LARGE_INTEGER _frameInfo;
	LARGE_INTEGER _prevFrameCounter;
	LARGE_INTEGER _nowFrameCounter;
	LONGLONG _perFrame;

public:
	Renderer();

	bool isEND();
	bool isRenderTiming();
	void GameStart();
	void isPhysicRender();
	void computeMatricesFromInputs();
	void SetCamera_World(int x, int y, int z);
	void SetCamera_Lookat(int x, int y, int z);
	void SetCamera_Headup(int x, int y, int z);
	void DrawObject(Object* src);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetShader(const char* vs, const char* fs);

	void hideObject(Object* src)
	{
		AddObject::instance()->a.clear();
	}

	void Update(IUpdater* src)
	{
		src->Update();
	}

	virtual void shutDown() override
	{
		Object::shutDown();

		glfwTerminate();
	}

	virtual void addObject(RenderableObject* src) override
	{

	}

	//화면 렌더링 부분과 객체 출력 부분을 나누기 >> 게임의 시작과 끝을 정할 수 있을 것 같음
	virtual void render() override
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		for (int i = 0; i < AddObject::instance()->a.size(); i++)
		{
			if (AddObject::instance()->a.at(i)->vertices.empty())
			{
				//해당 객체의 버텍스가 비어있다면 데이터가 없는 것이므로 파일매니저에서 데이터를 받아와서 저장
				//렌더링 하지 않을 객체는? 업데이트만 할 객체는?
				FileManager::instance()->GetData(AddObject::instance()->a.at(i));
			}
			else
			{
				//해당 객체의 버텍스가 비어있지 않다면 데이터가 있는 것이므로 해당 객체를 그려줌
				DrawObject(AddObject::instance()->a.at(i));
			}
		}

		if (!isStart)
		{
			GameStart();
		}
	}

};