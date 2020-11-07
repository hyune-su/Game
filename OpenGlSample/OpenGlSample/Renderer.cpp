#pragma once
#include "Renderer.h"

Renderer::Renderer()
{
	_targetFrame = 60;

	QueryPerformanceFrequency(&_frameInfo);
	QueryPerformanceCounter(&_prevFrameCounter);

	_perFrame = _frameInfo.QuadPart / _targetFrame;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		//return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1024, 768, "Tutorial 08 - Basic Shading", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		//return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		//return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR);
	
	glfwPollEvents();
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	SetShader("송현수_20161642_vs.shader", "송현수_20161642_fs.shader");

	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);

	ModelMatrix = glm::mat4(1.0);

	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
}

bool Renderer::isEND()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0)
	{
		return true;
	}
	else
	{
		glDeleteProgram(programID);
		glDeleteVertexArrays(1, &VertexArrayID);

		return false;
	}
}

bool Renderer::isRenderTiming()
{
	QueryPerformanceCounter(&_nowFrameCounter);

	LONGLONG time_distance = _nowFrameCounter.QuadPart - _prevFrameCounter.QuadPart;

	if (time_distance > _perFrame)
	{
		_prevFrameCounter = _nowFrameCounter;

		static int count = 0;

		if (count++ > _targetFrame)
		{
			count = 0;
		}

		return true;
	}
	return false;
}

void Renderer::GameStart()
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		isStart = true;
	}
}

void Renderer::isPhysicRender()
{
	if (isStart)
	{
		for (int i = 0; i < AddObject::instance()->a.size(); i++)
		{
			for (int j = 0; j < AddObject::instance()->a.size(); j++)
			{
				if (AddObject::instance()->a.at(i)->IsCharacter == true && AddObject::instance()->a.at(j)->IsCharacter == false)
				{
					if (AddObject::instance()->a.at(i)->object_pos.x - AddObject::instance()->a.at(j)->object_pos.x <= 2.0f
						&& AddObject::instance()->a.at(i)->object_pos.x - AddObject::instance()->a.at(j)->object_pos.x >= -2.0f
						&& AddObject::instance()->a.at(i)->object_pos.y - AddObject::instance()->a.at(j)->object_pos.y <= 2.0f
						&& AddObject::instance()->a.at(i)->object_pos.y - AddObject::instance()->a.at(j)->object_pos.y >= -2.0f)
					{
						AddObject::instance()->AddObject::instance()->a.at(j)->collision_check = true;
					}
					else
					{
						AddObject::instance()->AddObject::instance()->a.at(j)->collision_check = false;
					}
				}

				if(AddObject::instance()->a.at(i)->vertices.empty())
				{
					AddObject::instance()->a.at(i)->collision_check = false;
				}
			}

			if (AddObject::instance()->a.at(i)->IsCharacter)
			{
				if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
				{
					AddObject::instance()->a.at(i)->SetTranslate(0, AddObject::instance()->a.at(i)->y_speed, 0);
				}

				if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
				{
					AddObject::instance()->a.at(i)->SetTranslate(0, -AddObject::instance()->a.at(i)->y_speed, 0);
				}

				if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
				{
					AddObject::instance()->a.at(i)->SetTranslate(AddObject::instance()->a.at(i)->x_speed, 0, 0);
				}

				if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
				{
					AddObject::instance()->a.at(i)->SetTranslate(-AddObject::instance()->a.at(i)->x_speed, 0, 0);
				}
			}

			if (AddObject::instance()->a.at(i)->isMove)
			{
				AddObject::instance()->a.at(i)->IsPatrol(AddObject::instance()->a.at(i)->x_speed, AddObject::instance()->a.at(i)->y_speed, 0);
			}
		}
	}
}

void Renderer::computeMatricesFromInputs()
{
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();
	
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	
	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	
	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);
	
	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);
	
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle),
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross(right, direction);
	
	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= right * deltaTime * speed;
	}
	
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up AddObject::instance()->a callback for this. It's AddObject::instance()->a bit too complicated for this beginner's tutorial, so it's disabled instead.
	
						   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + direction, // and looks here : at the same position, plus "direction"
		up                 // Head is up (set to 0,-1,0 to look upside-down)
	);
	
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}

void Renderer::SetCamera_World(int x, int y, int z)
{
	cam_World = glm::vec3(x, y, z);
	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);
}

void Renderer::SetCamera_Lookat(int x, int y, int z)
{
	cam_Lookat = glm::vec3(x, y, z);
	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);
}

void Renderer::SetCamera_Headup(int x, int y, int z)
{
	cam_Headup = glm::vec3(x, y, z);
	ViewMatrix = glm::lookAt(cam_World, cam_Lookat, cam_Headup);
}

void Renderer::DrawObject(Object* src)
{
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix * src->Trans_Model;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, src->Texture);
	glUniform1i(TextureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, src->vertexbuffer);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, src->uvbuffer);
	glVertexAttribPointer(
		1,
		2,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, src->normalbuffer);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);

	//src->IsGliter(src, src->isGliter, src->gliter_speed);

	glUniform1f(LightID, src->alpha);

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, GLsizei(src->vertices.size()));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

GLuint Renderer::LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// 쉐이더들 생성
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// 버텍스 쉐이더 코드를 파일에서 읽기
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", vertex_file_path);
		getchar();
		return 0;
	}

	// 프래그먼트 쉐이더 코드를 파일에서 읽기
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// 버텍스 쉐이더를 컴파일
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// 프래그먼트 쉐이더를 컴파일
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// 프로그램에 링크
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// 프로그램 검사
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void Renderer::SetShader(const char* vs, const char* fs)
{
	VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	programID = LoadShaders(vs, fs);

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	LightID = glGetUniformLocation(programID, "Light");

	// Get a handle for our "myTextureSampler" uniform
	TextureID = glGetUniformLocation(programID, "myTextureSampler");
}