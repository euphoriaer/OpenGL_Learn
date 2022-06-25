#pragma once

#include <string>

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

private:
	void	CheckCompilerErrors(unsigned int ID, std::string type);  
};
