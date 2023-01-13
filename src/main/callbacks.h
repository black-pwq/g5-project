#ifndef __MAINAPP_CALLBACKS_H__
#define __MAINAPP_CALLBACKS_H__
#include "mainapp.h"
void cursorPosCallback(GLFWwindow *window, double xPos, double yPos);

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
#endif