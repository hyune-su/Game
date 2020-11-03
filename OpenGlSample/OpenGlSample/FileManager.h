#pragma once
#include <iostream>

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <stdlib.h>

#include "SphereObject.h"
#include "makeObject.h"
#include "NonRenderObject.h"

#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

class FileManager {

struct PackedVertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec3 normal;
	bool operator<(const PackedVertex that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
	};
};

private:

public:
	bool getSimilarVertexIndex_fast(
		PackedVertex & packed,
		std::map<PackedVertex, unsigned short> & VertexToOutIndex,
		unsigned short & result);

	void indexVBO(
		std::vector<glm::vec3> & in_vertices,
		std::vector<glm::vec2> & in_uvs,
		std::vector<glm::vec3> & in_normals,

		std::vector<unsigned short> & out_indices,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals);

	bool loadOBJ(
		const char * path,
		std::vector<glm::vec3> & out_vertices,
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals);

	GLuint LoadDDS(const char * imagepath);
	GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);

	void GetData(RenderableObject* src, const char* obj, const char* dds);
	void GetData(NonRenderObject* src, const char* obj, const char* dds);

	void SetObjectRange(RenderableObject* src, float min_x, float max_x, float min_y, float max_y);
	void SetObject(RenderableObject* src, double x, double y, double z);
	void SetObject(NonRenderObject* src, float x, float y, float z);
	void RandomSetObject(RenderableObject* src, int min_x, int max_x, int min_y, int max_y);
	void SetAlpha(RenderableObject* src, float a);
	void IsGliter(RenderableObject* src, bool isgliter, double speed);
	void SetCharacter(RenderableObject* src);

	void Moving(RenderableObject* src, double x_speed, double y_speed);

};