#include "StateMachineComponent.h"
#include "Actor.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "PathfindComponent.h"
#include "Transform2D.h"

void StateMachineComponent::start()
{
	Component::start();

	m_seekComponent = getOwner()->getComponent<SeekComponent>();
	m_seekForce = m_seekComponent->getSteeringForce();

	m_wanderComponent = getOwner()->getComponent<WanderComponent>();
	m_wanderForce = m_wanderComponent->getSteeringForce();

	m_pathFindComponent = getOwner()->getComponent<PathfindComponent>();

	m_currentState = WANDER;
}

void StateMachineComponent::update(float deltaTime)
{
	Component::update(deltaTime);
	MathLibrary::Vector2 weaponPos;
	MathLibrary::Vector2 targetPos = m_seekComponent->getTarget()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 ownerPos = getOwner()->getTransform()->getWorldPosition();
	float distanceFromTarget = (targetPos - ownerPos).getMagnitude();
	float distanceFromWeapon = (weaponPos - ownerPos).getMagnitude();

	bool targetInRange = distanceFromTarget <= m_seekRange;
	bool targetInPathRange = distanceFromTarget <= m_pathFindRange;
	bool weaponInRange = distanceFromWeapon <= m_seekRange;

	switch (m_currentState)
	{
	case WANDER:
		//make sure the steering force is off
		m_seekComponent->setSteeringForce(0);
		//Sets the enemy to start wandering 
		m_wanderComponent->setSteeringForce(m_wanderForce);
		//Remove the ability to path find
		m_pathFindComponent->setEnabled(false);

		if (targetInPathRange)
			setCurrentState(SEEKPLAYER);

		break;

	//case SEEKWEAPON:
	//	m_seekComponent->setSteeringForce(m_seekForce);
	//	m_wanderComponent->setSteeringForce(0);

	//	if (targetInRange)
	//		setCurrentState(SEEKPLAYER);

	//	break;


	case SEEKPLAYER:
		//make sure the steering force is off
		m_seekComponent->setSteeringForce(0);
		//removed the ability to wander
		m_wanderComponent->setSteeringForce(0);
		//sets the enemy to start pathfinding 
		m_pathFindComponent->setEnabled(true);

		if (!targetInPathRange)
			setCurrentState(WANDER);

		break;
	}
}
