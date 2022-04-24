#include "Shader.h"
#include <fstream>
#include <iostream>
#include <string>
Shader::Shader()
	: 
	vertexContents(" "), fragmentContents(" "), shaderProgram(0)
{
	std::cout << "Default Constructor" << std::endl;
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
	:
	vertexContents(""), fragmentContents(""), shaderProgram(0)
{
	// Load Shader Files into a string
	loadShader(vertexPath, vertexContents);
	loadShader(fragmentPath, fragmentContents);
	const char* vertexSource = vertexContents.c_str();
	const char* fragmentSource = fragmentContents.c_str();
	

	// Vertex Shader Creation Stuff
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "FRAGMENT");

	// Fragment Shader Creation Stuff
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");


	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkCompileErrors(shaderProgram, "PROGRAM");
	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);

}

Shader::~Shader()
{

}


void Shader::loadShader(std::string path, std::string& contents)
{
	std::ifstream inFile(path);
	std::string line = "";
	if (!inFile)
	{
		std::cout << "Error, could not open file path" << path << std::endl;
	}
	while (std::getline(inFile, line))
	{
		contents += line + "\n";
	}
	inFile.close();
}

void Shader::use()
{
	glUseProgram(shaderProgram);
}

void Shader::setUniformFloat4f(std::string uniformName, glm::vec4 floats)
{
	glUniform4f(glGetUniformLocation(shaderProgram, uniformName.c_str()), floats.x, floats.y, floats.z, 1.0f);
}

void Shader::setUniformTex2f(std::string uniformName)
{
	glUniform1i(glGetUniformLocation(shaderProgram, uniformName.c_str()), 0);
}

void Shader::setUniformMat4f(std::string unifornName, glm::mat4 modelMatrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, unifornName.c_str()), 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

