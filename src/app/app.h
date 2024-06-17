
#include "../prelude.h"

namespace simstudio
{

	class Stepper;
	class Entity;

	class App
	{
	public:
		App();

		HashMap<Shared<Entity>> _entities;

		HashMap<String> _connections;

		void Init();
		void Step(Stepper& stepper);
		void AddEntity(Shared<Entity> entity);


		void AddEntityConnection(String connA, String connB);


		void PrintFinalStatistics();
	};

};