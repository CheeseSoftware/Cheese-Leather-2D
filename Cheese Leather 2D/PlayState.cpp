#include "PlayState.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "World.h"


PlayState::PlayState()
{
	world = new World();
}


PlayState::~PlayState()
{
}

void PlayState::Update()
{

}

void PlayState::Draw(Game *game)
{
	/*// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat3 MVP;*/
	world->Render(game);
}
