

#include "app.h"
#include "entity.h"

namespace simstudio
{

    App::App()
    {
    }

    void App::Step()
    {

        for (const auto & iter: _entities) {
            Shared<Entity> entity = iter.second;
            entity->Step();
            LogI << "Stepping on entity";
        }
    }

}