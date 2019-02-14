#ifndef CHEAT_MANAGER
#define CHEAT_MANAGER

#include "player.h"
#include "utils/singleton.h"


namespace ResidentEvil4
{
    class CheatManager : public Singleton<CheatManager>
    {
        friend class Singleton<CheatManager>;
    
    public:
        bool isCheatToggled (const Player::TogglingCheats cheat) const
        {
            return m_player.m_togglingCheatsStatus[ GET_ENUM_VALUE(cheat) ];
        }
        
        void work ();

    protected:
    private:
        Player m_player;

        bool m_isWorking;


        CheatManager ();
        ~CheatManager ();
        
        void manageHotkeys ();
        void manageTeleportCheat ();

    };

}

#endif