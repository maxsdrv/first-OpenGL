#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <cmath>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int WIDTH = 1024;
const unsigned int HEIGHT = 800;



int main() {

    glfwInit();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Training", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader ourShader{"shader.vs", "shader.fs"};

    std::vector<float> indices {
        -0.5f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f
    };

    std::vector<float> multicolor {
        -0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(indices), &indices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);

    //Rendering cycle
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //Update for uniform color value
        /*float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;*/

        float offset = 0.5f;
        ourShader.setFloat("xOffset", offset);

        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}








