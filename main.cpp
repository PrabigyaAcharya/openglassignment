#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>


#include"shaders.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 800;

#pragma region unnecessary as separate file is created
//// Vertex Shader source code
//const char* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"layout (location = 1) in vec3 aColor;\n"
//
//"out vec3 color\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"	color = acolor\n"
//"}\0";
////Fragment Shader source code
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"in vec4 color\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(color, 1.0f);\n"
//"}\n\0";

//shaders are programs that run on gpu
//fragment shader outputs a vec4 color 

#pragma endregion

float vertices[] = {
		    // positions            // colors			//normals
	0.000000, 0.000000, -1.000000,	0.5f, 0.2f, 0.5f,	0.8402, 0.2425, -0.4851,
	0.000000, 2.000000, 0.000000,	0.5f, 0.2f, 0.5f,	0.8402, 0.2425, -0.4851,
	0.866025, 0.000000, 0.500000,	0.5f, 0.2f, 0.5f,	0.8402, 0.2425, -0.4851,

	0.000000, 0.000000, -1.000000,	0.5f, 0.2f, 0.5f,	0.0000, -1.0000, 0.0000,
	0.866025, 0.000000, 0.500000,	0.5f, 0.2f, 0.5f,	0.0000, -1.0000, 0.0000,
	-0.866025, 0.000000, 0.500000,	0.5f, 0.2f, 0.5f,	0.0000, -1.0000, 0.0000,

	0.866025, 0.000000, 0.500000,	0.5f, 0.2f, 0.5f,	-0.0000, 0.2425, 0.9701,
	0.000000, 2.000000, 0.000000,	0.5f, 0.2f, 0.5f,	-0.0000, 0.2425, 0.9701,
	-0.866025, 0.000000, 0.500000,	0.5f, 0.2f, 0.5f,	-0.0000, 0.2425, 0.9701,

	-0.866025, 0.000000, 0.500000,	0.5f, 0.2f, 0.5f,	-0.8402, 0.2425, -0.4851,
	0.000000, 2.000000, 0.000000,	0.5f, 0.2f, 0.5f,	-0.8402, 0.2425, -0.4851,
	0.000000, 0.000000, -1.000000,	0.5f, 0.2f, 0.5f,	-0.8402, 0.2425, -0.4851,
};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 5,
	1, 2, 5, 
	0, 1, 5
};

float lightcord[] = {
	0.7f, 0.7f, 0.0f,
	0.7f, 0.7f, -0.2f,
	0.7f,  0.9f, 0.0f,
	0.7f,  0.9f, -0.2f,
	0.5f, 0.7f, 0.0f,
	0.5f, 0.9f, 0.0f,
	0.5f, 0.9f, -0.2f,
	0.5f, 0.7f, -0.2f
};

GLuint lightindices[] = {
	0, 1, 2,
	1, 2, 3,
	0, 2, 5,
	0, 4, 5,
	2, 5, 6,
	2, 3, 6,
	4, 5, 7,
	7, 5, 6,
	7, 6, 3,
	7, 1, 3,
	0, 4, 7,
	0, 7, 1
};

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //hint to glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




	GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "hello", NULL, NULL);

	//error checking for window creation
	if (window == NULL) {
		std::cout << "Failed to initialize the window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//make the window part of the correct context
	glfwMakeContextCurrent(window);


	gladLoadGL();


	glViewport(0, 0, screen_width, screen_height);//render in the window available

	Shader shaderprogram("default.vert", "default.frag");
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttribute(VBO1, 2, 3, GL_FLOAT, 9 * sizeof(float), (void*)(6 * sizeof(float)));
   

	Shader lightshader("light.vert", "light.frag");
	VAO lVAO;
	lVAO.Bind();
	VBO lVBO(lightcord, sizeof(lightcord));
	EBO lEBO(lightindices, sizeof(lightindices));
	lVAO.LinkAttribute(lVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

	//glm::vec4 lightcolor = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
	//glUniform4f(glGetUniformLocation(lightshader.ID, "lightcolor"), lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);
	//glUniform4f(glGetUniformLocation(shaderprogram.ID, "lightcolor"), lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);

	//unbinding to prevent modification
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	lVAO.Unbind();
	lVBO.Unbind();
	lEBO.Unbind();

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);


	lightshader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightshader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightshader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderprogram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderprogram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderprogram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderprogram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	/*
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	*/
	glEnable(GL_DEPTH_TEST);

	Camera camera(screen_width, screen_height, glm::vec3(0.0f, 0.0f, 0.2f));

#pragma region unnecessay as shader class handles all this
	////create vertex shader object and get reference
	//GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//
	////attach vertex shader source to the vertex shader object
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//
	////compile the vertex shader into machine code
	//glCompileShader(vertexShader);

	////repeat the same process for fragment shader
	//GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	////create shader program and get its reference
	//GLuint shaderProgram = glCreateProgram();

	////attach the vertex shader and fragment shader to the shader program
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);

	////link all the shaders to the shader program
	//glLinkProgram(shaderProgram);

	////delete the vertex shader and fragment shader objects that are useless now
	//glDeleteShader(fragmentShader);
	//glDeleteShader(vertexShader);

	////binding, making some object the current object

	////create reference ccontainers for the vertex array object and vertex buffere object
	//GLuint VAO, VBO, EBO;

	////generate vao and vbo with only 1 object each
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	////make vao the current vertex object by binding it
	//glBindVertexArray(VAO);

	////bind the vbo specifying that it is a GL_BUFFER_ARRAY
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);


	////introduce the vertices into the vbo
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	////confiure the vertex attribute so that opengl knows how to read the vbo
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	////enable the vertex attribute so that opengl knows how to use it
	//glEnableVertexAttribArray(0);

	////bind both vbo and vao to zero to prevent accidental modification
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//specify the color of the background

	//glClear(GL_COLOR_BUFFER_BIT); //clean the back buffer and assign new color to it

	//glfwSwapBuffers(window); //swap the back bufffer with the front buffer

#pragma endregion

	while (!glfwWindowShouldClose(window)) {


		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);//specify the color of the background

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clean the back buffer and assign new color to it
		
		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		shaderprogram.Activate();
		/*
		double curnttime = glfwGetTime();
		if(curnttime - prevTime >= 1 / 60) {
			rotation += 0.1f;
			prevTime = curnttime;
		}
		*/
		camera.Matrix(shaderprogram, "cam");
#pragma region unnecessary because camera implemented
		////initialization of identity matrix
		////model matrix
		//glm::mat4 model = glm::mat4(1.0f);
		////view matrix
		//glm::mat4 view = glm::mat4(1.0f);
		////projection matrix
		//glm::mat4 proj = glm::mat4(1.0f);

		//model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.1f, 0.0f));
		//view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));//z axis is positive away from us
		//proj = glm::perspective(glm::radians(45.0f), (float)(screen_width / screen_height), 0.1f, 100.0f);

		//int modelLoc = glGetUniformLocation(shaderprogram.ID, "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//int viewLoc = glGetUniformLocation(shaderprogram.ID, "view");
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		//int projLoc = glGetUniformLocation(shaderprogram.ID, "proj");
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

#pragma endregion
		//bind tha vao
		VAO1.Bind();
		//draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);


		lightshader.Activate();
		camera.Matrix(lightshader, "cam");
		lVAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightindices) / sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderprogram.Delete();

	lVAO.Delete();
	lVBO.Delete();
	lEBO.Delete();
	lightshader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}