#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "MastDrawer.h"
#include "SailDrawer.h"
#include "HullDrawer.h"
#include "RudderDrawer.h"
#include "WaterDrawer.h"

using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;

Camera camera;

//czas pomi�dzy kolejnymi klatkami
float deltaTime = 0.0f;			
float lastFrame = 0.0f;

glm::vec3 sailScale = glm::vec3(1.0f, 1.0f, 1.0f);
float sailRotation = -90.0f;

//obracanie kamery mysz�
bool firstMouse = true;
float lastX = WIDTH / 2.0;
float lastY = HEIGHT / 2.0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


//Obs�ug� klawiszy nawigacji musia�em opisa� w innej funkcji jawnie wywo�ywanej w g��wnej p�tli, bo w key_callback strasznie si� ci�o. 
void processInput(GLFWwindow *window)
{	
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		sailScale += glm::vec3(0.001f, 0.001f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		sailScale += glm::vec3(-0.001f, -0.001f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		sailRotation += 0.1f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		sailRotation -= 0.1f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.Keyboard(Camera::Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.Keyboard(Camera::Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.Keyboard(Camera::Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.Keyboard(Camera::Camera_Movement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.MouseMovement(xoffset, yoffset);
}


// ----------------------------------------------------------------------
//wywo�ywane podobnie jak key_callback wi�c nie trzeba jawnie wywo�ywa� w p�tli g��wnej
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.MouseScroll(yoffset);
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	//glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	//glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = SOIL_load_image(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			SOIL_free_image_data(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SOIL_free_image_data(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

ostream& operator<<(ostream& os, const glm::mat4& mx)
{
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
			cout << mx[row][col] << ' ';
		cout << endl;
	}
	return os;
}

int main()
{
	{
		glm::mat4 trans;
		cout << trans << endl;
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
		cout << trans << endl;
	}
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);	//brak mo�liwo��i zmiany rozmiaru okna
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 05", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		glfwSetKeyCallback(window, key_callback);

		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);	//Ustalenie obszaru okna w kt�rym b�dzie odbywa�o si� rysowanie (dolny lewy r�g, szeroko��, wysoko��)

		glEnable(GL_DEPTH_TEST);			//Aby elementy poprawnie si� przes�ania�y

		// Let's check what are maximum parameters counts
		GLint nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		cout << "Max vertex attributes allowed: " << nrAttributes << std::endl;
		glGetIntegerv(GL_MAX_TEXTURE_COORDS, &nrAttributes);
		cout << "Max texture coords allowed: " << nrAttributes << std::endl;

		// Build, compile and link shader program
		//ShaderProgram theProgram("gl_05.vert", "gl_05.frag");
		ShaderProgram theProgram("basic.vert", "basic.frag");
		//ShaderProgram skyboxShader("skybox.vert", "skybox.frag");

		MastDrawer mast;
		SailDrawer sail;
		HullDrawer hull;
		RudderDrawer rudder;
		WaterDrawer water;

		 // Set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "wood.jpg");
		GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "water.png");
		GLuint texture2 = LoadMipmapTexture(GL_TEXTURE1, "sail.jpg");

		theProgram.Use();
		theProgram.setInt("material.diffuse", 0);
		theProgram.setInt("material.specular", 1);


		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			processInput(window);

			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();	//przetwarza zdarzenia znajduj�ce si� w kolejce - wywo�ywane s� funkcje typu callback

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);	//ustawienie na jaki kolor b�dzie czyszczony bufor kolor�w (R, G, B, alpfa (0-przezroczyste, 1-nie))
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//czyszczenie bufor�w

			// Bind Textures using texture units

			//glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			//glBindTexture(GL_TEXTURE_2D, texture0);
			//glUniform1i(glGetUniformLocation(theProgram.get_programID(), "Texture0"), 0);

			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			theProgram.Use();

			glUniform3f(glGetUniformLocation(theProgram.get_programID(), "light.position"), 5.2f, 5.0f, 4.0f);
			glUniform3fv(glGetUniformLocation(theProgram.get_programID(), "viewPos"), 1, &camera.position[0]);

			// light properties
			glUniform3f(glGetUniformLocation(theProgram.get_programID(), "light.ambient"), 0.2f, 0.2f, 0.2f);
			glUniform3f(glGetUniformLocation(theProgram.get_programID(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
			glUniform3f(glGetUniformLocation(theProgram.get_programID(), "light.specular"), 1.0f, 1.0f, 1.0f);
			glUniform1f(glGetUniformLocation(theProgram.get_programID(), "light.constant"), 0.5f);
			glUniform1f(glGetUniformLocation(theProgram.get_programID(), "light.linear"), 0.09f);
			glUniform1f(glGetUniformLocation(theProgram.get_programID(), "light.quadratic"), 0.032f);
			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------
			glm::mat4 view;
			view = camera.GetViewMatrix();		//po�o�enie kamery, pkt na kt�ry patrzy, wektor normalny dla obserwatora
			glm::mat4 projection;
			projection = glm::perspective(glm::radians(camera.zoom), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);  //k�t widzenia = 45, stosunek przycinania, odleg�o�� do przedniej i tylnej �ciany przycinania

			
			glUniformMatrix4fv(glGetUniformLocation(theProgram.get_programID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(theProgram.get_programID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

			glm::mat4 trans = glm::mat4(1.0f);
			glUniformMatrix4fv(glGetUniformLocation(theProgram.get_programID(), "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

			// Draw our first triangle
			theProgram.Use();
			mast.draw(theProgram);
			hull.draw(theProgram);
			rudder.draw(theProgram);

			glBindTexture(GL_TEXTURE_2D, texture2);
			sail.setParameters(sailRotation, sailScale);
			sail.draw(theProgram);
			glBindTexture(GL_TEXTURE_2D, texture1);
			water.draw(theProgram);
			glBindTexture(GL_TEXTURE_2D, texture0);
			// SKYBOX

/*
			glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
			skyboxShader.Use();
			glUniformMatrix4fv(glGetUniformLocation(skyboxShader.get_programID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(glGetUniformLocation(skyboxShader.get_programID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
			// skybox cube
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
			glDepthFunc(GL_LESS); // set depth function back to default
*/
			// Swap the screen buffers
			glBindVertexArray(0);
			glfwSwapBuffers(window);	//Prze�aczenie bufor�w
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
