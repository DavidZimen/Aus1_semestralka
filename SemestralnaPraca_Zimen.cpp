// SemestralnaPraca_Zimen.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include "../SemestralnaPraca_Zimen/loader.h"
#include "../SemestralnaPraca_Zimen/structures/heap_monitor.h"
#include "../SemestralnaPraca_Zimen/stat.h"
#include "bodove_Vyhladavanie.h"
#include "filtrovanie.h"
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"

#include <Windows.h>
#pragma execution_character_set("utf-8")

int main()
{
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    setlocale(LC_ALL, "slovak");

    std::wcout << L"---------------Aplikácia na spracovanie údajov zo Sčítania 2021--------------" << '\n';
    std::wcout << '\n';
    std::wcout << L"Pre vyhľadanie podľa vzdelania prosím napíšte jednu z nasledujúcich možností:" << '\n';
    std::wcout << L"'bez ukončeného vzdelania'" << '\n';
    std::wcout << L"'základné'" << '\n';
    std::wcout << L"'učňovské'" << '\n';
    std::wcout << L"'stredné'" << '\n';
    std::wcout << L"'vyššie'" << '\n';
    std::wcout << L"'vysokoškolské'" << '\n';
    std::wcout << L"'bez vzdelania'" << '\n';
    std::wcout << L"'nezistené'" << '\n';
    std::wcout << '\n';
    std::wcout << L"Pre voľbu vekovej skupiny prosím napíšte jednu z nasledujúcich možností:" << '\n';
    std::wcout << L"'predproduktívni' -> 0-14" << '\n';
    std::wcout << L"'produktívny' -> 15-64" << '\n';
    std::wcout << L"'poproduktívni' -> 65-100+" << '\n';
    std::wcout << '\n';
    std::wcout << L"Pre voľbu pohlavia prosím napíšte jednu z nasledujúcich možností:" << '\n';
    std::wcout << L"'muž'" << '\n';
    std::wcout << L"'žena'" << '\n';
    std::wcout << L"-----------------------------------------------------------------------------" << '\n';

    //auto statP = data_loading::Loader::getInstance().LoadData();

    //func::BodoveVyhladavanie bv;
    //bv.spusti(statP);

    //func::Filtrovanie f;
    //f.spusti(statP);

    //auto tab = statP->getObceU();
    auto tabFilt = new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>();
    auto crit = new crits::CriterionUJPrislusnost(L"Okres Sobrance");

    auto filter = new filter::FilterCriterionValue<std::wstring, uj::UzemnaJednotka, bool>(crit, true);
    uj::UzemnaJednotka* u1 = new uj::UzemnaJednotka(uj::TypUzemJednotka::OBEC, L"macka", L"macka", L"macka", L"macka");
    uj::UzemnaJednotka* u2 = new uj::UzemnaJednotka(uj::TypUzemJednotka::OKRES, L"Okres Sobrance", L"Okres Sobrance", L"Okres Sobrance", L"Okres Sobrance");

    u1->setNadradena(u2);
    
    //bool hodnota = crit.evaluate(*u1);
    //filter->filterTable(tab, tabFilt);

    delete u1;
    delete u2;
    delete tabFilt;
    delete filter;

    //delete statP;
    _CrtDumpMemoryLeaks();
}
