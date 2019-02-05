#include "common.h"
#include "player.h"
#include "addresses.h"


namespace ResidentEvil4
{
    Player::Player (Object* const associatedObject) :
        m_associatedObject { associatedObject },
        m_teleportDistance { DEFAULT_PLAYER_TELEPORT_DISTANCE }
    {
    }

    Player::~Player ()
    {
    }


    void Player::toggleTeleport ()
    {
        auto teleportIndex = GET_ENUM_VALUE(TogglingCheats::TELEPORT);
        m_togglingCheatsStatus[teleportIndex] = !m_togglingCheatsStatus[teleportIndex];
    }

    void Player::toggleESP ()
    {
        auto ESPIndex = GET_ENUM_VALUE (TogglingCheats::ESP);
        m_togglingCheatsStatus[ESPIndex] = !m_togglingCheatsStatus[ESPIndex];
    }
    
    void Player::teleportForward ()
    {
        auto myPosition  = &m_associatedObject->m_position;
        auto myDirection = &m_associatedObject->m_direction;
        myPosition->m_x += m_teleportDistance * myDirection->m_x;
        myPosition->m_y += m_teleportDistance * myDirection->m_y;
    }

    void Player::teleportBackward ()
    {
        auto myPosition  = &m_associatedObject->m_position;
        auto myDirection = &m_associatedObject->m_direction;
        myPosition->m_x += m_teleportDistance * -myDirection->m_x;
        myPosition->m_y += m_teleportDistance * -myDirection->m_y;
    }

    void Player::teleportUpward ()
    {
        auto myPosition = &m_associatedObject->m_position;
        myPosition->m_z += DEFAULT_PLAYER_TELEPORT_DISTANCE * 4.0f;
    }

    void Player::teleportDownward ()
    {
        auto myPosition = &m_associatedObject->m_position;
        myPosition->m_z -= DEFAULT_PLAYER_TELEPORT_DISTANCE * 4.0f;
    }

    void Player::increaseTeleportDistance ()
    {
        m_teleportDistance += DISTANCE_RATE_OF_CHANGE;
    }

    void Player::decreaseTeleportDistance ()
    {
        m_teleportDistance -= DISTANCE_RATE_OF_CHANGE;
    }

    void Player::traverseObjects (std::function<void (Object* const)> performAction) const
    {
        auto objectsArrayBase   = *(unsigned long*)g_objectsArrayBaseAddress;
        auto objectsArraySize   = *(unsigned int*)g_objectsArraySizeAddress,
             objectsArrayOffset = *(unsigned int*)g_objectsArrayOffsetAddress;

        for (unsigned int i = 1; i < objectsArraySize; ++i)
        {
            auto object = reinterpret_cast<Object*>(
                objectsArrayBase + objectsArrayOffset * i
            );
            performAction(object);
        }
    }
    
    void Player::hitEnemies (const unsigned char weaponType) const
    {
        traverseObjects(
            [&](Object* const object)
            {
                auto objectType = *(unsigned long*)object;
                if ( objectType == GET_ENUM_VALUE(ObjectTypes::ENTITY) )
                {
                    object->m_unknownPtr = m_dummy.get();
                    object->m_isHitted = true;
                    object->m_weaponTypeHittedBy = weaponType;
                }
            }
        );
    }
    
    void Player::stunEnemies () const
    {
        hitEnemies(0);
    }
    
    void Player::rapeEnemies () const
    {
        hitEnemies(10);
    }

    void Player::teleportEnemies() const
    {
        traverseObjects(
            [&](Object* const object)
            {
                auto objectType = *(unsigned long*)object;
                if ( objectType == GET_ENUM_VALUE(ObjectTypes::ENTITY) )
                {
                    auto playerPosition = m_associatedObject->m_position;
                    playerPosition.m_x += 5000.0f * m_associatedObject->m_direction.m_x;
                    playerPosition.m_y += 5000.0f * m_associatedObject->m_direction.m_y;
                    object->m_position = playerPosition;
                }
            }
        );
    }

    Object* Player::getClosestEnemy () const
    {
        float lowestDistance = 999999.0f;
        Object* closestEnemy = nullptr;

        traverseObjects(
            [&](Object* const object)
            {
                auto objectType = *(unsigned long*)object;
                if ( objectType == GET_ENUM_VALUE(ObjectTypes::ENTITY) )
                {
                    auto u = object->m_position - m_associatedObject->m_position;
                    float distance = u.getMagnitude();
                    if (distance < lowestDistance)
                    {
                        lowestDistance = distance;
                        closestEnemy = object;
                    }
                }
            }
        );

        return closestEnemy;
    }

#ifdef _DEBUG
    void Player::debug ()
    {
        auto closestEnemy = getClosestEnemy();
        if (closestEnemy == nullptr) return;
        
        auto u = closestEnemy->m_position - m_associatedObject->m_position;
        u.normalize();
        
        /*Vector3<float> i(1.0f, 0.0f, 0.0f);
        u.m_z = 0;
        float fixedHorizontalAngle = std::acos( i.dot(u) );
        m_associatedObject->m_bodyHorizontalRotation = (
            (u.m_y > 0.0f) ? fixedHorizontalAngle : -fixedHorizontalAngle
        );
        m_associatedObject->m_bodyHorizontalRotation = fixedHorizontalAngle;*/

        // ...

        auto enemyPos = closestEnemy->m_position;
        auto myPos = m_associatedObject->m_position;
        auto myRot = m_associatedObject->m_bodyHorizontalRotation;
        
        std::cout << "My pos : (" << myPos.m_x << ", " << myPos.m_y <<
            ", " << myPos.m_z << ")" << std::endl;
        std::cout << "Enemy pos : (" << enemyPos.m_x << ", " << enemyPos.m_y <<
            ", " << enemyPos.m_z << ")" << std::endl;
        std::cout << "My rot : " << myRot << std::endl;
    }
#endif

}
