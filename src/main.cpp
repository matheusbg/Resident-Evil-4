#include "common.h"
#include "cheat-manager.h"


unsigned long __stdcall unloadThread (void* args)
{
    FreeLibraryAndExitThread(static_cast<HMODULE>(args), 0);
    return 0;
}


unsigned long __stdcall mainThread (void* args)
{
    using namespace ResidentEvil4;
    
    /* Cheat's loop. */
    CheatManager cheatManager;
    cheatManager.work();    

    /* Unload module (i.e. when the cheat manager stops working). */
    CreateThread(NULL, NULL, unloadThread, args, NULL, NULL);

    return 0;
}

bool __stdcall DllMain (
        HINSTANCE instance,
        unsigned long reason,
        void* reserved
    )
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(instance);
            CreateThread(NULL, NULL, mainThread, instance, NULL, NULL);
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
    default:
        break;
    }

    return true;
}
