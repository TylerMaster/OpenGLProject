// OpenGLProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>

#include "Texture.h"
#include "ShaderClass.h"
#include "VAO.h"
#include "EBO.h"



const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


    GLfloat vertices[] =
    {

     -0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
     -0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
      0.5f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
      0.5f, -0.5f, 0.0f,    1.0f, 1.0f, 1.0f,     1.0f, 0.0f

     /*-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     0.8f, 0.3f,  0.02f,
     0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,       0.8f, 0.3f,  0.02f,
     0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    1.0f, 0.6f,  0.32f,
     -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,   0.9f, 0.45f, 0.17f,
     0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    0.9f, 0.45f, 0.17f,
     0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,       0.8f, 0.3f,  0.02f
     */
        
           /*
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,

             // second triangle
             -0.5f, -0.5f, 0.0f,
              0.5f,  0.5f, 0.0f,
             -0.5f,  0.5f, 0.0f*/
         
    };

    GLuint indices[] =
    {
        0, 2, 1, //Upper triangle
        0, 3, 2  //Lower triangle

        /* 0, 3, 5,
         3, 2, 4,
         5, 4, 1 */
    };

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
    gladLoadGL();
    glViewport(0, 0, 800, 600);

    /*GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);*/

    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");


    // Texture



    
   /* GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

   // glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    glfwSwapBuffers(window);



    Texture cat("textures/cat.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    cat.texUnit(shaderProgram, "tex0", 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glUniform1f(uniID, 0.5f);

        cat.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
       glfwPollEvents();
    }
    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);*/
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    cat.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
