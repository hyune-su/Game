#pragma once
#include <vector>
#include "ICleanUp.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Object : public ICleanUp {

private:

public:
	bool res;
	bool isPlus = false;
	bool isGliter = false;
	bool IsCharacter = false;
	bool out_Area = false;
	bool collision_check = false;
	bool isMove = false;

	double alpha = 1.0;
	double x_speed = 0.15;
	double y_speed = 0.15;
	double gliter_speed;
	double area_min_x = -INFINITY;
	double area_max_x = INFINITY;
	double area_min_y = -INFINITY;
	double area_max_y = INFINITY;
	glm::vec3 object_pos = glm::vec3(0, 0, 0);

	GLuint Texture;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	glm::mat4 Trans_Model = glm::mat4(1.0);

	virtual void shutDown() override
	{
		vertices.clear();
		uvs.clear();
		normals.clear();

		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteBuffers(1, &normalbuffer);

		glDeleteTextures(1, &Texture);
	}
};