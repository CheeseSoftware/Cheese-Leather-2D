#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}


void Camera::update() {
	if (m_needsMatrixUpdate) {
		glm::vec3 translate(-m_position.x + m_width / 2, -m_position.y + m_height / 2, 0.0f);
		glm::vec3 scale(m_scale, m_scale, 0.f);
		
		m_cameraMatrix = glm::ortho(0.0f, (float)m_height, 0.0f, (float)m_width);
		m_cameraMatrix = glm::translate(m_cameraMatrix, translate);
		m_cameraMatrix = glm::scale(glm::mat4(1.f), scale) * m_cameraMatrix;

		m_needsMatrixUpdate = false;
	}
}



void Camera::setSize(int width, int height) {
	m_width = width;
	m_height = height;

	m_needsMatrixUpdate = true;
}

void Camera::setScale(float scale) {
	m_scale = scale;
	m_needsMatrixUpdate = true;
}

void Camera::setPosition(int x, int y) {
	m_position.x = x;
	m_position.y = y;

	m_needsMatrixUpdate = true;
}


glm::vec2 Camera::toWorldPosition(glm::vec2 screenPosition) {

	screenPosition.y = m_height - screenPosition.y;

	screenPosition -= glm::vec2(m_width / 2, m_height / 2);
	screenPosition /= m_scale;
	screenPosition += m_position;

	return screenPosition;
}

glm::vec2 Camera::getPosition() {
	return m_position;
}

float Camera::getScale() {
	return m_scale;
}

glm::mat4 Camera::getCameraMatrix() {
	return m_cameraMatrix;
}