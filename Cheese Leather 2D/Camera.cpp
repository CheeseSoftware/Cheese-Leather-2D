#include "Camera.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {

}

Camera::~Camera() {

}


void Camera::update() {
	if (m_needsMatrixUpdate) {
		/*glm::vec3 translate(-m_position.x + m_width / 2, -m_position.y + m_height / 2, 0.0f);
		glm::vec3 scale(m_scale, m_scale, 0.f);
		
		m_cameraMatrix = glm::ortho(0.0f, (float)m_height, 0.0f, (float)m_width);
		m_cameraMatrix = glm::translate(m_cameraMatrix, translate);
		m_cameraMatrix = glm::scale(glm::mat4(1.f), scale) * m_cameraMatrix;*/
		glm::vec3 direction(
			cos(m_verticalAngle) * sin(m_horizontalAngle),
			sin(m_verticalAngle),
			cos(m_verticalAngle) * cos(m_horizontalAngle)
			);

		glm::mat4 projectionMatrix = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		glm::mat4 viewMatrix = glm::lookAt(
			m_position,           // Camera is here
			m_position + direction, // and looks here : at the same position, plus "direction"
			glm::vec3(0, 1, 0)                  // Head is up (set to 0,-1,0 to look upside-down)
			);
		glm::mat4 modelMatrix = glm::mat4(1.0f);

		m_cameraMatrix = projectionMatrix * viewMatrix * modelMatrix;
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
	m_position.z = 0;

	m_needsMatrixUpdate = true;
}

void Camera::setPosition(glm::vec3 pos) {
	m_position = pos;

	m_needsMatrixUpdate = true;
}

void Camera::setAngle(float horizontal, float vertical)
{
	m_horizontalAngle = horizontal;
	m_verticalAngle = vertical;

	m_needsMatrixUpdate = true;
}

/*void Camera::setFoV(float FoV)
{
	m_FoV = FoV;

	m_needsMatrixUpdate = true;
}*/


glm::vec2 Camera::toWorldPosition(glm::vec2 screenPosition) {

	screenPosition.y = m_height - screenPosition.y;

	screenPosition -= glm::vec2(m_width / 2, m_height / 2);
	screenPosition /= m_scale;
	screenPosition += glm::vec2(m_position.x, m_position.y);

	return screenPosition;
}

glm::vec3 Camera::getPosition() {
	return m_position;
}

float Camera::getScale() {
	return m_scale;
}

glm::mat4 Camera::getCameraMatrix() {
	return m_cameraMatrix;
}