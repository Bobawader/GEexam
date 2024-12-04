#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Camera.h"
#include "Shader.h"
#include "Spheres.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Camera& camera);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

int main()
{

    //-----------------------------------------------------------------------------------------------//
    //-------------------------------------INITILIZE-------------------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Test Win", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);  // Enable depth testing



    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("Exam.vs", "Exam.fs");




    //-----------------------------------------------------------------------------------------------//
    //-------------------------------------Forward--Declarations-------------------------------------//
    //-----------------------------------------------------------------------------------------------//
    Camera camera;
    Spheres sphere(1.0f, glm::vec3(0.0f, 0.0f, 0.0f)); // Radius = 1.0f, Position = (0, 0, 0)



    //-----------------------------------------------------------------------------------------------//
    //-----------------------------------------RenderLoop--------------------------------------------//
    //-----------------------------------------------------------------------------------------------//


    while (!glfwWindowShouldClose(window))
    {
        camera.processInput(window);
        processInput(window, camera);
        


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(camera.position, camera.position + camera.orientation, camera.up);
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f, 10000.0f);

        glm::mat4 model = glm::mat4(1.0f);

        sphere.renderSphere(ourShader,view,projection);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window, Camera& camera) {
    // Check for escape key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}