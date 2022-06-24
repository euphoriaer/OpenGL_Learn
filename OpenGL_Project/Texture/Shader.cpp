#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>//管理opengl 函数指针，所以要在任何opengl 库之前引用
#include <GLFW/glfw3.h>
using namespace std;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);

	vertexFile.exceptions(ifstream::failbit || fstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || fstream::badbit);

	try
	{
		if ((!vertexFile.is_open()) || (!fragmentFile.is_open()))
		{
			throw exception("Open File Error");
		}
		//file Stream->String Stream
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();
		//String Stream->string
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		//String -> char*  //C++风格字符串转 C风格字符串
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//vertex
		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		CheckCompilerErrors(vertex, "vertex");

		//fragment
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		CheckCompilerErrors(fragment, "fragment");


		//shader program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		//link
		glLinkProgram(ID);
		CheckCompilerErrors(ID, "Program");

		//Delete
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		cout << ex.what();
	}
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::CheckCompilerErrors(unsigned int id, std::string type)
{
	int	success;
	char infoLog[512];

	if (type != "Program")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			cout << "Shader compile Error:" << infoLog << endl;
		}

	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 512, NULL, infoLog);
			cout << "Shader Link Error:" << infoLog << endl;
		}
	}

}