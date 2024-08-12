
#include "entity.h"
#include "stepper.h"
#include "app.h"

#include "../serialization/prelude.h"
#include "../utils/crypto.h"

#include "../serialization/safejson.h"


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
		if (_app) {
			return _app->_stepper.GetStepSecond();
		}
		return 0;
	}

	long Entity::GetLastStepOffset()
	{
		if (_app) {
			return _app->_stepper.GetLastStepDiff();
		}
		return 0;
	}

	Array<Shared<Entity>> Entity::GetConnections()
	{
		if (_app) {
			return _app->GetConnectedEntities(_uid);
		}
		return {};
	}

	Shared<Entity> Entity::GetEntity(String& uid)
	{
		if (_app) {
			if (_app->_entities.contains(uid)) {
				return _app->_entities[uid];
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

		const auto& json_ref = json.get();
		json_ref->WriteString("uid", this->_uid);
		json_ref->WriteString("name", this->_name);
		json_ref->WriteString("type", this->_type);
		json_ref->WriteFloat3("position", 0, 0, 0);
		json_ref->WriteFloat3("scale", 1, 1, 1);


		return json;
	}

}