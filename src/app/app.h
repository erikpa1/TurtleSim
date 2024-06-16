
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

        void Init();
        void Step(Stepper &stepper);
        void AddEntity(Shared<Entity> entity);

        void PrintFinalStatistics();
    };

};