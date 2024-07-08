
#include "entity.h"
#include "stepper.h"
#include "app.h"

#include "../serialization/prelude.h"
#include "../utils/crypto.h"

namespace simstudio
{
	Entity::~Entity()
	{
	}
	Entity::Entity()
	{
		_uid = Crypto::Uuid_V4();
	}

	void Entity::Init()
	{
	}

	void Entity::Step(App& app, Stepper& stepper)
	{
	}


	bool Entity::TakeEntity(Shared<Entity>& entity)
	{
		return false;
	}

	bool Entity::CanTakeEntity()
	{
		return false;
	}

	void Entity::WasTaken()
	{
		_pos_local.Nullify();
	}

	void Entity::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{
	}

	String Entity::Type()
	{
		return "entity";
	}

	void Entity::FromXml(SafeXmlNode& xmlNode)
	{
		_uid = xmlNode.GetStringAttrib("uid", "");
		_name = xmlNode.GetStringAttrib("name", "");
	}

	String Entity::StringThis()
	{
		return F("[{}][{}]", _type, _uid);
	}

}