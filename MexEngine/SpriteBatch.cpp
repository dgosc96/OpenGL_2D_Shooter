#include "SpriteBatch.h"

#include <algorithm>

namespace MexEngine {


	Glyph::Glyph(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint Texture, float Depth, const ColorRGBA8& color) :
		texture(Texture),
		depth(Depth)
	{

		topLeft.color = color;
		topLeft.setPosition(destRect.x, destRect.y + destRect.w);
		topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

		bottomLeft.color = color;
		bottomLeft.setPosition(destRect.x, destRect.y);
		bottomLeft.setUV(uvRect.x, uvRect.y);

		topRight.color = color;
		topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
		topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);

		bottomRight.color = color;
		bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
		bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);


	}


	SpriteBatch::SpriteBatch() :
		m_vbo(0),
		m_vao(0)
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init()
	{
		createVertexArray();

	}

	void SpriteBatch::begin(GlyphSortType sortType)
	{

		m_sortType = sortType;
		m_renderBatches.clear();
		m_glyphs.clear();

	}

	void SpriteBatch::end()
	{
		m_glyphPtrs.resize(m_glyphs.size());

		for (size_t i = 0; i < m_glyphs.size(); i++)
		{
			m_glyphPtrs[i] = &m_glyphs[i];
		}

		sortGlyphs();
		createRenderBatches();


	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color)
	{

		m_glyphs.emplace_back(destRect, uvRect, texture, depth, color);

	}

	void SpriteBatch::renderBatch()
	{
		glBindVertexArray(m_vao);

		for (size_t i = 0; i < m_renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, m_renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, m_renderBatches[i].offset, m_renderBatches[i].numVertices);
		}
		



		glBindVertexArray(0);
	}



	void SpriteBatch::createRenderBatches()
	{
		std::vector<Vertex> vertices;
		vertices.resize(m_glyphPtrs.size() * 6);

		if (m_glyphPtrs.empty())
		{
			return;
		}

		int offset = 0;
		int currVert = 0;

		m_renderBatches.emplace_back(offset, 6, m_glyphPtrs[0]->texture);
		vertices[currVert++] = m_glyphPtrs[0]->topLeft;
		vertices[currVert++] = m_glyphPtrs[0]->bottomLeft;
		vertices[currVert++] = m_glyphPtrs[0]->bottomRight;
		vertices[currVert++] = m_glyphPtrs[0]->topLeft;
		vertices[currVert++] = m_glyphPtrs[0]->topRight;
		vertices[currVert++] = m_glyphPtrs[0]->bottomRight;
		offset += 6;

		for (size_t currGlyph = 1; currGlyph < m_glyphPtrs.size(); currGlyph++)
		{	
			if ((m_glyphPtrs[currGlyph]->texture) != (m_glyphPtrs[currGlyph - 1]->texture))
			{
				m_renderBatches.emplace_back(offset, 6, m_glyphPtrs[currGlyph]->texture);
			}
			else
			{
				m_renderBatches.back().numVertices += 6;
			}

		
			vertices[currVert++] = m_glyphPtrs[currGlyph]->topLeft;
			vertices[currVert++] = m_glyphPtrs[currGlyph]->bottomLeft;
			vertices[currVert++] = m_glyphPtrs[currGlyph]->bottomRight;
			vertices[currVert++] = m_glyphPtrs[currGlyph]->bottomRight;
			vertices[currVert++] = m_glyphPtrs[currGlyph]->topRight;
			vertices[currVert++] = m_glyphPtrs[currGlyph]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		//upload the data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		//unbind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



	void SpriteBatch::createVertexArray()
	{
		if (m_vao == 0)
		{
			glGenVertexArrays(1, &m_vao);
		}
		glBindVertexArray(m_vao);

		if (m_vbo == 0)
		{
			glGenBuffers(1, &m_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);


		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

	
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));


		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));


		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));



		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs()
	{
		switch (m_sortType)
		{
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(m_glyphPtrs.begin(), m_glyphPtrs.end(), compareFrontToBack);
			break;

		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(m_glyphPtrs.begin(), m_glyphPtrs.end(), compareBackToBack);
			break;

		case GlyphSortType::TEXTURE:
			std::stable_sort(m_glyphPtrs.begin(), m_glyphPtrs.end(), compareTexture);
			break;
		}

	}




	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b)
	{
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToBack(Glyph* a, Glyph* b)
	{
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
	{
		return (a->texture < b->texture);
	}


}