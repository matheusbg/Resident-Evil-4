#ifndef CHEAT_MANAGER
#define CHEAT_MANAGER

#include "player.h"
#include "utils/singleton.h"


namespace ResidentEvil4
{
    class CheatManager : public Singleton<CheatManager>
    {
    public:
        CheatManager ();
        ~CheatManager ();


        bool isCheatToggled (const Player::TogglingCheats cheat)
        {
            return m_player.m_togglingCheatsStatus[ GET_ENUM_VALUE(cheat) ];
        }
        
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