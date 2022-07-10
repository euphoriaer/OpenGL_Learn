#pragma once
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:

    Shader(const char* vertexPath, const char* fragmentPath);
    std::string fragmentString;
    std::string vertexString;

    const char* vertexSource;//Const 只能写入一次，不能修改
    const char* fragmentSource;
    /// <summary>
    /// Shader PorgramID
    /// </summary>
    unsigned int	 ID;//Shader PorgramID;
    void Use();
    void SetUniform3f(const char* paramNameString, glm::vec3 param);
    void SetUniform1f(const char* paramNameString, float param);
private:
    void	CheckCompilerErrors(unsigned int ID, std::string type);
};
