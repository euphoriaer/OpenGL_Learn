// HelloWindows.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <iostream>
#include <glad/glad.h>//管理opengl 函数指针，所以要在任何opengl 库之前引用
#include <GLFW/glfw3.h>

#include "main.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//opengl版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//opengl 管线 核心模式

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//窗口改变回调，第一次被创建时调用
    ////背面剔除
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);//深度测试
    Shader* shader = new Shader("vertexSource.vert", "fragmentSource.frag");

    //VAO Vertex Array Object
    unsigned	int	VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //VBO Vertex Buffer Object
    unsigned	int	VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//BindData

    //EBO Element Buffer Object
    unsigned	int	 EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//BindData

    //位置属性 Gluint =》shader layout
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);//启用 顶点属性位置

    ////顶点颜色
    //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(4);

    //uv
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(5);

    //TextureA
    unsigned   int TexbufferA;
    glGenTextures(1, &TexbufferA);
    glActiveTexture(GL_TEXTURE0);//激活0号贴图位置
    glBindTexture(GL_TEXTURE_2D, TexbufferA);

    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);//反转
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannel, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed" << std::endl;
    }
    stbi_image_free(data);

    //TextureB
    unsigned   int TexbufferB;
    glGenTextures(1, &TexbufferB);
    glActiveTexture(GL_TEXTURE3);//激活3号贴图位置
    glBindTexture(GL_TEXTURE_2D, TexbufferB);
    unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannel, 0);

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed" << std::endl;
    }
    stbi_image_free(data2);

    //Trans
    glm::mat4 trans = glm::mat4(1.0f);
    //trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0)); //位移
    //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0, 0, 1.0f));//旋转
    // trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));//缩放

    //mvp变换
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
    glm::mat4 viewMat = glm::mat4(1.0f);
    viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
    glm::mat4 projectMat = glm::mat4(1.0f);
    projectMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //渲染指令
        glActiveTexture(GL_TEXTURE0);//激活0号贴图位置
        glBindTexture(GL_TEXTURE_2D, TexbufferA);
        glActiveTexture(GL_TEXTURE3);//激活3号贴图位置
        glBindTexture(GL_TEXTURE_2D, TexbufferB);
        glBindVertexArray(VAO);

        //绘制多个物体
        for (size_t i = 0; i < 10; i++)
        {
            glm::mat4 modelMat2 = glm::mat4(1.0f);
            modelMat2 = glm::translate(modelMat2, cubePositions[i]);
            shader->Use();
            //激活贴图

            glUniform1i(glGetUniformLocation(shader->ID, "ourTexture"), 0);
            glUniform1i(glGetUniformLocation(shader->ID, "ourFace"), 3);
            //glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projectMat"), 1, GL_FALSE, glm::value_ptr(projectMat));
            //索引缓冲绘制
            //1.bind Buffer
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            //2.Draw
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}