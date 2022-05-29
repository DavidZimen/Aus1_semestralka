#pragma once
#include <iostream>
#include <string>
#include "../SemestralnaPraca_Zimen/structures/table/sorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/table/unsorted_sequence_table.h"
#include "../SemestralnaPraca_Zimen/structures/table/sequence_table.h"
#include "uzemna_jednotka.h"
#include "typ_uj.h"
#include "stat.h"

#define OBEC_MOZNOST 1
#define OKRES_MOZNOST 2
#define KRAJ_MOZNOST 3

namespace func
{
	class Funcionality
	{
	public:
		virtual void spusti(uj::Stat* stat) = 0;
		virtual ~Funcionality() {};

	protected:
		structures::SequenceTable<std::wstring, uj::UzemnaJednotka*>* zvolUroven(uj::Stat* stat);
		virtual structures::SequenceTable<std::wstring, uj::UzemnaJednotka*>* getTab(uj::Stat* stat, int moznost) = 0;
	};

	inline structures::SequenceTable<std::wstring, uj::UzemnaJednotka*>* Funcionality::zvolUroven(uj::Stat* stat)
	{
		std::wcout << L"Zadajte èíslo možnosti vyh¾adávania: 1 - OBEC  2 - OKRES  3 - KRAJ" << '\n';
		std::wcout << L"Vo¾ba: ";
		std::wstring volba;
		std::getline(std::wcin, volba);
		auto tab = this->getTab(stat, std::stoi(volba));


		while (tab == nullptr) {
			std::wcout << L"Nesprávna hodnota. Zadajte znova: ";
			std::wcin >> volba;
			std::wcout << '\n';
			auto tab = this->getTab(stat, std::stoi(volba));
		}

		return tab;
	}
}