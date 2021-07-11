#include <elevations.h>
#include <gui.h>

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
    
    DWORD pid = GetRotnProcessID();
    if (!pid) DisplayError(0);
    
    HANDLE hRotn = GetRotnHandle(pid);
    if (!hRotn) DisplayError(1);

    void *moduleBaseAddr = GetRotnModuleBaseAdress(pid);
    if (!moduleBaseAddr) DisplayError(2);

    void *moneyObjAddr = GetRotnMoneyObjectAdress(hRotn, moduleBaseAddr);
    if (!moneyObjAddr) DisplayError(3);

    return RunMainLoop(hRotn, moneyObjAddr);
}