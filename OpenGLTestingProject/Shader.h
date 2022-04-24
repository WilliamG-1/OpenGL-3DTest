#pragma once
#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader
{
public:
	GLuint shaderProgram;

	Shader();
	// Takes Two Parameters, the file path for the Vertex Shader and File path for Fragment Shader
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	void use();
    void setUniformFloat4f(std::string uniformName, glm::vec4 floats);
    void setUniformTex2f(std::string uniformName);
    void setUniformMat4f(std::string uniformName, glm::mat4 modelMatrix);
private:
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
	std::string vertexContents;
	std::string fragmentContents; 
    
	void loadShader(std::string path, std::string& contents);
    



    void checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

