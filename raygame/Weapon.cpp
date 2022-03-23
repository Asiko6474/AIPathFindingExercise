#include "Weapon.h"
#include "MazeScene.h"
#include "raylib.h"
#include "SpriteComponent.h"
#include "Transform2D.h"
#include <string.h>
#include "Wall.h"
#include "MoveComponent.h"
#include "Collider.h"

Weapon::Weapon(float x, float y, float speed, float maxForce, int color, Maze* maze) : Agent(x, y, "Gun", speed, maxForce)
{
	m_maze = maze;
	getTransform()->setScale({ Maze::TILE_SIZE,Maze::TILE_SIZE });
	addComponent(new SpriteComponent("Images/enemy.png"));
}

Weapon::~Weapon()
{
}

void Weapon::update(float deltaTime)
{
	Agent::update(deltaTime);
}

void Weapon::draw()
{
	Agent::draw();
}

void Weapon::onCollision(Actor* other)
{
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getTransform()->getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		//getTransform()->setWorldPostion(getTransform()->getWorldPosition() - getMoveComponent()->getVelocity().getNormalized() * -.05f);
		applyForce(getCollider()->getCollisionNormal() * -1 * getMoveComponent()->getVelocity().getMagnitude());
	}

	if(strcmp(other->getName(), "Gun") == 0)
		pickUpWeapon(other);
}

void Weapon::pickUpWeapon(Actor* weapon)
{
	m_weapon = weapon;
	m_hasWeapon = true;
}

bool Weapon::getHasWeapon()
{
	return m_hasWeapon;
}
