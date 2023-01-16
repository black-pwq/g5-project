#pragma once

#include <memory> 
#include <FreeImage.h>
#include "../texapp/texapp.h"
#include "../model/model.h"
#include "callbacks.h"

class MainApp : public TexApp {
private:

public:
	MainApp(const Options& options);
	~MainApp();

protected:
	virtual void handleInput();
	virtual void renderFrame();
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};