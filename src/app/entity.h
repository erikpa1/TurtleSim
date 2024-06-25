#pragma once

#include "../prelude.h"

namespace simstudio
{

	class Stepper;
	class App;

	class SafeXmlNode;

	class Entity
	{


	public:
		FactoryType("entity")

	public:



		String _name;
		String _uid;

		long _activeTime = 0;

		virtual ~Entity();

	public:

		Entity();

		virtual void Init();
		virtual void Step(App& app, Stepper& stepper);
		virtual bool TakeEntity(Shared<Entity>& entity);
		virtual bool CanTakeEntity();
		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);
		virtual String Type();

		virtual void FromXml(SafeXmlNode& xmlNode);

	};

};