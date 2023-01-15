#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/closest_point.hpp>
#include <glm/gtc/constants.hpp>
#include "util.h"
class Camera {
	public:
	glm::vec3 eye = {0.0f, 0.0f, 5.0f};
	glm::vec3 target = {0.0f, 0.0f, .0f};
	glm::vec3 view = {0.0f, 0.0f, -1.0f};

	glm::mat4 getViewMatrix() const;
	virtual glm::mat4 getProjectionMatrix() const = 0;

	glm::vec3 getRight() const ;
	virtual glm::vec3 getView() const ;
	glm::vec3 getUp() const ;
	virtual glm::vec3 getEye() const ;
	glm::vec3 getTarget() const ;
};

class PerspectiveCamera : public Camera {
	public:	
	float fovy;
	float aspect;
	float znear;
	float zfar;
	static constexpr float maxFovyDegree = 60.0f;
	static constexpr float defaulfFovyDegree = 45.0f;
	static constexpr float minFovyDegree = 1.0f;

	PerspectiveCamera(float fovy, float aspect, float znear, float zfar);
	glm::mat4 getProjectionMatrix() const;
	void zoom(float degreeOffset);
	virtual void zoomToFit();
};

class MovableCamera : public PerspectiveCamera {
	public:
	float _mouseMoveSen = 0.02f;
	float _cameraMoveSpeed = 10.0f;
	float _mouseScrollSen = 1.0f;

	public:
	MovableCamera(float fovy, float aspect, float znear, float zfar);
	void rotate(glm::vec3 rotateAxis, float radian);
	void move(glm::vec3 normalizedDirection, float distance);
	virtual void move(glm::vec3 displacement);
};

class OrbitCamera : public MovableCamera
{
public:
	OrbitCamera(float fovy, float aspect, float znear, float zfar);

	glm::vec3 getView() const;
	glm::vec3 getEye() const ;
    void rotateAzimuth(const float radians);
    void rotatePolar(const float radians);
	void move(glm::vec3 displacement);
	void zoomToFit();
};
