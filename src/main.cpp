#include "common.h"
#include "cheat-manager.h"
#include "d3d.h"


DWORD WINAPI unloadThread (LPVOID args)
{
    using namespace ResidentEvil4;

    D3D::getInstance().unhook ();

#ifdef _DEBUG
    Console::getInstance().detach ();
#endif

    FreeLibraryAndExitThread( (HMODULE)args, 0 );
    return 0;
}


DWORD WINAPI mainThread (LPVOID args)
{
    using namespace ResidentEvil4;
    
#ifdef _DEBUG
    /* Setup debugging console. */
    Console::getInstance().bind ("Resident Evil 4");
#endif

    D3D::getInstance().hook ();

    /* Cheat's loop. */
    CheatManager::getInstance().work();    

    /* Unload module (i.e. when the cheat manager stops working). */
    CreateThread(nullptr, 0, unloadThread, args, 0, nullptr);

    return 0;
}

BOOL WINAPI DllMain (
        HINSTANCE instance,
        DWORD reason,
        LPVOID reserved
    )
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(instance);
            CreateThread(nullptr, 0, mainThread, instance, 0, nullptr);
        }
        break;
    case DLL_THREAD_ATTACH:
        {
            //
        }
        break;
    case DLL_THREAD_DETACH:
        {
            //
        }
        break;
    case DLL_PROCESS_DETACH:
        {
            //
        }
        break;
    }

    return TRUE;
}
