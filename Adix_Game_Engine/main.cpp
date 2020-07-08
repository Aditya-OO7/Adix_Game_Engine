#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"Model.h"

#include<iostream>
#include<Windows.h>

#include"Shader.h"
#include"Texture.h"
#include"Camera.h"
#include"VertexArray.h"
#include"MVP.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const unsigned int FLOOR_WIDTH = 10;
const unsigned int FLOOR_HEIGHT = 10;

Camera camera(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), YAW, PITCH);
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
double deltaTime = 0.0f;
double lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void Lights(Shader &shader, glm::vec3 pointPos[], glm::vec3 colors[]);

enum CubeFace
{
	LEFT_FACE = 0, RIGHT_FACE = 6, FRONT_FACE = 12, BACK_FACE = 18, TOP_FACE = 30, BOTTOM_FACE = 24
};

int main()
{
	//Initializes glfw and OpenGL.
	glfwInit();
	//set major and minor version of openGl being used in this project and profile being set.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // major version is set to 3.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // minor version is set to 3.0
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // core profile is used

	//creates object of window;
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", NULL, NULL);

	//check if window is created correctly or error has occured.
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		//terminates the glfw and openGL.
		glfwTerminate();
		return -1;
	}
	//sets window as current context.
	glfwMakeContextCurrent(window);

	//initialize  GLAD and check for error.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);

	//Shader SHADER("res/Shaders/shader.vs", "res/Shaders/shader.fs");
	Shader lightingShader("res/Shaders/LightShaders/shader_c.vs", "res/Shaders/LightShaders/shader_c.fs");
	//Shader lightCubeShader("res/Shaders/LightShaders/shader_ls.vs", "res/Shaders/LightShaders/shader_ls.fs");
	//Shader modelShader("res/Shaders/ModelShaders/shader_m.vs", "res/Shaders/ModelShaders/shader_m.fs");
	
	MVP MVPLight(lightingShader);
	//MVP MVPLightCube(lightCubeShader);

	//Model ourModel("res/Models/backpack/backpack.obj");

	//set callback function for change in size of window.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int nAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAttributes);
	std::cout << "Maximum number of vertex attributes supported : " << nAttributes << std::endl;

	float vertices[] = {
		// positions         // normals          // texture coords

		//LEFT FACE :
	   -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
	   -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

	   //RIGHT FACE :
	   -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
	   -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
	   -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

		//FRONT FACE :
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

	   //BACK FACE :
		0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

		//BOTTOM FACE :
	   -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
	   -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,   0.0f, 1.0f,

	   //TOP FACE :
	   -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
	   -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
	   -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,   0.0f, 1.0f
	};
	unsigned int indices[] = {
		 0,  1,  2,  2,  3,  0, //1
		 4,  5,  6,  6,  7,  4,	//2
		 8,  9, 10, 10,  4,  8,	//3
		11,  2, 12, 12, 13, 11,	//4
		10, 14,  5,  5,  4, 10,	//5
		 3,  2, 11, 11, 15,  3	//6
	};
	
	VertexArray cubeVAO;
	unsigned int VBO;
	
	VBO = cubeVAO.AddVertexBufferObject(sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	VertexArray lightCubeVAO;
	lightCubeVAO.BindBuffer(Buffer::VERTEX_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Texture floor("res/Textures/marble.jpg", GL_REPEAT, GL_LINEAR);
	Texture wall("res/Textures/brickwall.jpg", GL_REPEAT, GL_LINEAR);
	
	//Texture diffuseMap("res/Textures/container2.png", GL_REPEAT, GL_LINEAR);
	//Texture specularMap("res/Textures/container2_specular.png", GL_REPEAT, GL_LINEAR);

/*
	lightingShader.use();
	lightingShader.setInt("material.diffuse", 0);
	lightingShader.setInt("material.specular", 1);

*/
	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f,  0.2f,   2.0f),
		glm::vec3(2.3f, -3.3f,  -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3(0.0f,  0.0f,  -3.0f)
	};

	float r = 44.0f / 255;
	float g = 12.0f / 255;
	float b = 148.0f / 255;

	glm::vec3 PointLightColors[] = {
		glm::vec3(0.6f, 0.0f, 0.0f),
		glm::vec3(0.6f, 0.0f, 0.0f),
		glm::vec3(r, g, b),
		glm::vec3(r, g, b)
	};

	double lastTime = glfwGetTime();
	int nbFrames = 0;
	double msPerF = 0;
	double fpsSixty = 16.666667;
	//main loop :
	while (!glfwWindowShouldClose(window))
	{
		//FPS limiter (current 60fps) :
		if (msPerF < fpsSixty)
		{
			Sleep(fpsSixty - msPerF);
		}

		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		nbFrames++;
		if (currentFrame - lastTime >= 1.0)
		{
			msPerF = 1000.0 / (double)nbFrames;
			std::cout << msPerF << " ms/frame" << std::endl;
			msPerF = 0;
			nbFrames = 0;
			lastTime += 1.0;
		}


		//process input in window.
		processInput(window);

		if (camera.Position.x > FLOOR_WIDTH - 1)
		{
			camera.Position.x = FLOOR_WIDTH - 1;
		}
		if (camera.Position.x < 0.0f)
		{
			camera.Position.x = 0.0f;
		}
		if (camera.Position.z > FLOOR_HEIGHT - 1)
		{
			camera.Position.z = FLOOR_HEIGHT - 1;
		}
		if (camera.Position.z < 0.0f)
		{
			camera.Position.z = 0.0f;
		}
		//clear color buffer with given color.
		//glClearColor(0.08f, 0.08f, 0.08f, 0.08f);
		glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightingShader.use();
/*
		lightingShader.setFloat("material.shininess", 32.0f);
		lightingShader.setVec("viewPos", camera.Position);

		Lights(lightingShader, pointLightPositions, PointLightColors);

		diffuseMap.Bind(GL_TEXTURE0);
		specularMap.Bind(GL_TEXTURE1);

*/
		floor.Bind(GL_TEXTURE0);

		MVPLight.Projection(camera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
		MVPLight.View(camera.GetViewMatrix());

/*
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		int modelLoc = glGetUniformLocation(modelShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		ourModel.Draw(modelShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(5.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		modelLoc = glGetUniformLocation(modelShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		ourModel.Draw(modelShader);
*/

		cubeVAO.Bind();
		float angle = 0.0f;
		float floorOffsetX = 0.0f;
		float floorOffsetZ = 0.0f;
		for (unsigned int i = 0; i < FLOOR_WIDTH; i++)
		{
			for (unsigned int j = 0; j < FLOOR_HEIGHT; j++)
			{
				if (i == 0)
				{
					wall.Bind(GL_TEXTURE0);
					MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
					glDrawArrays(GL_TRIANGLES, FRONT_FACE, 6);
					floor.Bind(GL_TEXTURE0);
					if (i == 0 && j == 0)
					{
						wall.Bind(GL_TEXTURE0);
						MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
						glDrawArrays(GL_TRIANGLES, LEFT_FACE, 6);
						floor.Bind(GL_TEXTURE0);
					}
					if (i == 0 && j == FLOOR_WIDTH - 1)
					{
						wall.Bind(GL_TEXTURE0);
						MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
						glDrawArrays(GL_TRIANGLES, RIGHT_FACE, 6);
						floor.Bind(GL_TEXTURE0);
					}
				}
				else if (i == FLOOR_HEIGHT - 1)
				{
					wall.Bind(GL_TEXTURE0);
					MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
					glDrawArrays(GL_TRIANGLES, BACK_FACE, 6);
					floor.Bind(GL_TEXTURE0);

					if (i == FLOOR_HEIGHT - 1 && j == 0)
					{
						wall.Bind(GL_TEXTURE0);
						MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
						glDrawArrays(GL_TRIANGLES, LEFT_FACE, 6);
						floor.Bind(GL_TEXTURE0);
					}
					if (i == FLOOR_HEIGHT - 1 && j == FLOOR_WIDTH - 1)
					{
						wall.Bind(GL_TEXTURE0);
						MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
						glDrawArrays(GL_TRIANGLES, RIGHT_FACE, 6);
						floor.Bind(GL_TEXTURE0);
					}
				}
				else if (j == FLOOR_WIDTH - 1)
				{
					wall.Bind(GL_TEXTURE0);
					MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
					glDrawArrays(GL_TRIANGLES, RIGHT_FACE, 6);
					floor.Bind(GL_TEXTURE0);
				}
				else if (j == 0)
				{
					wall.Bind(GL_TEXTURE0);
					MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
					glDrawArrays(GL_TRIANGLES, LEFT_FACE, 6);
					floor.Bind(GL_TEXTURE0);
				}

				MVPLight.Model(glm::vec3(floorOffsetX, 0.0f, floorOffsetZ), angle, glm::vec3(1.0f, 0.3f, 0.5f));
				glDrawArrays(GL_TRIANGLES, 24, 6);
				floorOffsetZ += 1.0f;
			}
			floorOffsetZ = 0.0f;
			floorOffsetX += 1.0f;
		}


/*
		lightCubeShader.use();
		MVPLight.Projection(camera.Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
		MVPLight.View(camera.GetViewMatrix());

		for (unsigned int i = 0; i < 4; i++)
		{
			MVPLight.Model(pointLightPositions[i], glm::vec3(0.2f));
			lightCubeShader.setVec("Color", PointLightColors[i]);

			lightCubeVAO.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
*/

		VertexArray::UnBind();
		Texture::UnBind();
		//double buffers are used to give smooth effect of graphics, so swap them.
		glfwSwapBuffers(window);
		//check if any event occured. Also, can be used for process input.
		glfwPollEvents();
	}

	//Terminate glfw and OpenGL.
	glfwTerminate();
	return 0;
}

/*
	processInput is used to process user input.
*/
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//set glfwWindowShouldClose as true which tell glfwWindowShouldClose to close when it is called.
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	}
}

void Lights(Shader &shader, glm::vec3 pointPos[], glm::vec3 colors[])
{
	// DIRECTION LIGHT :
	shader.setVec("dirLight.direction", -0.2f, -1.0f, -0.3f);
	shader.setVec("dirLight.ambient", 0.2f, 0.2f, 0.2f);
	shader.setVec("dirLight.diffuse", 0.5f, 0.5f, 0.5f);
	shader.setVec("dirLight.specular", 1.0f, 1.0f, 1.0f);

	// POINT LIGHTS :
	for (unsigned int i = 0; i < 4; i++)
	{
		string num = to_string(i);
		shader.setVec(("pointLights[" + num + "].lightColor").c_str(), colors[i]);
		shader.setVec(("pointLights[" + num + "].position").c_str(), pointPos[i]);
		shader.setFloat(("pointLights[" + num + "].constant").c_str(), 1.0f);
		shader.setFloat(("pointLights[" + num + "].linear").c_str(), 0.09f);
		shader.setFloat(("pointLights[" + num + "].quadratic").c_str(), 0.032f);
		shader.setVec(("pointLights[" + num + "].ambient").c_str(), 0.2f, 0.2f, 0.2f);//ambientColor.x, ambientColor.y, ambientColor.z);
		shader.setVec(("pointLights[" + num + "].diffuse").c_str(), 0.5f, 0.5f, 0.5f);//diffuseColor.x, diffuseColor.y, diffuseColor.z);
		shader.setVec(("pointLights[" + num + "].specular").c_str(), 1.0f, 1.0f, 1.0f);
	}

	// SPOT LIGHT :
	shader.setVec("spotLight.position", camera.Position);
	shader.setVec("spotLight.direction", camera.Front);
	shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
	shader.setVec("spotLight.ambient", 0.2f, 0.2f, 0.2f);//ambientColor.x, ambientColor.y, ambientColor.z);
	shader.setVec("spotLight.diffuse", 0.9f, 0.9f, 0.9f);//diffuseColor.x, diffuseColor.y, diffuseColor.z);
	shader.setVec("spotLight.specular", 1.0f, 1.0f, 1.0f);

}

/*
	framebuffer_size_callback is called by glfwSetFramebufferSizeCallback() when size of window changes.
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xOffset, yOffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}
