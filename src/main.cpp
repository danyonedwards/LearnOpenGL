#include <glad/glad.h>
#include <GlFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "key_handler.h"
#include "shader.h"
#include "stb_image.h"

const int VIEWPORT_HEIGHT = 600;
const int VIEWPORT_WIDTH = 800;

float FOV = 45;

float mixAmount = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

unsigned char* loadTexture(const char* texturePath, GLenum format);

// SHADERS
const char* vertexShaderPath = "src/shader.vert";
const char* fragmentShaderPath = "src/shader.frag";

// TEXTURES
const char* containerTexturePath = "resources/textures/container.jpg";
const char* awesomeFaceTexturePath = "resources/textures/awesomeface.png";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    
    // Used for OSX
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Init Window 
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
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

    printf("OpenGL Version:%s\n", glGetString(GL_VERSION));
    printf("GLSL Version  :%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));


    // Setup the window
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Configuration
    glEnable(GL_DEPTH_TEST);
   
    // Load shaders
    Shader shapeShader(vertexShaderPath, fragmentShaderPath);
   

    // Cube - uses element buffer object
    float vertices[] = {
    // Positions          // Textures
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    unsigned int indices[] = {
        0, 1, 3, // First triangle
        1, 2, 3 // Second triangle
    };

   // Element buffers (RECTANGLE)
    unsigned int VBO, EBO, VAO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    /*glEnableVertexAttribArray(2);*/


    // Generate, Bind and load texture
    unsigned int texture1, texture2;

    // Set the texture wrapping / filtering for texture 1
    glGenTextures(1, &texture1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    unsigned char* containerTextureData = loadTexture(containerTexturePath, GL_RGB);

    // Set the texture wrapping / filtering for texture 2
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    unsigned char* awesomefaceTextureData = loadTexture(awesomeFaceTexturePath, GL_RGBA);

    shapeShader.use();
    shapeShader.setInt("texture1", 0);
    shapeShader.setInt("texture2", 1);


    // WIREFRAME MODE
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //glfwSwapInterval(0);
    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        // This is incredibly unpreferable and requires a rework
        ProcessInput(window, &FOV);

        //rendering commands here
        // Set the background color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shapeShader.use();

        // Matrices
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // Move world away from view, negative z is away

        std::cout << FOV << std::endl;


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(FOV), (float)VIEWPORT_WIDTH / (float)VIEWPORT_HEIGHT, 0.1f, 100.0f);


        int viewLoc = glGetUniformLocation(shapeShader.ID, "view");
        int projectionLoc = glGetUniformLocation(shapeShader.ID, "projection");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)); 
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Blending
        shapeShader.setFloat("mixAmount", mixAmount);
 
        // Bindings
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAO);

        // Draw
        for (unsigned int i = 0; i < 10; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0) angle = glfwGetTime() * 25.0f;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
            shapeShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


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

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

unsigned char* loadTexture(const char* texturePath, GLenum format){
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load(texturePath, &width, &height, &nrChannels, 0);
     if (textureData) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture: " << texturePath << std::endl;
    }
    stbi_image_free(textureData);

    std::cout << "Successfully loaded texture: " << texturePath << std::endl;
    return textureData;
}