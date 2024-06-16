#pragma once

#include "../prelude.h"

namespace simstudio
{

    class Stepper;

    class Entity
    {

    public:
        String _name;
        String _uid;




    public:

        Entity();

        virtual void Init();
        virtual void Step(Stepper & stepper);
        virtual void PrintFinalStatistics();
    };

};