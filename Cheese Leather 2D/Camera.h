#pragma once

#include <glm\glm.hpp>
//#include <GLFW\glfw3.h>

class Camera {
public:
	Camera();
	~Camera();

	void update();
	void setSize(int width, int height);
	void setScale(float scale);
	void setPosition(int x, int y);
	void setPosition(glm::vec3 pos);
	void setAngle(float horizontal, float vertical);

	glm::vec2 toWorldPosition(glm::vec2 screenPosition);

	glm::vec3 getPosition();
	float getScale();
	glm::mat4 getCameraMatrix();

private:
	int m_width = 0;
	int m_height = 0;
	float m_scale = 1.f;
	float m_horizontalAngle = 0;
	float m_verticalAngle = 0;
	glm::vec3 m_position = glm::vec3(0.f);
	glm::mat4 m_cameraMatrix = glm::mat4(1.f);
	bool m_needsMatrixUpdate = true;
};