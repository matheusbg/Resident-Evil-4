#include "common.h"
#include "cheat-manager.h"


unsigned long __stdcall exitThread(void* args)
{
    FreeLibraryAndExitThread(static_cast<HMODULE>(args), 0);
    return 0;
}


unsigned long __stdcall mainThread(void* args)
{
    ResidentEvil4::CheatManager cheatManager;
    cheatManager.work();
    
    // We get here when the cheat manager stops working.
    //
    CreateThread(NULL, NULL, exitThread, args, NULL, NULL);
    return 0;
}

bool __stdcall DllMain(
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