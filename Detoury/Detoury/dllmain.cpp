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

/*****************************************************************************/
/*                             GLOBAL VARIABLES                              */
/*****************************************************************************/
int hFile = 0;

/*****************************************************************************/
/*                             HELPER FUNCTIONS                              */
/*****************************************************************************/

/* Needed to be used so that the dll library can be used with `withdll` */
__declspec(dllexport) void ordinal_1() {}

/* Logging */
#define Log(...) { \
    char buffer[100]; \
	/*memset(buffer, 0, sizeof(buffer));*/							\
	int len = sprintf_s(buffer, 100, __VA_ARGS__);					\
	int bytesWritten = 0;											\
	/** Sanity checks */											\
	if (bytesWritten == -1) {										\
		MessageBox(													\
			HWND_DESKTOP,											\
			L"Failed to write to the log file.", L"DetoursHooks",	\
			MB_OK													\
		);															\
	}																\
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
    errno_t err;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        
        DetourRestoreAfterWith();
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&True_CreateFile, Hook_CreateFile);
        error = DetourTransactionCommit();
        
        /** Create a logging file for all the hooked APIs */
        err = _sopen_s(
            & hFile,
            "C:/Users/inegm/Desktop/detours2.log",
            _O_APPEND | _O_CREAT | _O_RDWR,
            _SH_DENYNO, _S_IREAD | _S_IWRITE
        );
        /** Sanity checks */
        if (0 != err) {
        /** Failed to create the file */
            MessageBoxA(
                HWND_DESKTOP,
                "Failed to create the log file.", "Detoury",
                MB_OK
            );
        }

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
        /** Close the handle of the file */
        _close(hFile);
        break;
    }
    return TRUE;
}

