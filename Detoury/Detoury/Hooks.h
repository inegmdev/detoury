#pragma once

#include <Windows.h>

/* Logging */
#define Log(...) {  \
    logger.write(__VA_ARGS__); \
}

/*****************************************************************************/
/*                                   HOOKS                                   */
/*****************************************************************************/

static HANDLE(*True_CreateFileA) (
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
        lpFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, dwFlagsAndAttributes);
    return True_CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}
