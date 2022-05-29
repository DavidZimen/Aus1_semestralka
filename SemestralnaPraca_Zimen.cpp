#include <string>
#include <iostream>
#include "loader.h"
#include "stat.h"
#include "bodove_Vyhladavanie.h"
#include "vyberove_Kriteria.h"
#include "filtrovanie.h"
#include "triedenie.h"
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/heap_monitor.h"

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

    auto statP = data_loading::Loader::getInstance().LoadData();

    bool koniec = false;

    std::wcout << '\n' << L"Zvoľte si funkcionalitu na otestovanie" << '\n';
    std::wcout << L"1 - Bodové vyhľadávanie" << '\n';
    std::wcout << L"2 - Filtorovanie" << '\n';
    std::wcout << L"3 - Triedenie" << '\n';
    std::wcout << L"4 - Výberové kritéria" << '\n';
    std::wcout << L"K - koniec" << '\n';
    
    std::wstring volba;
    func::BodoveVyhladavanie bv;
    func::Filtrovanie f;
    func::Triedenie tr;
    func::VyberoveKriteria vk;


    while (!koniec) {
        std::wcout << '\n' << L"Zvolená funkcionalita: ";
        std::getline(std::wcin, volba);
        std::wcout << '\n';

        if (volba == L"1") {
            bv.spusti(statP);
            koniec = false;
        }
        else if (volba == L"2") {
            f.spusti(statP);
            koniec = false;
        }
        else if (volba == L"3") {
            tr.spusti(statP);
            koniec = false;
        }
        else if (volba == L"4") {
            vk.spusti(statP);
            koniec = false;
        }
        else if (volba == L"K") {
            koniec = true;
        }
        else {
            std::wcout << L"Nesprávny výber." << '\n';
            koniec = false;
        }
    }

    delete statP;
    _CrtDumpMemoryLeaks();
}