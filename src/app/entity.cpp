
#include "entity.h"
#include "stepper.h"
#include "world.h"

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

	void Entity::Step(World& app, Stepper& stepper)
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

	int Entity::GetStateInt()
	{
		return 0;
	}


	void Entity::EntityTaken(Shared<Entity>& entity)
	{

	}

	void Entity::SetNewParent(Shared<Entity>& parent)
	{
		_pos_local.Nullify();
		_pos_global = _pos_global;
		_parent = parent;
	}

	void Entity::WasTaken()
	{
		_pos_local.Nullify();
	}

	void Entity::PrintFinalStatistics(long statistics_delay, long simulation_duration)
	{

	}

	void Entity::FromXml(SafeXmlNode& xmlNode)
	{
		_uid = xmlNode.GetStringAttrib("uid", "");
		_name = xmlNode.GetStringAttrib("name", "");
	}

	long Entity::GetSimSecond()
	{
		if (_world) {
			return _world->_stepper.GetStepSecond();
		}
		return 0;
	}

	long Entity::GetLastStepOffset()
	{
		if (_world) {
			return _world->_stepper.GetLastStepDiff();
		}
		return 0;
	}

	Array<Shared<Entity>> Entity::GetConnections()
	{
		if (_world) {
			return _world->GetConnectedEntities(_uid);
		}
		return {};
	}

	Shared<Entity> Entity::GetEntity(String& uid)
	{
		if (_world) {
			if (_world->_entities.contains(uid)) {
				return _world->_entities[uid];
			}
		}

		return Shared<Entity>();
	}

	String Entity::StringThis()
	{
		return F("[{}][{}]", _type, _uid);
	}

	Shared<Entity> Entity::PopChildEntity()
	{
		return Shared<Entity>();
	}

	int Entity::ChildrenCount()
	{
		return 0;
	}

	Shared<SafeJson> Entity::ToJson()
	{
		const auto json = Share<SafeJson>();

		json->WriteString("uid", this->_uid);
		json->WriteString("name", this->_name);
		json->WriteString("type", Type());
		json->WriteFloat3("position", 0, 0, 0);
		json->WriteFloat3("scale", 1, 1, 1);

		return json;
	}

	void Entity::FromJson(const Shared<SafeJson>& json)
	{
		auto json_ref = *json;

		_uid = json_ref.GetString("uid", _uid);
		_name = json_ref.GetString("name", _name);

	}


}