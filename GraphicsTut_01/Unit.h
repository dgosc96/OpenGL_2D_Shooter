#pragma once
#include <MexEngine/SpriteBatch.h>

class CollidingTile
{
public:
	CollidingTile(){}
	CollidingTile(glm::vec2 Pos, float Distance) : 
		pos(Pos),
		distToPlayer(Distance){}

	glm::vec2 pos;
	float distToPlayer = (float)INT_MAX;


};


class Unit
{
public:
	Unit();
	virtual ~Unit();

	virtual void move() {}

	virtual void draw(MexEngine::SpriteBatch& spriteBatch);

protected:

	virtual void		_collideWithLevel	(const std::vector<std::string> &levelData);

	virtual void		_checkTilePos	(const std::vector<std::string> &levelData,
										std::vector<CollidingTile> &collidingTiles,
										float x, float y);

	virtual void		_collideWithTile(glm::vec2 tilePos);

	void				_sortCollidingTiles(std::vector<CollidingTile> &collidingTiles,
											int left,
											int right);

	void				_swapCollidingTiles(std::vector<CollidingTile> &collidingTiles,
											int a,
											int b);

	float				_speed;
	float				_depth;

	glm::vec2			_position;
	glm::vec2			_size;

	GLint				_textureID;

	MexEngine::Color	_color;
};

