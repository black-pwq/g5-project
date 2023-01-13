#include "../common/camera.h"
#include "util.h"

class OperatableCamera : public PerspectiveCamera {
	public:	
	static constexpr float maxFovyDegree = 60.0f;
	static constexpr float defaulfFovyDegree = 45.0f;
	static constexpr float minFovyDegree = 1.0f;
	float _mouseMoveSen = 0.02f;
	float _cameraMoveSpeed = 10.0f;
	float _mouseScrollSen = 1.0f;
	glm::vec3 displace = glm::vec3(0.0f);
	glm::quat rotation = { 1.0f, 0.0f, 0.0f, 0.0f };

	public:
	OperatableCamera(float fovy, float aspect, float znear, float zfar);
	glm::mat4 getViewMatrix() const;
	void zoomToFit();
	void zoom(float degreeOffset);
	void rotate(glm::vec3 rotateAxis, float radian);
	void move(glm::vec3 normalizedDirection, float distance);
	void move(glm::vec3 displacement);
	void orbit(glm::vec3 center, float degree);
	void pan(glm::vec3 normalizedDirection, float distance);
	void pan(glm::vec3 displacement);
	void toObserver();
	glm::vec3 getUp() const;
	glm::vec3 getFront() const;
	glm::vec3 getRight() const ;
};