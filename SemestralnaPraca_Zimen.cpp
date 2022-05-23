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
    SetConsoleOutputCP(65001);
    auto statP = new uzemne_jednotky::Stat();
    delete statP;
}
