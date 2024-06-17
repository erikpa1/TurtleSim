
#include "entity.h"
#include "stepper.h"
#include "app.h"

namespace simstudio
{

	Entity::Entity()
	{
	}

	void Entity::Init()
	{
	}

	void Entity::Step(App& app, Stepper& stepper)
	{
	}

	void Entity::TakeEntity()
	{
		LogI << _uid << " is taking some entity";
	}

	void Entity::TakeEntity(Shared<Entity>& entity)
	{
	}

	void Entity::PrintFinalStatistics()
	{
	}

}