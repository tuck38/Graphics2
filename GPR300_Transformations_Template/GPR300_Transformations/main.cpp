#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>
#include <Time.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "EW/Shader.h"
#include "EW/ShapeGen.h"

#include "Source/Camera.h"

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height);
void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods);

float lastFrameTime;
float deltaTime;

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

double prevMouseX;
double prevMouseY;
bool firstMouseInput = false;

/* Button to lock / unlock mouse
* 1 = right, 2 = middle
* Mouse will start locked. Unlock it to use UI
* */
const int MOUSE_TOGGLE_BUTTON = 1;
const float MOUSE_SENSITIVITY = 0.1f;

glm::vec3 bgColor = glm::vec3(0);
float exampleSliderFloat = 0.0f;

const int numOfCubes = 5;

std::vector<Transform> cubes;

int main() {
	if (!glfwInit()) {
		printf("glfw failed to init");
		return 1;
	}

	Camera cam = Camera();

	srand(time(NULL));

	//creation of each cube

	Transform cube(glm::vec3(0), glm::vec3(0), glm::vec3(1, 1, 1));

	cubes.push_back(cube);

	for (int i = 0; i < numOfCubes - 1; i++)
	{
		Transform cube(glm::vec3((rand() % 10) - 5, (rand() % 10) - 5, (rand() % 10) - 5), glm::vec3(rand() % 360, rand() % 360, rand() % 360), glm::vec3(1));
		//Transform cube(glm::vec3(0), glm::vec3(0), glm::vec3(1));

		cubes.push_back(cube);
	}

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Transformations", 0, 0);
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		printf("glew failed to init");
		return 1;
	}

	glfwSetFramebufferSizeCallback(window, resizeFrameBufferCallback);
	glfwSetKeyCallback(window, keyboardCallback);

	// Setup UI Platform/Renderer backends
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//Dark UI theme.
	ImGui::StyleColorsDark();

	Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

	MeshData cubeMeshData;
	createCube(1.0f, 1.0f, 1.0f, cubeMeshData);

	Mesh cubeMesh(&cubeMeshData);

	//Enable back face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(bgColor.r,bgColor.g,bgColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		float time = (float)glfwGetTime();
		deltaTime = time - lastFrameTime;
		lastFrameTime = time;

		//Draw
		shader.use();

		shader.setMat4("_CamProj", cam.getProjectionMatrix());

		shader.setMat4("_CamView", cam.getViewMatrix());

		for (int i = 0; i < cubes.size(); i++)
		{
			shader.setMat4("_Cube", cubes[i].getModelMatrix());

			cubeMesh.draw();
		}

		//Draw UI
		ImGui::Begin("Settings");
		ImGui::SliderFloat("Orbit Radius", &cam.radius, 1.0f, 100.0f);
		ImGui::SliderFloat("Orbit", &cam.speed, 0.0f, 6.30f);
		ImGui::SliderFloat("FOV", &cam.fov, 1.0f, 180.0f);
		ImGui::SliderFloat("Ortho Size", &cam.orthographicSize, 0.0f, 100.0f);
		ImGui::Checkbox("Ortho", &cam.orthographic);
		ImGui::End();

		ImGui::Begin("Cube 1");

		ImGui::SliderFloat("position x", &cubes[0].position.x, -10.0f, 10.0f);
		ImGui::SliderFloat("position y", &cubes[0].position.y, -10.0f, 10.0f);
		ImGui::SliderFloat("position z", &cubes[0].position.z, -10.0f, 10.0f);

		ImGui::SliderFloat("rotation x", &cubes[0].rotation.x, 0.f, 6.30f);
		ImGui::SliderFloat("rotation y", &cubes[0].rotation.y, 0.f, 6.30f);
		ImGui::SliderFloat("rotation z", &cubes[0].rotation.z, 0.f, 6.30f);

		ImGui::SliderFloat("scale x", &cubes[0].scale.x, 0.f, 10.f);
		ImGui::SliderFloat("scale y", &cubes[0].scale.y, 0.f, 10.f);
		ImGui::SliderFloat("scale z", &cubes[0].scale.z, 0.f, 10.f);

		ImGui::End();

		ImGui::Begin("Cube 2");

		ImGui::SliderFloat("position x", &cubes[1].position.x, -10.0f, 10.0f);
		ImGui::SliderFloat("position y", &cubes[1].position.y, -10.0f, 10.0f);
		ImGui::SliderFloat("position z", &cubes[1].position.z, -10.0f, 10.0f);

		ImGui::SliderFloat("rotation x", &cubes[1].rotation.x, 0.f, 6.30f);
		ImGui::SliderFloat("rotation y", &cubes[1].rotation.y, 0.f, 6.30f);
		ImGui::SliderFloat("rotation z", &cubes[1].rotation.z, 0.f, 6.30f);

		ImGui::SliderFloat("scale x", &cubes[1].scale.x, 0.f, 10.f);
		ImGui::SliderFloat("scale y", &cubes[1].scale.y, 0.f, 10.f);
		ImGui::SliderFloat("scale z", &cubes[1].scale.z, 0.f, 10.f);

		ImGui::End();

		ImGui::Begin("Cube 3");


		ImGui::SliderFloat("position x", &cubes[2].position.x, -10.0f, 10.0f);
		ImGui::SliderFloat("position y", &cubes[2].position.y, -10.0f, 10.0f);
		ImGui::SliderFloat("position z", &cubes[2].position.z, -10.0f, 10.0f);

		ImGui::SliderFloat("rotation x", &cubes[2].rotation.x, 0.f, 6.30f);
		ImGui::SliderFloat("rotation y", &cubes[2].rotation.y, 0.f, 6.30f);
		ImGui::SliderFloat("rotation z", &cubes[2].rotation.z, 0.f, 6.30f);

		ImGui::SliderFloat("scale x", &cubes[2].scale.x, 0.f, 10.f);
		ImGui::SliderFloat("scale y", &cubes[2].scale.y, 0.f, 10.f);
		ImGui::SliderFloat("scale z", &cubes[2].scale.z, 0.f, 10.f);

		ImGui::End();

		ImGui::Begin("Cube 4");


		ImGui::SliderFloat("position x", &cubes[3].position.x, -10.0f, 10.0f);
		ImGui::SliderFloat("position y", &cubes[3].position.y, -10.0f, 10.0f);
		ImGui::SliderFloat("position z", &cubes[3].position.z, -10.0f, 10.0f);

		ImGui::SliderFloat("rotation x", &cubes[3].rotation.x, 0.f, 6.30f);
		ImGui::SliderFloat("rotation y", &cubes[3].rotation.y, 0.f, 6.30f);
		ImGui::SliderFloat("rotation z", &cubes[3].rotation.z, 0.f, 6.30f);

		ImGui::SliderFloat("scale x", &cubes[3].scale.x, 0.f, 10.f);
		ImGui::SliderFloat("scale y", &cubes[3].scale.y, 0.f, 10.f);
		ImGui::SliderFloat("scale z", &cubes[3].scale.z, 0.f, 10.f);

		ImGui::End();

		ImGui::Begin("Cube 5");


		ImGui::SliderFloat("position x", &cubes[4].position.x, -10.0f, 10.0f);
		ImGui::SliderFloat("position y", &cubes[4].position.y, -10.0f, 10.0f);
		ImGui::SliderFloat("position z", &cubes[4].position.z, -10.0f, 10.0f);

		ImGui::SliderFloat("rotation x", &cubes[4].rotation.x, 0.f, 6.30f);
		ImGui::SliderFloat("rotation y", &cubes[4].rotation.y, 0.f, 6.30f);
		ImGui::SliderFloat("rotation z", &cubes[4].rotation.z, 0.f, 6.30f);

		ImGui::SliderFloat("scale x", &cubes[4].scale.x, 0.f, 10.f);
		ImGui::SliderFloat("scale y", &cubes[4].scale.y, 0.f, 10.f);
		ImGui::SliderFloat("scale z", &cubes[4].scale.z, 0.f, 10.f);

		ImGui::End();

		cam.update();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();

		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

void resizeFrameBufferCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}

void keyboardCallback(GLFWwindow* window, int keycode, int scancode, int action, int mods)
{
	if (keycode == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}