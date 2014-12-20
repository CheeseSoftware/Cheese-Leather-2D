#include "PlayState.h"

#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IRenderer.h"
#include "RandomTestRenderable.h"

#include "ShaderProgram.h"
#include "Shader.h"

PlayState::PlayState()
{
	this->renderable = new RandomTestRenderable();

	std::vector<Shader> defaultShaders;
	defaultShaders.emplace_back(GL_VERTEX_SHADER, "shaders\\default_Vertex.glsl");
	defaultShaders.emplace_back(GL_FRAGMENT_SHADER, "shaders\\default_Fragment.glsl");

	std::vector<std::string> defaultUniforms;
	defaultUniforms.push_back("MVP");
	defaultUniforms.push_back("baseTexture");

	shaderProgram = new ShaderProgram(std::move(defaultShaders));
	shaderProgram->addUniforms(defaultUniforms);
}


PlayState::~PlayState()
{
}

void PlayState::Update()
{

}

void PlayState::Draw(State *state)
{
	shaderProgram->bind();

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat3 MVP;

	renderable->Render(MVP);

	shaderProgram->unbind();
}
