#ifndef CHEAT_MANAGER
#define CHEAT_MANAGER

#include "player.h"


namespace ResidentEvil4
{
    class CheatManager
    {
    public:
        CheatManager ();
        ~CheatManager ();


        void work ();

    protected:
    private:
        Player m_player;

        bool m_isWorking;


        void manageHotkeys ();
        void manageTeleportCheat ();

    };

}

#endif