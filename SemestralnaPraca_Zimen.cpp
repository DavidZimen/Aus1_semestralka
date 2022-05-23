// SemestralnaPraca_Zimen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include "../SemestralnaPraca_Zimen/main.h"

#include <Windows.h>
#pragma execution_character_set("utf-8")

int main()
{
    SetConsoleOutputCP(65001);
    auto statP = new hlavny::Main();
    delete statP;
}
