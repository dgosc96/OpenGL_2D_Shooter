#include "Wall.h"



Wall::Wall(glm::vec2 position, glm::vec2 size, std::string texturePath) :

	_position		(position),
	_size			(size),
	_texturePath	(texturePath)
{
	//_texture = MexEngine::ResourceManager::getTexture(_texturePath);

}


Wall::~Wall()
{
}


void Wall::draw(MexEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static MexEngine::GLTexture _texture = MexEngine::ResourceManager::getTexture(_texturePath);
	//static std::string _textureFilePath = _texturePath;
	//if (_textureFilePath != _texturePath)
	//{
	//	_texture = MexEngine::ResourceManager::getTexture(_texturePath);
	//	_textureFilePath = _texturePath;
	//}
	
	MexEngine::Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, _size.x, _size.y);

	spriteBatch.draw(posAndSize, uv, _texture.id, 0.0f, color);



}



Floor::Floor(glm::vec2 position, glm::vec2 size, std::string texturePath) :
	_position(position),
	_size(size),
	_texturePath(texturePath)

{

	//_position = position; 
	//_size = size;
	//_texturePath = texturePath;

	//_texture = MexEngine::ResourceManager::getTexture(_texturePath);

}


Floor::~Floor()
{
}
//
//
//
//Floor::~Floor()
//{
//}
//
//
void Floor::draw(MexEngine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	static MexEngine::GLTexture texture = MexEngine::ResourceManager::getTexture(_texturePath);
	//static std::string _textureFilePath = _texturePath;
	//if (_textureFilePath != _texturePath)
	//{
	//	_texture = MexEngine::ResourceManager::getTexture(_texturePath);
	//	_textureFilePath = _texturePath;
	//}

	MexEngine::Color color;

	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, _size.x, _size.y);

	spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);



}