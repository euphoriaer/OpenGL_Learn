// HelloWindows.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "main.h"
#include "Camera.h"

unsigned   int LoadImageToGPU(const char* filename, GLint internalFormat, GLint Format, int textureSlot)
{
    unsigned int    TexBuffer;
    glGenTextures(1, &TexBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);//激活3号贴图位置
    glBindTexture(GL_TEXTURE_2D, TexBuffer);

    int width, height, nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data2 = stbi_load(filename, &width, &height, &nrChannel, 0);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, Format, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "load image failed" << std::endl;
    }
    stbi_image_free(data2);
    return TexBuffer;
}

int main()
{
#pragma region Open a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//opengl版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//opengl 管线 核心模式
    //OpenWindows
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标
    glfwSetCursorPosCallback(window, mouse_Callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//窗口改变回调，第一次被创建时调用
    glEnable(GL_DEPTH_TEST);//深度测试
#pragma endregion

#pragma region Shader
    Shader* shader = new Shader("vertexSource.vert", "fragmentSource.frag");
#pragma endregion

#pragma region Init and Load MOdels To VAO,VBO
    //VAO Vertex Array Object
    unsigned	int	VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //VBO Vertex Buffer Object
    unsigned	int	VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//BindData

    //位置属性 Gluint =》shader layout
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(3);//启用 顶点属性位置

    //uv
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(5);
#pragma endregion

#pragma region Init and Load Texture
    //TextureA
    unsigned   int TexbufferA;
    TexbufferA = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);

    unsigned   int TexbufferB;
    TexbufferB = LoadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 0);
#pragma endregion

#pragma region Prepare MVP matrices
    //Trans
    glm::mat4 trans = glm::mat4(1.0f);

    //mvp变换
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));

    glm::mat4 viewMat = glm::mat4(1.0f);
    //viewMat = glm::translate(viewMat, glm::vec3(0, 0, -3.0f));
    //viewMat = camera.GetViewMatrix();

    glm::mat4 projectMat = glm::mat4(1.0f);
    projectMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion

    while (!glfwWindowShouldClose(window))
    {
        //input
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       
        

        //更新view
        viewMat = camera.GetViewMatrix();
        //绘制多个物体
        for (size_t i = 0; i < 10; i++)
        {
            //Set Model matrix
            modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            shader->Use();

            //Set View matrix

            //Set Project matrix

            //激活贴图
             //渲染指令
            glActiveTexture(GL_TEXTURE0);//激活0号贴图位置
            glBindTexture(GL_TEXTURE_2D, TexbufferA);
            glActiveTexture(GL_TEXTURE3);//激活3号贴图位置
            glBindTexture(GL_TEXTURE_2D, TexbufferB);

            glUniform1i(glGetUniformLocation(shader->ID, "ourTexture"), 0);
            glUniform1i(glGetUniformLocation(shader->ID, "ourFace"), 3);
           
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
            glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projectMat"), 1, GL_FALSE, glm::value_ptr(projectMat));

            //Set MOdel
            glBindVertexArray(VAO);
            //Draw Call  ,Batch 优化,将所有顶点在外部变换，然后一次传入，只绘制一次减少DrawCall

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        // Clean up, prepare for next render loop
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void mouse_Callback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        mouseLastX = xPos;
        mouseLastY = yPos;
        firstMouse = false;
    }
    float deltaX, deltaY;

    deltaX = xPos - mouseLastX;
    deltaY = yPos - mouseLastY;
    mouseLastX = xPos;
    mouseLastY = yPos;
    std::cout << deltaX << std::endl;
    std::cout << deltaY << std::endl;
    camera.ProcessMouseMovement(deltaX, deltaY);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    //相机前后移动
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.cameraTransform.x = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.cameraTransform.x = -1.0f;
    }
    else
    {
        camera.cameraTransform.x = 0.0f;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)//相机左右移动
    {
        camera.cameraTransform.y = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.cameraTransform.y = -1.0f;
    }
    else
    {
        camera.cameraTransform.y = 0.0f;
    }
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}