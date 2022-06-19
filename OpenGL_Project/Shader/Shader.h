#pragma once
int main();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float vertices[] = {
    -0.5f, -0.5f, 0.0f,/*vertex color*/1.0f,0.2f,0.9f,
     0.5f, -0.5f, 0.0f,/*vertex color*/1.0f,0.2f,0.4f,
     0.5f,  0.5f, 0.0f,/*vertex color*/1.0f,0,0,
     -0.5f,  0.5f, 0.0f,/*vertex color*/0.1f,0.2f,0.8f
};

unsigned    int indices[] =
{
   0,1,2,
   0,2,3

};

unsigned	int	fragmentShader;
unsigned	int	vertexShader;
unsigned	int	shaderProgram;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 3) in vec3 aPos;\n"
"layout (location = 4) in vec3 aColor;\n"
"out vec4 vertexcolor;\n "
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   vertexcolor =vec4(aColor.x,aColor.y,aColor.z,1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec4 vertexcolor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexcolor;\n"
"}\n\0";