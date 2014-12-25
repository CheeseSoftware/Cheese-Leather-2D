#include <vector>

#include "Vertex.h"
#include "types.h"

class SpriteBatch {
	void draw(glm::vec4 rectangle, glm::vec4 uvRectangle, glm::mat4 spriteMatrix, glm::vec4 color, float depth));

	void sortGlyphs(); 

	// Render all the sprites!
	void renderBatch();

	private:
		struct Glyph;

		std::vector<Glyph> glyphData;
		std::vector<u16> sortedGlyphIndices;

		struct Glyph {
			Vertex vertices[4];
			float depth;
		};
};