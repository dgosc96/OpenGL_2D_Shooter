#pragma once

#include <glm/glm.hpp>
#include <MexEngine/SpriteBatch.h>
#include <MexEngine/ResourceManager.h> 

class Wall
{
public:
	//Wall(){}
	Wall(glm::vec2 position, glm::vec2 size, std::string texturePath);
	~Wall();

	void draw(MexEngine::SpriteBatch& spriteBatch);


protected:
	glm::vec2	_position;
	glm::vec2	_size;
	std::string _texturePath;
	//MexEngine::GLTexture _texture;
};

class Floor/* : public Wall*/
{
public:
	Floor(glm::vec2 position, glm::vec2 size, std::string texturePath);
	~Floor();
	void draw(MexEngine::SpriteBatch& spriteBatch);

protected:
	glm::vec2	_position;
	glm::vec2	_size;
	std::string _texturePath;
};
