#define NOMINMAX
#include <Windows.h>

#include "valve_sdk/sdk.hpp"
#include "helpers/utils.hpp"

#include "hooks/hooks.hpp"
#include "options.hpp"
#include "helpers/input.hpp"
#include "menu/menu.hpp"
#include "features/bullettracers.hpp"

bool Unload = false;
DWORD WINAPI OnDllAttach(LPVOID base)
{
    // 
    // Wait at most 10s for the main game modules to be loaded.
    // 
    if (Utils::WaitForModules(10000, { L"client_panorama.dll", L"engine.dll", L"shaderapidx9.dll" }) == WAIT_TIMEOUT) {
        // One or more modules were not loaded in time
        return FALSE;
    }

#ifdef _DEBUG
    Utils::AttachConsole();
#endif

    try {
        Utils::ConsolePrint("Initializing...\n");

        Interfaces::Initialize();
        Interfaces::Dump();

        //CvarVariables();

        NetvarSys::Get().Initialize();
        InputSys::Get().Initialize();
        Menu::Get().Initialize();
        Hooks::Initialize();
        g_Event.RegisterSelf();
        BulletBeamsEvent::Get().RegisterSelf();
        InputSys::Get().RegisterHotkey(VK_INSERT, [base]() {
            Menu::Get().Toggle();
            });
        InputSys::Get().RegisterHotkey(VK_END, [base]() {
            Unload = true;
            });
        // Register some hotkeys.
        // - Note:  The function that is called when the hotkey is pressed
        //          is called from the WndProc thread, not this thread.
        // 

        Utils::ConsolePrint("Finished.\n");

        while (!Unload)
            Sleep(1000);

        g_CVar->FindVar("crosshair")->SetValue(true);

        FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);

    }
    catch (const std::exception& ex) {
        Utils::ConsolePrint("An error occured during initialization:\n");
        Utils::ConsolePrint("%s\n", ex.what());
        Utils::ConsolePrint("Press any key to exit.\n");
        Utils::ConsoleReadKey();
        Utils::DetachConsole();

        FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
    }

    // unreachable
    //return TRUE;
}

BOOL WINAPI OnDllDetach()
{
#ifdef _DEBUG
    Utils::DetachConsole();
#endif

    Menu().Shutdown();
    return TRUE;
}

BOOL WINAPI DllMain(
    _In_      HINSTANCE hinstDll,
    _In_      DWORD     fdwReason,
    _In_opt_  LPVOID    lpvReserved
)
{
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDll);
        CreateThread(nullptr, 0, OnDllAttach, hinstDll, 0, nullptr);
        return TRUE;
    case DLL_PROCESS_DETACH:
        if (lpvReserved == nullptr)
            return OnDllDetach();
        return TRUE;
    default:
        return TRUE;
    }
}




























































