

#include "app.h"
#include "entity.h"
#include "stepper.h"
namespace simstudio
{

    App::App()
    {
    }

    void App::Init()
    {
        for (const auto &iter : _entities)
        {
            iter.second->Init();
        }
    }

    void App::Step(Stepper &stepper)
    {

        for (const auto &iter : _entities)
        {
            auto entity = iter.second;
            entity->Step(stepper);
        }
    }

    void App::AddEntity(Shared<Entity> entity)
    {
        _entities[entity->_uid] = entity;
    }

    void App::PrintFinalStatistics()
    {
        LogI << "==============";
        LogI << "Final statistics:";
        for (const auto &iter : _entities)
        {
            iter.second->PrintFinalStatistics();
        }
    }

}