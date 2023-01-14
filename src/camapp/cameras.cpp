#include "cameras.h"

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(getEye(), getView() + getEye(), getUp());
}
glm::vec3 Camera::getView() const {
	return view;
}
glm::vec3 Camera::getRight() const {
	return glm::cross(glm::vec3{0.0f, 1.0f, 0.0f}, -getView());
}
glm::vec3 Camera::getUp() const {
	return glm::cross(getRight(), getView());
}
glm::vec3 Camera::getEye() const {
	return eye;
}
glm::vec3 Camera::getTarget() const {
	return target;
}


PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float znear, float zfar)
	: fovy(fovy), aspect(aspect), znear(znear), zfar(zfar) { }

glm::mat4 PerspectiveCamera::getProjectionMatrix() const {
	return glm::perspective(fovy, aspect, znear, zfar);
}
void PerspectiveCamera::zoom(float degreeOffset) {
	float degree = static_cast<float>(glm::degrees(fovy) - degreeOffset);
	fovy = glm::radians(clampToEdge(degree, minFovyDegree, maxFovyDegree));
}
void PerspectiveCamera::zoomToFit() {
    fovy = defaulfFovyDegree;
}


MovableCamera::MovableCamera(float fovy, float aspect, float znear, float zfar)
	:PerspectiveCamera(fovy, aspect, znear, zfar) {}
void MovableCamera::rotate(glm::vec3 rotateAxis, float radian) {
	view = glm::quat{glm::cos(radian), sin(radian) * rotateAxis} * getView();
}
void MovableCamera::move(glm::vec3 normalizedDirection, float distance) {
	eye += normalizedDirection * distance;
}
void MovableCamera::move(glm::vec3 displacement) {
	eye += displacement;
}


OrbitCamera::OrbitCamera(float fovy, float aspect, float znear, float zfar):MovableCamera(fovy, aspect, znear, zfar) { }
glm::vec3 OrbitCamera::getView() const {
    return glm::normalize(target - eye);
}
void OrbitCamera::rotateAzimuth(const float radians)
{
    glm::vec3 axis = {.0f, 1.0f, .0f};
    glm::vec3 t2e = eye - target;
    eye = glm::quat{cos(radians), sin(radians) * axis} * t2e + target;
}
void OrbitCamera::rotatePolar(const float radians)
{
    glm::vec3 axis = -getRight();
    glm::vec3 t2e = eye - target;
    eye = glm::quat{cos(radians), sin(radians) * axis} * t2e + target;
}
void OrbitCamera::move(glm::vec3 displacement) {
    this->displacement += displacement;
}
glm::vec3 OrbitCamera::getEye() const {
    return eye + displacement;
}
void OrbitCamera::zoomToFit() {
    fovy = defaulfFovyDegree;
    displacement = {.0f, .0f, .0f};
    eye = {.0f, .0f, 5.0f};
}