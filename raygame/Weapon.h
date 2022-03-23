#pragma once
#include "Agent.h"
class Maze;
class PathFindComponent;
class Weapon :
	public Agent
{
public:
	Weapon(float x, float y, float speed, float maxForce, int color, Maze* maze);
	~Weapon();

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;
	void pickUpWeapon(Actor* weapon);
	bool getHasWeapon();
private:
	Maze* m_maze;
	Actor* m_weapon;
	bool m_hasWeapon = false;
	
};

