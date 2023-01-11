#include "callbacks.h"

void cursorPosCallback(GLFWwindow *window, double x, double y) {
	MainApp *app = reinterpret_cast<MainApp*>(glfwGetWindowUserPointer(window));
	app->cursorPosCallback(window, x, y);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {

}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
}