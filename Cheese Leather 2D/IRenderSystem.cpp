#include "IRenderSystem.h"

#include "IComponent.h"
#include "Vertex.h"

#include "Game.h"
#include "ShaderProgram.h"
#include "TextureHandler.h"
#include "Texture.h"

void RenderSystemSprite::render(Game *game, ShaderProgram *shaderProgram, Entity *entity, IComponent **components) {
	ComponentSprite *componentSprite = reinterpret_cast<ComponentSprite*>(components[0]);

	// Update spriteMatrix/modelMatrix
	if (componentSprite->needsMatrixUpdate) {
		componentSprite->needsMatrixUpdate = false;

		glm::vec3 translate = glm::vec3(componentSprite->position, 0.f);
		glm::vec3 scale = glm::vec3(componentSprite->scale, 1.f);
		float angle = componentSprite->angle;

		componentSprite->spriteMatrix = glm::translate(glm::mat4(1.f), translate);
		componentSprite->spriteMatrix *= glm::rotate(glm::mat4(1.f), angle, glm::vec3(0.f, 0.f, 1.f));
		componentSprite->spriteMatrix *= glm::scale(glm::mat4(1.f), scale);
	}

	if (componentSprite->vertexBuffer == 0) {
		Vertex quad[] = {
			Vertex(0, 0, 0, 0, 0, 1.f, 1.f, 1.f, 1.f),
			Vertex(0, 1, 0, 0, 1, 1.f, 1.f, 1.f, 1.f),
			Vertex(1, 1, 0, 1, 1, 1.f, 1.f, 1.f, 1.f),

			Vertex(0, 0, 0, 0, 0, 1.f, 1.f, 1.f, 1.f),
			Vertex(1, 1, 0, 1, 1, 1.f, 1.f, 1.f, 1.f),
			Vertex(1, 0, 0, 1, 0, 1.f, 1.f, 1.f, 1.f)
		};


		glGenBuffers(1, &componentSprite->vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, componentSprite->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), quad, GL_STATIC_DRAW);
	}

	if (&componentSprite->vertexBuffer != 0) {

		glm::mat4 mvp = componentSprite->spriteMatrix;

		glUniformMatrix4fv(shaderProgram->getMVPUniform(), 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, game->getTextureHandler()->getBlockTexture(1)->getGlTexture());

		glUniform1i(shaderProgram->getTextureUniform(), 0);

		glBindBuffer(GL_ARRAY_BUFFER, componentSprite->vertexBuffer);
		{
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
				reinterpret_cast<void*>(offsetof(Vertex, position)));
		}
	{
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, color)));
	}
	{
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, uv)));
	}

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}


}

std::vector<std::type_index> RenderSystemSprite::getComponentTypes() {

	static const std::type_index type_index_array[] = {
		typeid(ComponentSprite)
	};

	static const std::vector<std::type_index> componentTypes(type_index_array, type_index_array + sizeof(type_index_array) / sizeof(type_index_array[0]));

	return componentTypes;
}
