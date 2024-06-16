#pragma once
#include "entity.h"
#include "anynumber.h"

namespace simstudio
{

    class Stepper;

    enum StationNotEnoughEntitiesMode
    {
        NON_OPERATIVE,
        HANDICAPED

    };

    class StationStatistics
    {
    public:
        uint64_t manufactured;
        uint64_t manufactured_time;
    };

    class Station : public Entity
    {
    public:
        double _operation_time = 0;

        AnyNumber _any_operation_time;

        String _operation_time_input = "00:00";

        bool _is_manufacturing = false;
        uint64_t _manufacturing_started = 0;

        StationNotEnoughEntitiesMode _not_enought_entities_mode = StationNotEnoughEntitiesMode::NON_OPERATIVE;

        StationStatistics _statistics;

    public:
        virtual void Init();
        virtual void Step(Stepper &stepper);

        virtual void PrintFinalStatistics();
    };

};