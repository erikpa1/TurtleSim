#pragma once

#include "../prelude.h"

namespace simstudio
{

	class Stepper;
	class App;

	class Entity
	{

	public:
		String _name;
		String _uid;




	public:

		Entity();

		virtual void Init();
		virtual void Step(App& app, Stepper& stepper);
		virtual void TakeEntity();
		virtual void TakeEntity(Shared<Entity>& entity);
		virtual void PrintFinalStatistics();
	};

};