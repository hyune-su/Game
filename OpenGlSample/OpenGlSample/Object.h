#pragma once
#include "ICleanUp.h"

#include <vector>

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Object : public ICleanUp {

private:

public:
	Object* parent;

	bool res;
	bool isRender = true;
	bool isData = false;
	bool isPlus = false;
	bool out_Area = false;
	bool collision_check = false;
	bool isMove = false;
	bool isAdded = false;
	bool isDead = false;

	//오류를 위한 기본 에셋
	const char* name = "오브젝트";
	const char* collision_name = "충돌한 객체";
	const char* dds = "태양.DDS";
	const char* obj = "sphere.obj";

	double alpha = 1.0;
	double x_speed = 0.15;
	double y_speed = 0.15;
	double gliter_speed;
	float Theta = 0.0f;
	glm::vec3 object_pos = glm::vec3(0, 0, 0);
	glm::vec3 world_pos = glm::vec3(0, 0, 0);

	float object_x = 0;

	GLuint Texture;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	glm::mat4 Scale_Model = glm::mat4(1.0);
	glm::mat4 Move_Model = glm::mat4(1.0);

	virtual void shutDown() override
	{
		vertices.clear();
		uvs.clear();
		normals.clear();

		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteBuffers(1, &normalbuffer);

		glDeleteTextures(1, &Texture);

		isDead = true;
	}
};