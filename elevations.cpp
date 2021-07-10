#include <elevations.h>

DWORD GetRotnProcessID()
{
    DWORD arrProcessId[512], nbProcesses, nbModules;
    HANDLE hProcess;
    HMODULE hModule;
    WCHAR strProcessName[MAX_PATH]; 

    K32EnumProcesses(arrProcessId, sizeof(arrProcessId), &nbProcesses);
    nbProcesses /= sizeof(DWORD);

    for (UINT16 i = 0; i < nbProcesses; i++)
    {
        if (arrProcessId[i])
        {
            hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, arrProcessId[i]);
            if (hProcess)
            {
                if( K32EnumProcessModules(hProcess, &hModule, sizeof(hModule), &nbModules) )
                {
                    if ( K32GetModuleBaseNameW(hProcess, hModule, strProcessName, sizeof(strProcessName)))
                    {
                        if (!_wcsicmp(strProcessName, L"BloodstainedRotN-Win64-Shipping.exe"))
                        {
                            CloseHandle(hProcess);
                            return arrProcessId[i];
                        }
                    }
                }
                CloseHandle(hProcess);
            }
        }
    }

    return (DWORD) 0;   //fails to get RotN PID (cause: The game is not opened)
}

HANDLE GetRotnHandle(DWORD pidRotn)
{
    return OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pidRotn);     //might fail if the app is not in admin mode
}

void *GetRotnModuleBaseAdress(DWORD pidRotn)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pidRotn);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32W mdlEntry;
        mdlEntry.dwSize = sizeof(MODULEENTRY32W);
        if (Module32FirstW(hSnapshot, &mdlEntry))
        {
            do
            {
                if (!_wcsicmp(mdlEntry.szModule, L"BloodstainedRotN-Win64-Shipping.exe"))
                {
                    CloseHandle(hSnapshot);
                    return (void*) mdlEntry.modBaseAddr;
                }

            }while (Module32NextW(hSnapshot, &mdlEntry));
        }
    }
    CloseHandle(hSnapshot);
    return NULL;
}

void *GetRotnMoneyObjectAdress(HANDLE hRotn, void *rotnModuleBaseAdress)
{
    void *objAddr = NULL;
    SIZE_T nbRead = 0;
    ReadProcessMemory(hRotn, (const void*)((DWORD64)rotnModuleBaseAdress + 0x6F91F60), &objAddr, sizeof(void*), &nbRead);
    return objAddr;
}

BOOL SetRotnMoney(HANDLE hRotn, void *rotnMoneyObjectAdress, INT32 money)
{
    SIZE_T nbWritten;
    return WriteProcessMemory(hRotn, (void*)((DWORD64)rotnMoneyObjectAdress + 0x2B0), (const void*)&money, sizeof(INT32), &nbWritten);
}

INT32 GetRotnMoney(HANDLE hRotn, void *rotnMoneyObjectAdress)
{
    INT32 money;
    SIZE_T nbRead;
    ReadProcessMemory(hRotn, (void*)((DWORD64)rotnMoneyObjectAdress + 0x2B0), (void*) &money, sizeof(INT32), &nbRead);
    return money;
}