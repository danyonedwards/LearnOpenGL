#include "key_handler.h";

void ProcessInput(GLFWwindow* window, float* mixAmount) {
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		(*mixAmount) += 0.001;
	}
	
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		(*mixAmount) -= 0.001;
	}
}