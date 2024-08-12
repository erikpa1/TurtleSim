#pragma once

#include "../prelude.h"

#include "../math/vec4.h"



namespace simstudio
{

	class Stepper;
	class App;

	class SafeXmlNode;
	class SafeJson;

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

		App* _app = nullptr;

		Weak<Entity> _parent;

		Weak<Entity> _weakThis;

		virtual ~Entity();

	public:

		Entity();

		virtual void Init();
		virtual void Step(App& app, Stepper& stepper);
		virtual bool TakeEntity(Shared<Entity>& entity);
		virtual bool CanTakeEntity();


		virtual void EntityTaken(Shared<Entity>& entity);

		virtual void SetNewParent(Shared<Entity>& parent);



		virtual void WasTaken();

		virtual void PrintFinalStatistics(long statistics_delay, long simulation_duration);

		virtual void FromXml(SafeXmlNode& xmlNode);


		long GetSimSecond();
		long GetLastStepOffset();

		Array<Shared<Entity>> GetConnections();

		Shared<Entity>  GetEntity(String& uid);

		String StringThis();

		virtual Shared<Entity> PopChildEntity();

		virtual int ChildrenCount();


		virtual Shared<SafeJson> ToJson();


	};

};