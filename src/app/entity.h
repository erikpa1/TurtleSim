#pragma once

#include "../prelude.h"

#include "../math/vec4.h"

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


		Vec4 _pos_global;
		Vec4 _pos_local;


		String _name;
		String _uid;
		String _type;

		long _activeTime = 0;
		double _length = 1;

		virtual ~Entity();

	public:

		Entity();

		virtual void Init();
		virtual void Step(App& app, Stepper& stepper);
		virtual bool TakeEntity(Shared<Entity>& entity);
		virtual bool CanTakeEntity();

		virtual void WasTaken();

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);
		virtual String Type();

		virtual void FromXml(SafeXmlNode& xmlNode);


		String StringThis();

	};

};