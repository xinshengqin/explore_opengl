#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Core\GameModels.h"
#include <iostream>
#include <fstream>
#include <vector>

#include "Core\Shader_Loader.h"

using namespace Core;

Models::GameModels* gameModels;
GLuint program;
GLuint vertex_array_object;


void renderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.3, 0.3, 1.0);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	//use the created program
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}
void closeCallback()
{

	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init()
{

	glEnable(GL_DEPTH_TEST);

	gameModels = new Models::GameModels();
	gameModels->CreateTriangleModel("triangle1");
	//load and compile shaders
	Core::Shader_Loader shaderLoader;
	program = shaderLoader.CreateProgram("Shaders\\Vertex_Shader.glsl",
		"Shaders\\Fragment_Shader.glsl");
	//generate the vertex array
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional
	glutCreateWindow("Drawing my first triangle");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glewInit();
	if (glewIsSupported("GL_VERSION_4_4"))
	{
		std::cout << " GLEW Version is 4.4\n ";
	}
	else
	{
		std::cout << "GLEW 4.4 not supported\n ";
	}
	std::cout << "OpenGL version is:\n" << glGetString(GL_VERSION) << std::endl;
	Init();

	// register callbacks
	glutDisplayFunc(renderScene);
	glutCloseFunc(closeCallback);
	glutMainLoop();
	delete gameModels;
	glDeleteProgram(program);
	return 0;
}