#include <iostream>
#include <elevations.h>

int main()
{
    std::cout << GetRotnProcessID() << std::endl;
    std::cout << GetRotnHandle(GetRotnProcessID()) << std::endl;
}