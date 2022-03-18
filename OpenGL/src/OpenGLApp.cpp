#include "GL\glew.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>
#include <windows.h>
#include <thread>
#include <chrono>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define WIDTH 960
#define HEIGHT 540

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WIDTH, HEIGHT, "Snake", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Changing OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Changing OpenGL profile

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewInit();

    if (glewInit() != GLEW_OK)
        std::cout << "Error" << std::endl;

    float position[] = {
        0.0f, 0.0f,
        0.0f, 30.0f,
        30.0f, 0.0f,
        30.0f, 30.0f
    };

    unsigned int indexes[] = {
        0, 1, 2,
        2, 1, 3
    };


    glm::vec3 modelCoord(0.0f, 0.0f, 0.0f);
    glm::vec3 viewCoord(0.0f, 0.0f, 0.0f);

    glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), modelCoord);
    glm::mat4 MVP = projection * model;

    VertexArray va;
    VertexBuffer vb(8 * sizeof(float), position);
    VertexBufferLayout layout;
    layout.Push<float>(2);

    IndexBuffer ib(6, indexes);
    ib.Bind();
    va.AddBuffer(vb, layout);

    Shader shader("res/Shaders/Basic.shader");
    shader.Bind();
    shader.UniformMat4f("u_MVP", MVP);
    shader.Uniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    Renderer renderer;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    renderer.Clear();
    va.Unbind();
    ib.Unbind();
    shader.Unbind();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

