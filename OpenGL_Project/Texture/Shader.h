#pragma once

#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string fragmentString;
	std::string vertexString;

	const char* vertexSource;//Const ֻ��д��һ�Σ������޸�
	const char* fragmentSource;
	/// <summary>
	/// Shader PorgramID
	/// </summary>
	unsigned int	 ID;//Shader PorgramID;
	void Use();

private:
	void	CheckCompilerErrors(unsigned int ID, std::string type);
};
