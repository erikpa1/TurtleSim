#include "loader.h"


#include "../serialization/safexml.h"

namespace simstudio {


	bool Loader::TakeEntity(Shared<Entity>& entity)
	{
		if (_activeEntity) {
			return false;
		}
		else {
			_activeEntity = entity;
			return true;
		}

	}
	void Loader::Step(App& app, Stepper& stepper)
	{

	}

	void Loader::FromXml(SafeXmlNode& node)
	{
		Entity::FromXml(node);

		_unloading_time = node.GetStringAttrib("processing_time", "");
		_targetBuffer = node.GetStringAttrib("target_buffer", "");
	}

	void Loader::_TryPickEntryEntity()
	{

	}
}