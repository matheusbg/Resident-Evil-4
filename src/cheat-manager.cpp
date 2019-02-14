#include "common.h"
#include "cheat-manager.h"
#include "addresses.h"


namespace ResidentEvil4
{
    CheatManager::CheatManager () :
        m_player { *(Object**)g_playerAddress }, m_isWorking { true }
    {
    }

    CheatManager::~CheatManager ()
    {
    }


    void CheatManager::work ()
    {
        while (m_isWorking)
        {
            /* [Hack-ish]
               We need to keep updating the player's associated object pointer 
               because the game changes it in some cases (switching stages is an
               example). It is possible to hook the function(s) that changes
               it, but this will do for now. */
            m_player.m_associatedObject = *(Object**)g_playerAddress;

            manageHotkeys();
            manageTeleportCheat();
        }
    }

    void CheatManager::manageHotkeys ()
    {
        if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
        {
            m_player.toggleTeleport();
            Sleep(250);
        }
        if (GetAsyncKeyState(VK_F1) & 0x8000)
        {
            m_player.stunEnemies();
            Sleep(250);
        }
        if (GetAsyncKeyState(VK_F2) & 0x8000)
        {
            m_player.rapeEnemies();
            Sleep(250);
        }
        if (GetAsyncKeyState(VK_F3) & 0x8000)
        {
            m_player.teleportEnemies();
            Sleep(250);
        }
        if (GetAsyncKeyState (VK_F4) & 0x8000)
        {
            m_player.toggleESP ();
            Sleep (250);
        }
#ifdef _DEBUG
        if (GetAsyncKeyState(VK_F5) & 0x8000)
        {
            m_player.debug();
            Sleep(250);
        }
#endif
        if (GetAsyncKeyState(VK_SHIFT) & 0x8000 &&
            GetAsyncKeyState(VK_F11) & 0x8000)
        {
            Beep(750, 300);
            m_isWorking = false;
        }
    }

    void CheatManager::manageTeleportCheat ()
    {
        auto teleportIndex = GET_ENUM_VALUE(Player::TogglingCheats::TELEPORT);
        if ( m_player.m_togglingCheatsStatus[teleportIndex] )
        {
            if (GetAsyncKeyState(0x57 /* w */) & 0x8000)
            {
                m_player.teleportForward();
                Sleep (25);
            }
            if (GetAsyncKeyState(0x53 /* s */) & 0x8000)
            {
                m_player.teleportBackward();
                Sleep (25);
            }
            if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
            {
                m_player.teleportUpward();
                Sleep (25);
            }
            if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
            {
                m_player.teleportDownward();
                Sleep (25);
            }
        }
    }

}
