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

	glm::vec2	getPosition()					{ return m_position; }
	glm::vec2	getCenterPosition()				{ return (m_position + (m_size / 2.0f)); }

	glm::vec2	getSize()						{ return m_size; }

	void		setPosition(glm::vec2 position) { m_position = position; }

	virtual void update() {}
	
	virtual void move(std::vector<Unit*>& enemies, std::vector<Unit*>& allies) {}
	virtual void move() {}

	virtual bool attack(Unit* target);

	void		 takeDMG(int amount);

	int			 getHealth() { return m_health; }

	virtual bool		CollideWithUnit		(Unit* unit, const std::vector<std::string> &levelData);

	virtual bool		collideWithUnits	(std::vector<Unit*>& enemies,
											 std::vector<Unit*>& humans,
											 const std::vector<std::string> &levelData);

	virtual bool		collideWithLevel(const std::vector<std::string> &levelData);

	virtual void		draw(MexEngine::SpriteBatch& spriteBatch);



protected:

	glm::vec2			getDistanceVec(Unit* target);


	virtual void		checkTilePos	(const std::vector<std::string> &levelData,
										std::vector<CollidingTile> &collidingTiles,
										float x, float y);

	virtual void		collideWithTile(glm::vec2 tilePos);

	void				sortCollidingTiles(std::vector<CollidingTile> &collidingTiles,
											int left,
											int right);

	void				swapCollidingTiles(std::vector<CollidingTile> &collidingTiles,
											int a,
											int b);

	virtual bool		canIMove(glm::vec2 &newPosition, const std::vector<std::string> &leveldata);


	int					m_health, m_damage;
	float				m_attackSpeed;


	float				m_lastAttackTime;

	float				m_speed;
	float				m_depth;

	glm::vec2			m_position;
	glm::vec2			m_size;

	GLint				m_textureID;

	MexEngine::ColorRGBA8	m_color;

	glm::vec2			m_direction;
	float				m_dirChangingTime;

	float				m_radius;
};

