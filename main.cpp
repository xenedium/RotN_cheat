#include <iostream>
#include <elevations.h>

int main()
{
    DWORD pid = GetRotnProcessID();
    HANDLE hRotn = GetRotnHandle(pid);
    void *moduleBaseAddr = GetRotnModuleBaseAdress(pid);

    std::cout << moduleBaseAddr << "\n" << GetRotnMoneyObjectAdress(hRotn, moduleBaseAddr) << std::endl;
}