//#include <algorithm>
//
//#include "SpriteBatch.h"
//
//
//void SpriteBatch::draw(glm::vec4 rectangle, glm::vec4 uvRectangle, glm::mat4 spriteMatrix, glm::vec4 color, float depth) {
//	Vertex vertices[4] = {
//		Vertex(rectangle[0], rectangle[1], 0, uvRectangle[0], uvRectangle[1], color.r, color.g, color.b, color.a),
//		Vertex(rectangle[2], rectangle[1], 0, uvRectangle[2], uvRectangle[1], color.r, color.g, color.b, color.a),
//		Vertex(rectangle[0], rectangle[3], 0, uvRectangle[0], uvRectangle[3], color.r, color.g, color.b, color.a),
//		Vertex(rectangle[2], rectangle[3], 0, uvRectangle[2], uvRectangle[3], color.r, color.g, color.b, color.a)
//	};
//
//	Glyph glyph = { vertices[0], vertices[1], vertices[2], vertices[3], depth };
//
//	glyphData.push_back(glyph);
//	sortedGlyphIndices.push_back(sortedGlyphIndices.size());
//}
//
//
//// Render all the sprites!
//void SpriteBatch::renderBatch() {
//
//	std::sort(sortedGlyphIndices.begin(), sortedGlyphIndices.end(), [this](u16 a, u16 b)->bool {
//		return (this->glyphData[a].depth > this->glyphData[b].depth);
//	});
//
//
//}