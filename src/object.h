#ifndef OBJECT_H
#define OBJECT_H

#include "vector.h"


namespace ResidentEvil4
{
    class Object
    {
    public:
        friend class Player;

    protected:
        /* Change this hack-ish way of detecting enemies later. */
        /* TODO: add more object types. */
        enum class ObjectTypes
        {
            ENTITY = 0x009D3558,
        };
        
        typedef struct ArmsInformation
        {
            unsigned char gap[0x28];
            float verticalRotation, horizontalRotation;
        } ArmsInformation;


        unsigned char gap1[0x30];
        Vector3<float> m_direction;         // 0x30

        unsigned char gap2[0x84];
        Vector3<float> m_position;          // 0xC0

        unsigned char gap3[0x8];
        float m_bodyHorizontalRotation;     // 0xD4

        unsigned char gap4[0x328];
        unsigned long* m_unknownPtr;        // 0x400

        bool m_isHitted;                    // 0x404

        unsigned char gap5[0x1];
        unsigned char m_weaponTypeHittedBy; // 0x406

        unsigned char gap6[0x4C9];
        ArmsInformation* m_armsInformation; // 0x8D0

    private:

    };

}

#endif