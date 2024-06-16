

#include "app.h"
#include "entity.h"
#include "stepper.h"
namespace simstudio
{

    App::App()
    {
    }

    void App::Step(Stepper & stepper)
    {

        for (const auto &iter : _entities)
        {
            // Shared<Entity> entity = iter.second;
            // entity->Step(stepper);
            LogI << "Stepping on entity";
        }
    }

    void App::AddEntity(Shared<Entity> entity)
    {
        _entities[entity->_uid] = entity;
    }

}