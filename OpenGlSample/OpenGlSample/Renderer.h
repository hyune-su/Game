#pragma once
#include "FileManager.h"
#include "Object.h"
#include "IRender.h"
#include "IUpdater.h"
#include <Windows.h>

class Renderer : public RenderableObject, public IRender {

private:
	std::vector<RenderableObject*> a;

	glm::vec3 cam_World = glm::vec3(0, 5, 7);
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
	void DrawObject(RenderableObject* src);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void SetShader(const char* vs, const char* fs);

	void hideObject(RenderableObject* src)
	{
		a.clear();
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
		a.push_back(src);
	}

	//화면 렌더링 부분과 객체 출력 부분을 나누기 >> 게임의 시작과 끝을 정할 수 있을 것 같음
	virtual void render() override
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		for (int i = 0; i < a.size(); i++)
		{
			if (!a.at(i)->vertices.empty())
			{
				DrawObject(a.at(i));
			}
		}

		if (!isStart)
		{
			GameStart();
		}
	}

};