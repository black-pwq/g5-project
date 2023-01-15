#include "callbacks.h"
#include <iostream>

void cursorPosCallback(GLFWwindow *window, double x, double y) {
	auto *app = reinterpret_cast<CamApp*>(glfwGetWindowUserPointer(window));
	app->cursorPosCallback(window, x, y);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
	auto *app = reinterpret_cast<CamApp*>(glfwGetWindowUserPointer(window));
	app->scrollCallback(window, xOffset, yOffset);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	auto *app = reinterpret_cast<CamApp*>(glfwGetWindowUserPointer(window));
	app->keyCallback(window, key, scancode, action, mods);
}