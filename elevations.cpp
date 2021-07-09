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
                        if (!_wcsicmp(strProcessName, L"BloodstainedRotN-Win64-Shipping.exe")) return arrProcessId[i];
                    }
                }
            }
        }
    }

    return (DWORD) 0;   //fails to get RotN PID (cause: The game is not opened)
}

HANDLE GetRotnHandle(DWORD pidRotn)
{
    return OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pidRotn);     //might fail if the app is not in admin mode
}

