#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int main();
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float vertices[] = {
    //位置                  //颜色               //纹理坐标
    0.5f,  0.5f, 0.0f,     1.0f,0.2f,0.9f,      1.0f,1.0f,
    0.5f, -0.5f, 0.0f,     1.0f,0.2f,0.4f,      1.0f,0.0f,
   -0.5f, -0.5f, 0.0f,     1.0f,0,0,            0.0f,0.0f,
   -0.5f,  0.5f, 0.0f,     0.1f,0.2f,0.8f,      0.0f,1.0f
};

unsigned    int indices[] =
{
   0,1,2,
   2,3,0

};

