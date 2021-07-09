#ifndef ELEVATIONS_INCLUDED
#define ELEVATIONS_INCLUDED

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#pragma comment(lib, "psapi.lib")

DWORD GetRotnProcessID();
HANDLE GetRotnHandle(DWORD pidRotn);
void *GetRotnModuleBaseAdress(DWORD pidRotn);
void *GetRotnMoneyObjectAdress(HANDLE hRotn, void *rotnModuleBaseAdress);
BOOL SetRotnMoney(HANDLE hRotn, void *rotnMoneyObjectAdress, INT32 money);


#endif