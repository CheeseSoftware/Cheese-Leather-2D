#include <algorithm>

#include <glm\gtc\matrix_transform.hpp>

#include "SpriteBatch.h"
#include "ShaderProgram.h"

SpriteBatch::SpriteBatch() {
}

SpriteBatch::~SpriteBatch() {

}


void SpriteBatch::init() {
	createVertexArrays();
}

void SpriteBatch::begin(GlyphSortType glyphSortType /*= GlyphSortType::TEXTURE*/) {
	m_glyphSortType = glyphSortType;

	m_renderBatches.clear();
	m_glyphData.clear();
	m_sortedGlyphIndices.clear(); 
}
void SpriteBatch::end() {
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4 &rectangle, const glm::vec4 &uvRectangle, const glm::mat4 &transformationMatrix_not, const glm::vec4 &color, GLuint glTexture, float depth) {

	glm::vec4 a(rectangle[0], rectangle[1], 1.f, 1.f);
	glm::vec4 b(rectangle[2], rectangle[1], 1.f, 1.f);
	glm::vec4 c(rectangle[0], rectangle[3], 1.f, 1.f);
	glm::vec4 d(rectangle[2], rectangle[3], 1.f, 1.f);

	glm::mat4 transformationMatrix = transformationMatrix_not;

	a = transformationMatrix * a;
	b = transformationMatrix * b;
	c = transformationMatrix * c;
	d = transformationMatrix * d;

	Vertex vertices[4] = {
		Vertex(a.x, a.y, 0, uvRectangle[0], uvRectangle[1], color.r, color.g, color.b, color.a),
		Vertex(b.x, b.y, 0, uvRectangle[2], uvRectangle[1], color.r, color.g, color.b, color.a),
		Vertex(c.x, c.y, 0, uvRectangle[0], uvRectangle[3], color.r, color.g, color.b, color.a),
		Vertex(d.x, d.y, 0, uvRectangle[2], uvRectangle[3], color.r, color.g, color.b, color.a)
	};

	Glyph glyph = { vertices[0], vertices[1], vertices[2], vertices[3], depth, glTexture};

	m_glyphData.push_back(glyph);
	m_sortedGlyphIndices.push_back(m_sortedGlyphIndices.size());
}


// Render all the sprites!
void SpriteBatch::renderBatch(ShaderProgram *shaderProgram) {
	
	glBindVertexArray(m_vao);

	

	for (auto renderBatch : m_renderBatches) {
		glm::mat4 mvp = glm::mat4(1.f);
		glUniformMatrix4fv(shaderProgram->getMVPUniform() , 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderBatch.texture);
		glUniform1i(shaderProgram->getTextureUniform(), 0);

		glDrawArrays(GL_TRIANGLES, renderBatch.offset, renderBatch.numVertices);
	}

	glBindVertexArray(0);
}

void SpriteBatch::createRenderBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(m_glyphData.size() * 6);

	if (m_glyphData.empty())
		return;

	//m_renderBatches.emplace_back(0, 6, m_glyphData[m_sortedGlyphIndices[0]].texture);

	GLuint currentTexture = 0;

	for (int i = 0; i < m_glyphData.size(); ++i) {
		Glyph &glyph = m_glyphData[m_sortedGlyphIndices[i]];

		if (glyph.texture != currentTexture || i == 0) {
			currentTexture = glyph.texture;

			m_renderBatches.emplace_back(i*6, 6, glyph.texture);
		}
		else {
			m_renderBatches.back().numVertices += 6;
		}


		vertices[i * 6 + 0] = glyph.vertices[0];
		vertices[i * 6 + 1] = glyph.vertices[2];
		vertices[i * 6 + 2] = glyph.vertices[1];
		vertices[i * 6 + 3] = glyph.vertices[1];
		vertices[i * 6 + 4] = glyph.vertices[2];
		vertices[i * 6 + 5] = glyph.vertices[3];
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBatch::createVertexArrays() {
	if (m_vao == 0)
		glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);
	
	if (m_vbo == 0)
		glGenBuffers(1, &m_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Positions
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	// Colors:
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	// UV:
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glBindVertexArray(0);
}

/********************************************
            Private:
**********************/

void SpriteBatch::sortGlyphs() {
	switch (m_glyphSortType) {

	default:
	case GlyphSortType::NONE:
		break;

	case GlyphSortType::FRONT_TO_BACK:
		std::stable_sort(m_sortedGlyphIndices.begin(), m_sortedGlyphIndices.end(), [this](u16 a, u16 b)->bool {
			return (this->m_glyphData[a].depth < this->m_glyphData[b].depth);
		});
		break;

	case GlyphSortType::BACK_TO_FRONT:
		std::stable_sort(m_sortedGlyphIndices.begin(), m_sortedGlyphIndices.end(), [this](u16 a, u16 b)->bool {
			return (this->m_glyphData[a].depth > this->m_glyphData[b].depth);
		});
		break;

	case GlyphSortType::TEXTURE:
		std::stable_sort(m_sortedGlyphIndices.begin(), m_sortedGlyphIndices.end(), [this](u16 a, u16 b)->bool {
			return (this->m_glyphData[a].texture < this->m_glyphData[b].texture);
		});
		break;
	}
}