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

        void Step(Stepper & stepper);
    };

};