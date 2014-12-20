#pragma once

#include <glm\glm.hpp>

class Camera {
public:
	Camera();
	~Camera();

	void update();
	void setSize(int width, int height);
	void setScale(float scale);
	void setPosition(int x, int y);


	glm::vec2 toWorldPosition(glm::vec2 screenPosition);

	glm::vec2 getPosition();
	float getScale();
	glm::mat4 getCameraMatrix();


private:
	int m_width = 800;
	int m_height = 800;
	float m_scale = 1.f;
	glm::vec2 m_position = glm::vec2(0.f);

	glm::mat4 m_cameraMatrix = glm::mat4(1.f);
	bool m_needsMatrixUpdate = true;
};