#include <iostream>
#include <elevations.h>
#include <conio.h>

int main()
{
    DWORD pid = GetRotnProcessID();
    if (!pid) exit(1);
    std::cout << "Got pid !\n";

    HANDLE hRotn = GetRotnHandle(pid);
    if (!hRotn) exit(1);
    std::cout << "Got handle\n";

    void *moduleBaseAddr = GetRotnModuleBaseAdress(pid);
    if (!moduleBaseAddr) exit(1);
    std::cout << "Got module base adress\n";

    void *moneyObjAddr = GetRotnMoneyObjectAdress(hRotn, moduleBaseAddr);
    if (!moneyObjAddr) exit(1);
    std::cout << "got money object address\n";

    std::cout << "Press a key...\n";
    getch();
    std::cout << SetRotnMoney(hRotn, moneyObjAddr, 9500000);

}