#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

#include <array>
#include <memory>
#include <functional>


namespace ResidentEvil4
{
    constexpr float DEFAULT_PLAYER_TELEPORT_DISTANCE = 300.0f,
                    DISTANCE_RATE_OF_CHANGE = 100.0f;


#define GET_ENUM_VALUE(enumType) static_cast<unsigned long>(enumType)


    class Player : Object
    {
    public:
        Player (Object* const associatedObject);
        ~Player ();


        void toggleTeleport ();
        void teleportForward ();
        void teleportBackward ();
        void teleportUpward ();
        void teleportDownward ();
        void increaseTeleportDistance ();
        void decreaseTeleportDistance ();

        void stunEnemies () const;
        void rapeEnemies () const;
        void teleportEnemies() const;


        friend class CheatManager;

    protected:
    private:
        enum class TogglingCheatTypes
        {
            TELEPORT,
            END
        };

        
        // Hack-ish. Maybe there is a better (OO) way?
        //
        Object* m_associatedObject;

        // 0: disabled; 1: enabled. All toggling cheats are disabled by default.
        //
        std::array<bool, GET_ENUM_VALUE(TogglingCheatTypes::END)> m_togglingCheatsStates {};

        float m_teleportDistance;

        std::unique_ptr<unsigned long> m_dummy = std::make_unique<unsigned long>();


        void traverseObjects (std::function<void (Object* const)> performAction) const;
        void hitEnemies (const unsigned char weaponType) const;

    };

}

#endif