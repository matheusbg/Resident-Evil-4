#include "common.h"
#include "addresses.h"


namespace ResidentEvil4
{
    unsigned long g_playerAddress = 0x033F6EAC;

    unsigned long g_objectsArrayBaseAddress = g_playerAddress;
    unsigned long g_objectsArrayOffsetAddress = 0x033F6ED0;
    unsigned long g_objectsArraySizeAddress = 0x033F6ECC;

}