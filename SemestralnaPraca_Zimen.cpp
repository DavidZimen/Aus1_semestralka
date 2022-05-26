// SemestralnaPraca_Zimen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include "../SemestralnaPraca_Zimen/loader.h"
#include "../SemestralnaPraca_Zimen/structures/heap_monitor.h"
#include "../SemestralnaPraca_Zimen/stat.h"

#include <Windows.h>
#pragma execution_character_set("utf-8")

int main()
{
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    setlocale(LC_ALL, "slovak");
    auto statP = data_loading::Loader::getInstance().LoadData();
    delete statP;

    _CrtDumpMemoryLeaks();
}
