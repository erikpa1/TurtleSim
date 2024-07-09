#pragma once
#include "entity.h"

namespace simstudio {

	class Loader : public Entity {

	public:
		FactoryType("loader");
		FactoryNew(Loader);

		Shared<Entity> _loaded;

	public:

		void TakeLoadedEntity(Shared<Entity> entity);

		virtual void FromXml(SafeXmlNode& node) override;

	private:

		void _TryPickEntryEntity();

	};


}