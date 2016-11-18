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

	glm::vec2	getPosition()					{ return _position; }
	glm::vec2	getSize()						{ return _size; }

	void		setPosition(glm::vec2 position) { _position = position; }

	virtual void update() {}
	
	virtual void move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies) {}
	virtual void move() {}

	virtual bool attack(Unit* target);

	void takeDMG(int amount);

	int getHealth() { return _health; }

	virtual bool		CollideWithUnit		(Unit* unit, const std::vector<std::string> &levelData);

	virtual bool		collideWithUnits	(std::vector<Unit*>& enemies,
											 std::vector<Unit*>& humans,
								const std::vector<std::string> &levelData);

	virtual bool		collideWithLevel(const std::vector<std::string> &levelData);

	virtual void		draw(MexEngine::SpriteBatch& spriteBatch);



protected:

	glm::vec2			_getDistanceVec(Unit* target);


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




	int		_health, _damage;
	float	_attackSpeed;


	float _lastAttackTime;

	float				_speed;
	float				_depth;

	glm::vec2			_position;
	glm::vec2			_size;

	GLint				_textureID;

	MexEngine::Color	_color;

	glm::vec2			_direction;
	float				_dirChangingTime;

	float				_radius;
};

