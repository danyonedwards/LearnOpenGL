#include <glad/glad.h>
#include <GlFW/glfw3.h>
#include <iostream>

#include "key_handler.h"
#include "shader.h"

const int VIEWPORT_HEIGHT = 600;
const int VIEWPORT_WIDTH = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const char* vertexShaderPath = "src/shader.vert";
const char* fragmentShaderPath = "src/shader.frag";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Used for OSX
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Init Window 
    GLFWwindow* window = glfwCreateWindow(VIEWPORT_WIDTH, VIEWPORT_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Setup the window
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);

    // Load shaders 
    Shader triangleShader(vertexShaderPath, fragmentShaderPath);


    // Define vertices
    float triangleOneVertices[] = {
        // posistions       // colors
        -0.9, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.1, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    float triangleTwoVertices[] = {
        0.1, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.9, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    // Recatangle - uses element buffer object
    //float vertices[] = {
    //    0.5f,  0.5f, 0.0f,  // top right
    //    0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //};
    //unsigned int indices[] = {
    //    0, 1, 3, // First triangle
    //    1, 2, 3 // Second triangle
    //};


    //** Setup triangle 1 **//
    unsigned int t1VAO, t1VBO;
    glGenVertexArrays(1, &t1VAO);
    glBindVertexArray(t1VAO);
    glGenBuffers(1, &t1VBO);

    // Bind the triangle 1 VBO to VAO
    glBindBuffer(GL_ARRAY_BUFFER, t1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOneVertices), triangleOneVertices, GL_STATIC_DRAW);

    // Enable the position and color attribs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    //** Setup triangle 2 **//
    unsigned int t2VAO, t2VBO;
    glGenVertexArrays(1, &t2VAO);
    glBindVertexArray(t2VAO);
    glGenBuffers(1, &t2VBO);

    // Bind the triangle 2 VBO to VAO
    glBindBuffer(GL_ARRAY_BUFFER, t2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwoVertices), triangleTwoVertices, GL_STATIC_DRAW);

    // Enable to the position vertex attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);



   // DEPRECATED - Element buffers
   /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


    // WIREFRAME MODE
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        ProcessInput(window);

        //rendering commands here
        // Set the background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Bind vao 
        triangleShader.use();

        triangleShader.setFloat("xOffset", 0.3f);

        
        glBindVertexArray(t1VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3); 

        glBindVertexArray(t2VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // DEPRECATED - Element buffers
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // Count is num indices
        
        // Unbind VAO
        glBindVertexArray(0);
        glUseProgram(0);

        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate(); 
    return 0;
}

