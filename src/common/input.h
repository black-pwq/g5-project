#pragma once

#include <array>
#include <iostream>
#include <GLFW/glfw3.h>

struct Input {
	struct Mouse {
		struct {
			bool left = false;
			bool middle = false;
			bool right = false;
		} press;

		struct {
			float currPos[2] = {0.0f, 0.0f};
			float prevPos[2] = {0.0f, 0.0f};
		} move;

		struct {
			float xOffset = 0.0f;
			float yOffset = 0.0f;
		} scroll;
	} mouse;

	struct Keyboard {
		std::array<int, GLFW_KEY_LAST + 1> keyStates = { GLFW_RELEASE };
	} keyboard;

	void forwardState() {
		mouse.move.prevPos[0] = mouse.move.currPos[0];
		mouse.move.prevPos[1] = mouse.move.currPos[1];
		mouse.scroll.xOffset = 0.0f;
		mouse.scroll.yOffset = 0.0f;
	}
};