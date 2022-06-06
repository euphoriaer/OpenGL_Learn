// OpenGL_Project.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "GLFW/glfw3.h"
#include "GL/gl3w.h"//https://blog.csdn.net/snail_hunan/article/details/115837263
#include "GL/GL.h"
using namespace std;
enum VAO_IDs
{
    Triangle, NumVAOs
};
enum Buffer_IDs
{
    ArrayBuffer, NumBuffers
};
enum Attrib_IDs
{
    vPosition = 0
};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;



void Init()
{
    static const GLfloat vertices[NumVertices][2] =
    {
        {-0.90,-0.90},
        {-0.85,-0.90},
        {-0.90,0.85},
        {-0.90,-0.85},
        {-0.90,0.90},
        {-0.85,0.90},
    };
    glCreateBuffers(NumBuffers, Buffers);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

}

void Display()
{

}

int main()
{
    std::cout << "Hello World!\n";
    glfwInit();
    GLFWwindow* windows = glfwCreateWindow(640, 480, "Triangles", NULL, NULL);
    glfwMakeContextCurrent(windows);
    gl3wInit();
    Init();
    while (!glfwWindowShouldClose(windows))
    {
        Display();
        glfwSwapBuffers(windows);
        glfwPollEvents();
    }
    glfwDestroyWindow(windows);
    glfwTerminate();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
