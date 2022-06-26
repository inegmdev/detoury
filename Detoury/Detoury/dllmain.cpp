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
    logger.write(); \
} 

/*****************************************************************************/
/*                                   HOOKS                                   */
/*****************************************************************************/

static HANDLE (* True_CreateFile)(
    LPCTSTR lpFileName,
    // pointer to name of the file
    DWORD dwDesiredAccess,
    // access (read-write) mode
    DWORD dwShareMode,
    // share mode
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    // pointer to security attributes
    DWORD dwCreationDistribution,
    // how to create
    DWORD dwFlagsAndAttributes,
    // file attributes
    HANDLE hTemplateFile
    // handle to file with attributes to copy
) = CreateFile;

static HANDLE Hook_CreateFile(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDistribution, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    Log("Created file name\n");
    return True_CreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDistribution, dwFlagsAndAttributes, hTemplateFile);
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
    
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        
        logger.init();
        logger.write();

        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&True_CreateFile, Hook_CreateFile);
        error = DetourTransactionCommit();     

        if (error == NO_ERROR) {
            Log("Detoury successfully hooked the functions.\n");
        }
        else {
            Log("[ERROR] Detoury failed to hook the functions, returns(%ld).\n", error);
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

