#include "Sprite.h"

#include "Vertex.h"

#include <cstddef>

Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0) {
		glDeleteBuffers(1, &_vboID);
	}

}


void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (_vboID == 0) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	//First Triangle
	vertexData[0].position.x = x + width;
	vertexData[0].position.y = y + height;

	vertexData[1].position.x = x;
	vertexData[1].position.y = y + height;

	vertexData[2].position.x = x;
	vertexData[2].position.y = y;

	//Second Triangle
	vertexData[3].position.x = x;
	vertexData[3].position.y = y;

	vertexData[4].position.x = x + width;
	vertexData[4].position.y = y;

	vertexData[5].position.x = x + width;
	vertexData[5].position.y = y + height;


	for (int i = 0; i < 6; i++) {
		vertexData[i].color.r = 41;
		vertexData[i].color.g = 54;
		vertexData[i].color.b = 231;
		vertexData[i].color.a = 255;

	}

	vertexData[1].color.r = 122;
	vertexData[1].color.g = 123;
	vertexData[1].color.b = 255;
	vertexData[1].color.a = 255;

	vertexData[3].color.r = 233;
	vertexData[3].color.g = 50;
	vertexData[3].color.b = 156;
	vertexData[3].color.a = 255;

	vertexData[0].color.r = 0;
	vertexData[0].color.g = 50;
	vertexData[0].color.b = 156;
	vertexData[0].color.a = 255;

	vertexData[4].color.r = 123;
	vertexData[4].color.g = 122;
	vertexData[4].color.b = 255;
	vertexData[4].color.a = 255;

	vertexData[5].color.r = 0;
	vertexData[5].color.g = 50;
	vertexData[5].color.b = 156;
	vertexData[5].color.a = 255;

	vertexData[2].color.r = 233;
	vertexData[2].color.g = 50;
	vertexData[2].color.b = 156;
	vertexData[2].color.a = 255;



	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}