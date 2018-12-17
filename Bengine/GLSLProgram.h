#pragma once

#include <GL/glew.h>

#include <string>

namespace Bengine {
//This class handles the compilation, linking, and usage of a GLSL program
//Refernce: http://www.opengl.com/wiki/Shader_Compilation

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShaders(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string& attributeName);

	GLint getUnifromLocation(const std::string& uniformName);

	void use();
	void unuse();
private:
	int _numAttributes = 0;

	void compileShader(const std::string &filePath, GLuint id);

	GLuint _programID = 0;

	GLuint _vertexShaderID = 0;
	GLuint _fragmentShaderID = 0;
};

}