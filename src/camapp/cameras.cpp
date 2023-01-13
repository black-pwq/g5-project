#include "cameras.h"

OperatableCamera::OperatableCamera(float fovy, float aspect, float znear, float zfar)
 : PerspectiveCamera(fovy, aspect, znear, zfar) {}

glm::mat4 OperatableCamera::getViewMatrix() const {
	glm::vec3 eye = transform.position + displace;
	glm::vec3 target = eye + getFront();
	glm::vec3 up = getUp();
	return glm::lookAt(eye, target, up);
}

void OperatableCamera::zoomToFit() {
	fovy = glm::radians(defaulfFovyDegree);
	displace = glm::vec3(0.0f);
	rotation = { 1.0f, 0.0f, 0.0f, 0.0f };
}

void OperatableCamera::zoom(float degreeOffset) {
	float degree = static_cast<float>(glm::degrees(fovy) - degreeOffset);
	fovy = glm::radians(clampToEdge(degree, minFovyDegree, maxFovyDegree));
}

void OperatableCamera::rotate(glm::vec3 rotateAxis, float radian) {
	transform.rotation = glm::quat{glm::cos(radian), sin(radian) * rotateAxis} * transform.rotation;
}

void OperatableCamera::move(glm::vec3 normalizedDirection, float distance) {
	transform.position += normalizedDirection * distance;
}

void OperatableCamera::move(glm::vec3 displacement) {
	transform.position += displacement;
}

void OperatableCamera::pan(glm::vec3 normalizedDirection, float distance) {
	displace += normalizedDirection * distance;
}

void OperatableCamera::pan(glm::vec3 displacement) {
	displace += displacement;
}

void OperatableCamera::orbit(glm::vec3 center, float degree) {
	auto up = getUp();
	auto right = getRight();	
	auto front = getFront();
	float radian = glm::radians(degree);
	glm::vec3 axis = glm::vec3{0.0f, 1.0f, 0.0f};
	float radius = static_cast<float>((transform.position - center).length());

	rotation = glm::quat{glm::cos(radian), sin(radian) * up} * rotation;
	glm::vec3 tan = radius * (front - getFront());
	pan(tan);

}

void OperatableCamera::toObserver() {
	transform.rotation = transform.rotation * rotation;
	transform.position = transform.position + displace;
	rotation = {1.0f, 0.0f, 0.0f, 0.0f};
	displace = {0.0f, 0.0f, 0.0f};
}

glm::vec3 OperatableCamera::getUp() const {
	return rotation * transform.getUp();
}
glm::vec3 OperatableCamera::getFront() const {
	return rotation * transform.getFront();
}
glm::vec3 OperatableCamera::getRight() const {
	return rotation * transform.getRight();
}