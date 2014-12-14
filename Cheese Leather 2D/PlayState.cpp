#include "PlayState.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IRenderer.h"
#include "RandomTestRenderable.h"


PlayState::PlayState()
{
	this->renderable = new RandomTestRenderable();
}


PlayState::~PlayState()
{
}

void PlayState::Update()
{

}

void PlayState::Draw(State *state, IRenderer *renderer)
{
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 *MVP = new glm::mat4(Projection * View * Model); // Remember, matrix multiplication is the other way around

	renderable->Render(renderer, MVP, ShaderType::SHADER_DEFAULT);

	delete MVP;
}
