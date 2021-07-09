#ifndef ELEVATIONS_INCLUDED
#define ELEVATIONS_INCLUDED

#include <Windows.h>
#include <Psapi.h>
#pragma comment(lib, "psapi.lib")

DWORD GetRotnProcessID();
HANDLE GetRotnHandle(DWORD pidRotn);


#endif