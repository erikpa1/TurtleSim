
#include "../prelude.h"

namespace simstudio
{

    class Entity;

    class App
    {
    public:
        App();

        HashMap<Shared<Entity>> _entities;

        void Step();
        void AddEntity(Shared<Entity> entity);
    };

};