#include <glad/glad.h>
#include <GlFW/glfw3.h>
#include <iostream>
#include "keyHandler.h"

const int VIEWPORT_HEIGHT = 600;
const int VIEWPORT_WIDTH = 800;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderOrangeSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* fragmentShaderYellowSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.1f, 1.0f);\n"
"}\0";


unsigned int compileVertexShader() {
    // Setup the shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Validate shader success
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return vertexShader;
}

unsigned int compileFragmentShader(const char* shaderSource) {
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderSource, NULL);
    glCompileShader(fragmentShader);

    // validate shader success
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return fragmentShader;
}

unsigned int attachShaders(unsigned int vertexShader, unsigned int fragmentShader) {
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    }

    return shaderProgram;
}

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

    // SETUP SHADERS
    // setup vertex shader
    unsigned int vertexShader; 
    vertexShader = compileVertexShader();
    // setup fragment shader
    unsigned int fragmentShaderOrange, fragmentShaderYellow;
    fragmentShaderOrange = compileFragmentShader(fragmentShaderOrangeSource);
    fragmentShaderYellow = compileFragmentShader(fragmentShaderYellowSource);
    // compile shader program
    unsigned int triangleOneShaderProgram, triangleTwoShaderProgram;
    triangleOneShaderProgram = attachShaders(vertexShader, fragmentShaderOrange);
    triangleTwoShaderProgram = attachShaders(vertexShader, fragmentShaderYellow);
    
    // remove the shaders once they have been linked to the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);


    float triangleOneVertices[] = {
        -0.9, -0.5f, 0.0f,
        -0.1, -0.5f, 0.0f,
        -0.5, 0.5f, 0.0f
    };
    float triangleTwoVertices[] = {
        0.1, -0.5f, 0.0f,
        0.9, -0.5f, 0.0f,
        0.5, 0.5f, 0.0f,
    };

    // Recatangle - uses element buffer object
    //float vertices[] = {
    //    0.5f,  0.5f, 0.0f,  // top right
    //    0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f   // top left 
    //};
    unsigned int indices[] = {
        0, 1, 3, // First triangle
        1, 2, 3 // Second triangle
    };


    // Setup triangle 1
    unsigned int t1VAO, t1VBO; 
    glGenBuffers(1, &t1VBO);
    glGenVertexArrays(1, &t1VAO);

    glBindVertexArray(t1VAO);
    glBindBuffer(GL_ARRAY_BUFFER, t1VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleOneVertices), triangleOneVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // Setup triangle 2
    unsigned int t2VAO, t2VBO;
    glGenBuffers(1, &t2VBO);
    glGenVertexArrays(1, &t2VAO);

    glBindVertexArray(t2VAO);
    glBindBuffer(GL_ARRAY_BUFFER, t2VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleTwoVertices), triangleTwoVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Bind Element Buffer
   /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


    // WIREFRAME MODE
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        //rendering commands here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Bind vao 
        glUseProgram(triangleOneShaderProgram);
        glBindVertexArray(t1VAO); // Draw triangle 1
        glDrawArrays(GL_TRIANGLES, 0, 3); 

        glUseProgram(triangleTwoShaderProgram);
        glBindVertexArray(t2VAO); // Draw triangle 2
        glDrawArrays(GL_TRIANGLES, 0, 3);

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

