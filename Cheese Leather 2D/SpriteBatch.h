#include <vector>
#include <glm\glm.hpp>

#include "Vertex.h"
#include "types.h"

class ShaderProgram;

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	// FRONT_TO_BACK_THEN_TEXTURE
	BACK_TO_FRONT,
	// BACK_TO_FRONT_THEN_TEXTURE
	TEXTURE
};

struct Glyph {
	Vertex vertices[4];
	float depth;
	GLuint texture;
};

struct RenderBatch {
	RenderBatch(GLuint offset, GLuint numVertices, GLuint texture)
		: offset(offset)
		, numVertices(numVertices)
		, texture(texture)
	{
	}

	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch {
public:
	SpriteBatch();
	~SpriteBatch();

	void init();

	void begin(GlyphSortType glyphSortType = GlyphSortType::TEXTURE);
	void end();

	void draw(const glm::vec4 &rectangle, const glm::vec4 &uvRectangle, const glm::mat4 &transformationMatrix, const glm::vec4 &color, GLuint glTexture, float depth);
	

	// Render all the sprites!
	void renderBatch(ShaderProgram *shaderProgram);
	void createRenderBatches();
	void createVertexArrays();


	private:
		void sortGlyphs();

		std::vector<Glyph> m_glyphData;
		std::vector<u16> m_sortedGlyphIndices;

		std::vector<RenderBatch> m_renderBatches;

		GLuint m_vao = 0;
		GLuint m_vbo = 0;

		GlyphSortType m_glyphSortType;
};