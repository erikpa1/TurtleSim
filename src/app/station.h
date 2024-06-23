#pragma once

#include "entity.h"
#include "anynumber.h"

namespace simstudio
{

	class Stepper;
	class App;
	class Mu;

	class SafeXmlNode;

	enum StationNotEnoughEntitiesMode
	{
		NON_OPERATIVE,
		HANDICAPED

	};

	class StationStatistics
	{
	public:
		uint64_t manufactured;
		uint64_t manufactured_time;
	};

	class Station : public Entity
	{

	public:

		FactoryType("station");
		~Station();

	public:


		AnyNumber _any_operation_time;

		long _manufacturing_end = LONG_MAX;

		String _operation_time_input = "00:00";

		bool _is_manufacturing = false;
		uint64_t _manufacturing_started = 0;

		StationNotEnoughEntitiesMode _not_enought_entities_mode = StationNotEnoughEntitiesMode::NON_OPERATIVE;

		StationStatistics _statistics;

		Shared<Entity> _activeEntity;





	public:

		static Shared<Station> New();

		String Type();

		virtual void Init();
		virtual void Step(App& app, Stepper& stepper) override;

		virtual void PrintFinalStatistics();

		virtual void FromXml(SafeXmlNode& node) override;
		virtual bool TakeEntity(Shared<Entity>& entity) override;
		virtual bool CanTakeEntity() override;

	private:
		void _StartManufacturing();

	};

};