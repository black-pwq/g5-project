#include "triapp.h"
#include "objloader.cpp"


SceneRoaming::SceneRoaming(const Options& options): Application(options) {
	// set input mode
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	_input.mouse.move.xNow = _input.mouse.move.xOld = 0.5f * _windowWidth;
	_input.mouse.move.yNow = _input.mouse.move.yOld = 0.5f * _windowHeight;
	glfwSetCursorPos(_window, _input.mouse.move.xNow, _input.mouse.move.yNow);

	// init cameras
	_cameras.resize(2);

	const float aspect = 1.0f * _windowWidth / _windowHeight;
	constexpr float znear = 0.1f;
	constexpr float zfar = 10000.0f;

	// perspective camera
	_cameras[0].reset(new PerspectiveCamera(
		glm::radians(60.0f), aspect, 0.1f, 10000.0f));
	_cameras[0]->transform.position = glm::vec3(0.0f, 0.0f, 15.0f);

	// orthographic camera
	_cameras[1].reset(new OrthographicCamera(
		-4.0f * aspect, 4.0f * aspect, -4.0f, 4.0f, znear, zfar));
	_cameras[1]->transform.position = glm::vec3(0.0f, 0.0f, 15.0f);

	std::string modelRelPath = "obj/cube.obj";

	// init model
	// _bunny.reset(new Model(getAssetFullPath(modelRelPath)));
	Objloader Objloader;
	Objloader.loadobj(modelRelPath);
			

	_cubes[0].reset(new Cube(Objloader._vertices,Objloader._indices));
	// _cubes[0]->transform.setFromTRS(glm::mat4(
	// 	1,0,0,0,
	// 	0,1,0,1,
	// 	0,0,1,0,
	// 	0,0,0,0
	// ));
	// init shader
	std::cout << "vertices size "<<_cubes[0]->_vertices.size()<<std::endl;
	std::cout << "indices size "<<_cubes[0]->_indices.size()<<std::endl;
	// for (int i = 0; i < _cubes[0]->_vertices.size(); i++) {
    //     std::cout << _cubes[0]->_vertices.at(i).position.x<< "  "<< _cubes[0]->_vertices.at(i).position.y<< "  "<< _cubes[0]->_vertices.at(i).position.z << std::endl;
    //     std::cout << _cubes[0]->_vertices.at(i).normal.x<< "  "<< _cubes[0]->_vertices.at(i).normal.y<< "  "<< _cubes[0]->_vertices.at(i).normal.z << std::endl;

    // }

    // for (int i = 0; i < _cubes[0]->_indices.size(); i++) {
    //     std::cout << _cubes[0]->_indices.at(i) << std::endl;
    // }
	initShader();
}

void SceneRoaming::handleInput() {
	constexpr float cameraMoveSpeed = 5.0f;
	constexpr float cameraRotateSpeed = 0.02f;

	if (_input.keyboard.keyStates[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
		glfwSetWindowShouldClose(_window, true);
		return ;
	}

	if (_input.keyboard.keyStates[GLFW_KEY_SPACE] == GLFW_PRESS) {
		std::cout << "switch camera" << std::endl;
		// switch camera
		activeCameraIndex = (activeCameraIndex + 1) % _cameras.size();
		_input.keyboard.keyStates[GLFW_KEY_SPACE] = GLFW_RELEASE;
		return;
	}

	Camera* camera = _cameras[activeCameraIndex].get();

	if (_input.keyboard.keyStates[GLFW_KEY_W] != GLFW_RELEASE) {
		// std::cout << "W" << std::endl;
		// TODO: move the camera in its front direction
		// write your code here
		// -------------------------------------------------
		// camera->transform.position = ...;
		camera->transform.position = camera->transform.rotation * glm::vec3{ 0.0f,0.0f, -3 * _deltaTime * cameraMoveSpeed } + camera->transform.position;

		// -------------------------------------------------
	}

	if (_input.keyboard.keyStates[GLFW_KEY_A] != GLFW_RELEASE) {
		// std::cout << "A" << std::endl;
		// TODO: move the camera in its left direction
		// write your code here
		// -------------------------------------------------
		// camera->transform.position = ...;
		// -------------------------------------------------
		camera->transform.position = camera->transform.rotation * glm::vec3{ -3 * _deltaTime * cameraMoveSpeed,0.0f,0.0f } + camera->transform.position;

	}

	if (_input.keyboard.keyStates[GLFW_KEY_S] != GLFW_RELEASE) {
		// std::cout << "S" << std::endl;
		// TODO: move the camera in its back direction
		// write your code here
		// -------------------------------------------------
		camera->transform.position = camera->transform.rotation * glm::vec3{ 0.0f,0.0f, 3 * _deltaTime * cameraMoveSpeed } + camera->transform.position;

		// camera->transform.position = ...;
		// -------------------------------------------------
	}

	if (_input.keyboard.keyStates[GLFW_KEY_D] != GLFW_RELEASE) {
		// std::cout << "D" << std::endl;
		// TODO: move the camera in its right direction
		// write your code here
		// -------------------------------------------------
		camera->transform.position = camera->transform.rotation * glm::vec3{ 3 * _deltaTime * cameraMoveSpeed,0.0f,0.0f } + camera->transform.position;

		// camera->transform.position = ...;
		// -------------------------------------------------
	}

	if (_input.mouse.move.xNow != _input.mouse.move.xOld) {
		// std::cout << "mouse move in x direction" << std::endl;
		// TODO: rotate the camera around world up: glm::vec3(0.0f, 1.0f, 0.0f)
		// hint1: you should know how do quaternion work to represent rotation
		// hint2: mouse_movement_in_x_direction = _input.mouse.move.xNow - _input.mouse.move.xOld
		// write your code here
		// -----------------------------------------------------------------------------
		// camera->transform.rotation = ...
		// -----------------------------------------------------------------------------
		float mouse_movement_in_x_direction = -(_input.mouse.move.xNow - _input.mouse.move.xOld) * cameraRotateSpeed * 10 * _deltaTime;
		camera->transform.rotation = glm::quat{ cosf(mouse_movement_in_x_direction / 2),0.0f,1.0f * sinf(mouse_movement_in_x_direction / 2),0.0f }*camera->transform.rotation;

	}

	if (_input.mouse.move.yNow != _input.mouse.move.yOld) {
		// std::cout << "mouse move in y direction" << std::endl;
		// TODO: rotate the camera around its local right
		// hint1: you should know how do quaternion work to represent rotation
		// hint2: mouse_movement_in_y_direction = _input.mouse.move.yNow - _input.mouse.move.yOld
		// write your code here
		// -----------------------------------------------------------------------------
		// camera->transform.rotation = ...
		// -----------------------------------------------------------------------------
		float  mouse_movement_in_y_direction = -(_input.mouse.move.yNow - _input.mouse.move.yOld) * cameraRotateSpeed * 10 * _deltaTime;
		// write your code here
		// ---------------------------------------------------------- -------------------
		glm::quat temp = { cosf(mouse_movement_in_y_direction / 2),camera->transform.getRight() * sinf(mouse_movement_in_y_direction / 2) };
		camera->transform.rotation = temp * camera->transform.rotation;
	}

	_input.forwardState();
}

void SceneRoaming::renderFrame() {
	showFpsInWindowTitle();

	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glm::mat4 projection = _cameras[activeCameraIndex]->getProjectionMatrix();
	glm::mat4 view = _cameras[activeCameraIndex]->getViewMatrix();
	
	_shader->use();
	_shader->setUniformMat4("projection", projection);
	_shader->setUniformMat4("view", view);
	glm::mat4 translation = glm::mat4(1.0f);
		// @rotation
		glm::mat4 rotation = glm::mat4(1.0f);
		// @scale
		glm::mat4 scale = glm::mat4(1.0f);
		// ------------------------------------------------

		glm::mat4 model = translation * rotation * scale;
	_shader->setUniformMat4("model", model);
	// std::cout << _cubes[0]->transform.getLocalMatrix()[0][0] << _cubes[0]->transform.getLocalMatrix()[0][1] << std::endl;
	// std::cout << _cubes[0]->transform.getLocalMatrix()[1][0] << _cubes[0]->transform.getLocalMatrix()[1][1] << std::endl;

	// std::cout << _cubes[0]->transform.getLocalMatrix()[2][0] << _cubes[0]->transform.getLocalMatrix()[2][1] << std::endl;

	// std::cout << _cubes[0]->transform.getLocalMatrix()[3][0] << _cubes[0]->transform.getLocalMatrix()[3][1] << std::endl;
	_cubes[0]->draw();
}

void SceneRoaming::initShader() {
	const char* vsCode =
		"#version 330 core\n"
		"layout(location = 0) in vec3 aPosition;\n"
		"layout(location = 1) in vec3 aNormal;\n"
		"out vec3 worldPosition;\n"
		"out vec3 normal;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main() {\n"
		"	normal = mat3(transpose(inverse(model))) * aNormal;\n"
		"	worldPosition = vec3(model * vec4(aPosition, 1.0f));\n"
		"	gl_Position = projection * view * vec4(worldPosition, 1.0f);\n"
		"}\n";

	const char* fsCode =
		"#version 330 core\n"
		"in vec3 worldPosition;\n"
		"in vec3 normal;\n"
		"out vec4 fragColor;\n"
		"void main() {\n"
		"vec3 lightPosition = vec3(100.0f, 100.0f, 100.0f);\n"
		"// ambient color\n"
		"float ka = 0.1f;\n"
		"vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);\n"
		"vec3 ambient = ka * objectColor;\n"
		"// diffuse color\n"
		"float kd = 0.8f;\n"
		"vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);\n"
		"vec3 lightDirection = normalize(lightPosition - worldPosition);\n"
		"vec3 diffuse = kd * lightColor * max(dot(normalize(normal), lightDirection), 0.0f);\n"
		"fragColor = vec4(ambient + diffuse, 1.0f);\n"
		"}\n";

	_shader.reset(new GLSLProgram);
	_shader->attachVertexShader(vsCode);
	_shader->attachFragmentShader(fsCode);
	_shader->link();
}