/*****************************************************************************/
/*                                 INCLUDES                                  */
/*****************************************************************************/
#include <Windows.h>
#include "pch.h"
#include "detours.h"
#include <cstdio>
#include <io.h>
#include <sstream>
#include <fcntl.h>

#include "Logger.h"

/*****************************************************************************/
/*                             GLOBAL VARIABLES                              */
/*****************************************************************************/
Logger logger;

/*****************************************************************************/
/*                             HELPER FUNCTIONS                              */
/*****************************************************************************/

/* Needed to be used so that the dll library can be used with `withdll` */
__declspec(dllexport) void ordinal_1() {}

/* Logging */
#define Log(...) {  \
    logger.write(__VA_ARGS__); \
}

/*****************************************************************************/
/*                                   HOOKS                                   */
/*****************************************************************************/

static HANDLE (*True_CreateFileA) (
  LPCSTR                lpFileName,
  DWORD                 dwDesiredAccess,
  DWORD                 dwShareMode,
  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
  DWORD                 dwCreationDisposition,
  DWORD                 dwFlagsAndAttributes,
  HANDLE                hTemplateFile
) = CreateFileA;

static HANDLE Hook_CreateFileA(
    LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes, HANDLE hTemplateFile
    ) {
    Log("{{ 'HookedFunction': 'Create_File', 'Parameters': {{ 'lpFileName': '{}', 'dwDesiredAccess': '{}', 'dwShareMode': '{}', 'dwCreationDisposition': '{}', 'dwFlagsAndAttributes': '{}' }} }}",
                                                           lpFileName   ,      dwDesiredAccess,         dwShareMode,         dwCreationDisposition,         dwFlagsAndAttributes);
    return True_CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

/*****************************************************************************/
/*                                   MAIN                                    */
/*****************************************************************************/
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    LONG error;
    std::string s;
    
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        
        /* Logger Initialization */
        logger.init();
        Log("'Started logging'");

        /* Microsoft Detours Initialization */
        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&True_CreateFileA, Hook_CreateFileA);
        error = DetourTransactionCommit();     

        if (error == NO_ERROR) {
            Log("'Detoury successfully hooked the functions.'");
        }
        else {
            Log("'[ERROR] Detoury failed to hook the functions, returns {}.'", error);
        }


        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

