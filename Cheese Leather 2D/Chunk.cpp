#include <map>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Chunk.h"
#include "Vertex.h"
#include "Game.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "TextureHandler.h"
#include "Texture.h"

struct Quad {
	i8 x, y;
	i8 w, h;

	u16 baseTexture;
};



Chunk::Chunk()
{
}


Chunk::~Chunk(void) {
	if (m_blocks != nullptr)
		delete[] m_blocks;
	if (m_blockData != nullptr)
		delete[] m_blockData;

	if (m_vertexBuffer) {
		// TODO: Destroy vertex buffer.
	}
}

void Chunk::Render(glm::mat4 &mvp, Game *game, ShaderProgram *shaderProgram, Camera *camera) {
	if (m_isBlocksChanged) { // && !m_isBlockMeshCalculating) {
		// m_isBlockMeshCalculating = true;
		m_isBlocksChanged = false;

		loadMesh(game);
	}

	if (m_isMeshChanged) {
		m_isMeshChanged = false;

		loadVertexBuffer();
	}

	if (m_vertexBuffer != 0) {
		/*glm::mat4 mvp = glm::mat4(1.0f);
		mvp[0][0] = 1.f * 4.f;
		mvp[1][1] = 1.f * 4.f;

		glUniformMatrix4fv(
			0,
			1,
			GL_FALSE,
			&mvp[0][0]
			);*/
		////////////////////////////////////////GLuint matrixId = shaderProgram->addUniform("MVP");
		//GLuint MatrixID = glGetUniformLocation(programID, "MVP");

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		// For each model you render, since the MVP will be different (at least the M part)
		
		glUniformMatrix4fv(shaderProgram->getMVPUniform(), 1, GL_FALSE, &mvp[0][0]);

		// Load the texture using any two methods
		//GLuint Texture = loadBMP_custom("uvtemplate.bmp");
		///GLuint Texture = loadDDS("uvtemplate.DDS");
		//GLuint Texture = loadDDS
		// Get a handle for our "myTextureSampler" uniform
		/////////////////////////////////////GLuint textureId = shaderProgram->addUniform("myTextureSampler");
		//GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, game->getTextureHandler()->getBlockTexture(1)->getGlTexture());
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(shaderProgram->getTextureUniform(), 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
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

		glDrawArrays(GL_TRIANGLES, 0, m_vertexBufferSize);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}

}

void Chunk::NotifyAll() {
	// TODO: NotifyAll (generate blockData)
}

void Chunk::setBlock(i8 x, i8 y, u16 block) {
	if (m_blocks == nullptr)
	{
		if (block == 0)
			return;
		else
			initalizeBlocks();
	}

	m_blocks[y*cChunkSize + x] = block;

	m_isBlocksChanged = true;
}
//void placeBlockWithoutLock(i8 x, i8 y, u16 block);
//void placeBlockWithoutNotify(i8 x, i8 y, u16 block);
//void placeBlockWithoutNotifyAndLock(i8 x, i8 y, u16 block);
//u16 getBlockWithoutLock(i8 x, i8 y);
//std::mutex getBlockMutex();
u16 Chunk::getBlock(i8 x, i8 y) {
	if (m_blocks == nullptr)
		return 0;
	else
		return m_blocks[y* cChunkSize + x];
}

/******************************************
*              Private                    *
*******************************************/

void Chunk::initalizeBlocks() {
	m_blocks = new u16[cChunkSize*cChunkSize];

	memset(m_blocks, 0, cChunkSize*cChunkSize * sizeof(u16));
}

void Chunk::initalizeBlockData() {
	m_blockData = new BlockData[cChunkSize*cChunkSize];

	memset(m_blocks, 0, cChunkSize*cChunkSize * sizeof(BlockData));
}

void Chunk::loadMesh(Game *game) {
	std::vector<Vertex> vertices;
	std::vector<Quad> quads;
	/*std::map<i8vec2, Quad, i8vec2_hash, i8vec2_hash> quads;*/

	for (int x = 0; x < cChunkSize; ++x) {
		for (int y = 0; y < cChunkSize; ++y) {
			u16 block = m_blocks[x + y * cChunkSize];
			if (block != 0) {
				//Texture *texture = game->getTextureHandler()->getBlockTexture(block);
				Quad quad = { 16*x, 16*y, 16, 16, /*texture->getGlTexture()*/0 };
				quads.push_back(quad);
			}
		}
	}

	for (auto itA = quads.begin(); itA != quads.end(); ++itA) {

		auto &q = *itA; //itA->second;

		vertices.emplace_back(
			q.x, // x
			q.y, // y
			0, // depth
			0, // u
			0, // v
			0.5f, // r
			0.5f, // g
			0.5f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x + q.w, // x
			q.y + q.h, // y
			0, // depth
			1, // u
			1, // v
			0.5f, // r
			0.5f, // g
			0.5f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x + q.w, // x
			q.y, // y
			0, // depth
			1, // u
			0, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x, // x
			q.y, // y
			0, // depth
			0, // u
			0, // v
			0.5f, // r
			0.5f, // g
			0.5f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x, // x
			q.y + q.h, // y
			0, // depth
			0, // u
			1, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x + q.w, // x
			q.y + q.h, // y
			0, // depth
			1, // u
			1, // v
			0.5f, // r
			0.5f, // g
			0.5f, // b
			1.f // a
			);


	}


	vertices.shrink_to_fit();
	m_mesh = vertices;

	m_isMeshChanged = true;

}

void Chunk::loadVertexBuffer() {
	GLuint vertexBuffer;
	GLuint vertexBufferSize;

	{
		//std::lock_guard<std::mutex> guard(m_meshMutex);
		if (m_mesh.size() >= 0)
		{
			//////////////////////////////////////////
			// Send our vertices as a vertex buffer.//
			//////////////////////////////////////////
			glGenBuffers(0, &vertexBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

			// Give our vertices to OpenGL.
			glBufferData(GL_ARRAY_BUFFER, m_mesh.size() * sizeof(Vertex), m_mesh.data(), GL_DYNAMIC_DRAW);

			vertexBufferSize = m_mesh.size();
		}
		else
		{
			vertexBuffer = NULL;
		}
	}

	{
		//std::lock_guard<boost::mutex> guard(m_voxelContainerMutex);
		m_vertexBuffer = vertexBuffer;
		m_vertexBufferSize = vertexBufferSize;
	}

	return;
}

#pragma region merge quads
/*{
auto mergeQuad = [&](Quad &quadA, i8vec2 &posA)->bool {
bool changed = false;

for (auto itB = quads.begin(); itB != quads.end();) {
if (itA == itB) continue;

bool changedB = false;

i8vec2 posB = itB->first;
Quad& quadB = itB->second;

if (quadA.x == quadB.x) {
if (quadA.y + quadA.h == quadB.y && quadA.w == quadB.w) {
quadA.h += quadB.h;

changedB = true;
}
else if (quadB.y + quadB.h == quadA.y && quadA.w == quadB.w) {
quadA.h += quadB.h;
quadA.y = quadB.y;

changedB = true;
}
}
if (quadA.y == quadB.y) {
if (quadA.x + quadA.w = quadB.x && quadA.h == quadB.h) {
quadA.w += quadB.w;

changedB = true;
}
else if (quadB.x + quadB.w = quadA.x && quadA.h == quadB.h) {
quadA.w += quadB.w;
quadA.x = quadB.x;

changedB = true;
}
}

if (changedB)
{
changed = true;
it = quads.erase(posB);
}
else
++it;
}

posA.x = quadA.x;
posA.y = quadA.y;

return changed;
};


for (auto itA = quads.begin(); itA != quads.end(); ++itA) {
i8vec2 posA = itA->first;
Quad& quadA = itA->second;

if (mergeQuad(quadA, posA))
itA = quads.find(posA);

}
}*/

#pragma endregion