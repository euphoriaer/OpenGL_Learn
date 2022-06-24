#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
