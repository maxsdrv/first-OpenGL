#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/freeglut.h>

#include <iostream>
#include <vector>

const unsigned int HEIGHT = 1920;
const unsigned int WIDTH = 1028;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void textRendering(std::string text);


//Shaders GLSL
/************************************************************************/
const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char* blackShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
                                   "}\n\0";

const char* yellowShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                   "}\n\0";

/*************************************************************************/


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

    //Initialization vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success = 0;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Initialization fragment shader
    int blackShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(blackShader, 1, &blackShaderSource, nullptr);
    glCompileShader(blackShader);

    glGetShaderiv(blackShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(blackShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Initialization new fragment shader
    int yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellowShader, 1, &yellowShaderSource, nullptr);
    glCompileShader(yellowShader);

    glGetShaderiv(yellowShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(yellowShader, 512, nullptr, infoLog);
        std::cout << "ERROR::YELLOW::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }



    //Linking shaders
    unsigned int shaderProgramBlack = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram();

    glAttachShader(shaderProgramBlack, vertexShader);
    glAttachShader(shaderProgramBlack, blackShader);
    glLinkProgram(shaderProgramBlack);

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, yellowShader);
    glLinkProgram(shaderProgramYellow);

    glGetProgramiv(shaderProgramBlack, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramBlack, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramYellow, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(blackShader);
    glDeleteShader(yellowShader);

    std::vector<float> vertices {
        -0.05f,  1.0f, 0.0f,
        -1.0f,  0.0f, 0.0f,
        -0.05f,  0.0f, 0.0f
    };


    std::vector<float> triangle2 {
        0.05f,  1.0f, 0.0f,
        1.0f,  0.0f, 0.0f,
        0.05f,  0.0f, 0.0f
    };

    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices), &vertices.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, triangle2.size() * sizeof(triangle2), &triangle2.front(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);
    glEnableVertexAttribArray(0);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    glBindVertexArray(0);

    //Getting count vertex
    int getAttributes = 0;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &getAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << getAttributes << std::endl;

    //Rendering cycle
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramBlack);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgramYellow);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

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

void textRendering(std::string text) {
    int w = 0;
    w = glutBitmapLength(GLUT_BITMAP_8_BY_13, text);
    glRasterPos2f(0.0, 0.0);

    float x = 0.5;
    glRasterPos2f(x - (float) WIDTH / 2, 0.0);

    glColor3f(1.0, 0.0, 0.0);
}





