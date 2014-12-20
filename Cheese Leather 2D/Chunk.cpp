#include <map>

#include "Chunk.h"

#include "Vertex.h"

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

	if (m_vertexBuffer)
	{
		// TODO: Destroy vertex buffer.
	}
}

void Chunk::Render(Game *game) {
	// TODO: Fix proper chunk rendering.

	GLuint vertexbuffer;
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
}

void Chunk::NotifyAll() {
	// TODO: NotifyAll (generate blockData)
}

void Chunk::placeBlock(i8 x, i8 y, u16 block) {
	if (m_blocks == nullptr)
	{
		if (block == 0)
			return;
		else
			initalizeBlocks();
	}

	m_blocks[y*cChunkSize + x] = block;

	m_blocksChanged = true;
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

void Chunk::loadMesh() {
	std::vector<Vertex> vertices;
	std::vector<Quad> quads;
	/*std::map<i8vec2, Quad, i8vec2_hash, i8vec2_hash> quads;*/

	for (int x = 0; x < cChunkSize; ++x) {
		for (int y = 0; y < cChunkSize; ++y) {
			if (m_blocks[x + y * cChunkSize] != 0) {
				Quad quad = { x, y, 1, 1, 0 };
				quads.push_back(quad);
			}
		}
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

	for (auto itA = quads.begin(); itA != quads.end(); ++itA) {

		auto &q = *itA; //itA->second;

		vertices.emplace_back(
			q.x, // x
			q.y, // y
			0, // depth
			q.baseTexture % 16, // u
			q.baseTexture / 16, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x + q.w, // x
			q.y + q.h, // y
			0, // depth
			q.baseTexture % 16 + 16, // u
			q.baseTexture / 16 + 16, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x + q.w, // x
			q.y, // y
			0, // depth
			q.baseTexture % 16 + 16, // u
			q.baseTexture / 16, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x, // x
			q.y, // y
			0, // depth
			q.baseTexture % 16, // u
			q.baseTexture / 16, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x, // x
			q.y + q.h, // y
			0, // depth
			q.baseTexture % 16, // u
			q.baseTexture / 16 + 16, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);

		vertices.emplace_back(
			q.x + q.w, // x
			q.y + q.h, // y
			0, // depth
			q.baseTexture % 16 + 16, // u
			q.baseTexture / 16 + 16, // v
			1.f, // r
			1.f, // g
			1.f, // b
			1.f // a
			);


	}


	vertices.shrink_to_fit();
	m_mesh = vertices;

}

void Chunk::loadVertexBuffer() {

}