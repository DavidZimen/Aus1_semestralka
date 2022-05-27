#pragma once
#include "funcionality.h"
#include "filter_UJ_Nazov.h"
#include "filter_UJ_Prislusnost.h"
#include "filter_UJ_Typ.h"
#include "filter_UJ_VekovaSkupinaPocet.h"
#include "filter_UJ_VekovaSkupinaPodiel.h"
#include "filter_UJ_VekPocet.h"
#include "filter_UJ_VekPodiel.h"
#include "filter_UJ_VzdelaniePocet.h"
#include "filter_UJ_VzdelaniePodiel.h"
#include "filter_Composite_AND.h"
#include "filter_Composite_OR.h"
#include "criterion_UJ_Nazov.h"
#include "criterion_UJ_Nadradena.h"
#include "criterion_UJ_Prislusnost.h"
#include "criterion_UJ_Typ.h"
#include "criterion_UJ_VekPocet.h"
#include "criterion_UJ_VekPodiel.h"
#include "criterion_UJ_VekovaSkupinaPocet.h"
#include "criterion_UJ_VekovaSkupinaPodiel.h"
#include "criterion_UJ_VzdelaniePocet.h"
#include "criterion_UJ_VzdelaniePodiel.h"


namespace func
{
	class Filtrovanie : public virtual Funcionality
	{
	public:
		void spusti(uj::Stat* stat) override;
	protected:
		filter::Filter<std::wstring, uj::UzemnaJednotka>* vyberFilter();
		filter::Filter<std::wstring, uj::UzemnaJednotka>* getNazov();
		filter::Filter<std::wstring, uj::UzemnaJednotka>* getPrislusnost();
		filter::Filter<std::wstring, uj::UzemnaJednotka>* getTyp();
		filter::Filter<std::wstring, uj::UzemnaJednotka>* getVek(int volba);
		filter::Filter<std::wstring, uj::UzemnaJednotka>* getVekSkup(int volba);
		filter::Filter<std::wstring, uj::UzemnaJednotka>* getVzdel(int volba);
		structures::SequenceTable<std::wstring, uj::UzemnaJednotka*>* getTab(uj::Stat* stat, int moznost) override;
		void vypisTabulku(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* filteredTab);
	private:
		void getMinMax(std::wstring& min, std::wstring& max);
	};

	inline void Filtrovanie::spusti(uj::Stat* stat)
	{
		auto tab = Funcionality::zvolUroven(stat);
		std::wstring volba;
		std::wcout << L"Chcete zložený filter ? [A/N]: ";
		std::getline(std::wcin, volba);
		std::wcout << '\n';

		if (volba == L"A" || volba == L"a") {
			std::wcout << L"AND alebo OR filter ? [and/or]: ";
			std::getline(std::wcin, volba);
			std::wcout << '\n';

			if (volba == L"and") {
				auto filter = new filter::FilterCompositeAND<std::wstring, uj::UzemnaJednotka>();
				filter->registerFilter(vyberFilter());

				bool dalsi = true;
				while (dalsi) {
					std::wcout << L"Registrova ïalší ? [A/N]: ";
					std::getline(std::wcin, volba);

					if (volba == L"A" || volba == L"a") {
						filter->registerFilter(vyberFilter());
						dalsi = true;
					}
					else {
						dalsi = false;
					}
				}

				auto filteredTab = new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>();

				filter->filterTable(tab, filteredTab);
				vypisTabulku(filteredTab);

				delete filter;
				delete filteredTab;
				
			}
			else if (volba == L"or") {
				auto filter = new filter::FilterCompositeOR<std::wstring, uj::UzemnaJednotka>();
				filter->registerFilter(vyberFilter());

				bool dalsi = true;
				while (dalsi) {
					std::wcout << L"Registrova ïalší ? [A/N]: ";
					std::getline(std::wcin, volba);

					if (volba == L"A" || volba == L"a") {
						filter->registerFilter(vyberFilter());
						dalsi = true;
					}
					else {
						dalsi = false;
					}
				}

				auto filteredTab = new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>();

				filter->filterTable(tab, filteredTab);
				vypisTabulku(filteredTab);

				delete filter;
				delete filteredTab;
			}
		}
		else if (volba == L"N" || volba == L"n") {
			auto filter = vyberFilter();
			//filter::FilterUJVekPocet<std::wstring> filter(100, L"žena", 1, 15);
			//auto crit = new crits::CriterionUJVekPocet(100, L"žena");
			//filter::FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int> filter(crit, 1, 15);
			auto filteredTab = new structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>();
			
			filter->filterTable(tab, filteredTab);
			vypisTabulku(filteredTab);

			//delete dynamic_cast<filter::FilterCriterion<std::wstring, uj::UzemnaJednotka, int>*>(filter);
			delete filter;
			delete filteredTab;
		}

		std::wcout << L"Znova ? [A/N]: ";
		std::getline(std::wcin, volba);

		if (volba == L"A" || volba == L"a") {
			spusti(stat);
		}
	}

	inline filter::Filter<std::wstring, uj::UzemnaJednotka>* Filtrovanie::vyberFilter()
	{
		std::wcout << L"Pod¾a èísla vyberte s dostupných filtrov" << '\n';
		std::wcout << L"1 - UJ Názov" << '\n';
		std::wcout << L"2 - UJ Príslušnos" << '\n';
		std::wcout << L"3 - UJ Typ" << '\n';
		std::wcout << L"4 - UJ Vek Poèet" << '\n';
		std::wcout << L"5 - UJ Vek Podiel" << '\n';
		std::wcout << L"6 - UJ Veková skupina Poèet" << '\n';
		std::wcout << L"7 - UJ Veková skupina Podiel" << '\n';
		std::wcout << L"8 - UJ Vzdelanie Poèet" << '\n';
		std::wcout << L"9 - UJ Vzdelanie Podiel" << '\n';

		std::wcout << L"Vo¾ba: ";
		std::wstring moznost;
		std::getline(std::wcin, moznost);

		switch (std::stoi(moznost)) {
			case 1:
				return getNazov();
			case 2:
				return getPrislusnost();
			case 3:
				return getTyp();
			case 4:
				return getVek(4);
			case 5:
				return getVek(5);
			case 6:
				return getVekSkup(6);
			case 7:
				return getVekSkup(7);
			case 8:
				return getVzdel(8);
			case 9:
				return getVzdel(9);
			default:
				return nullptr;
		}
	}

	inline filter::Filter<std::wstring, uj::UzemnaJednotka>* Filtrovanie::getNazov()
	{
		std::wstring nazov;

		std::wcout << L"Zadajte nazov jednotky: ";
		std::getline(std::wcin, nazov);


		return new filter::FilterUJNazov<std::wstring>(nazov);
	}

	inline filter::Filter<std::wstring, uj::UzemnaJednotka>* Filtrovanie::getPrislusnost()
	{
		std::wstring vyssiCelok, maPatrit;

		std::wcout << L"Zadajte nazov príslušného vyššieho celku (napr. Žilinský kraj, Okres Žilina): ";
		std::getline(std::wcin, vyssiCelok);

		std::wcout << L"Má tam patri ? [A/N]: ";
		std::getline(std::wcin, maPatrit);


		if (maPatrit == L"A" || maPatrit == L"a") {
			return new filter::FilterUJPrislusnost<std::wstring>(true, vyssiCelok);
		}
		else {
			return new filter::FilterUJPrislusnost<std::wstring>(false, vyssiCelok);
		}
	}

	inline filter::Filter<std::wstring, uj::UzemnaJednotka>* Filtrovanie::getTyp()
	{
		std::wstring volba;
		bool spravne = false;

		std::wcout << L"Vyberte z nasledujúcivh možností: " << '\n';
		std::wcout << L"1 - OBEC " << '\n';
		std::wcout << L"2 - OKRES " << '\n';
		std::wcout << L"3 - KRAJ " << '\n';

		while (!spravne) {
			std::wcout << L"Vo¾ba: ";
			std::getline(std::wcin, volba);
			if (std::stoi(volba) == 1 || std::stoi(volba) == 2 || std::stoi(volba) == 3) {
				spravne = true;
			}
			else {
				std::wcout << L"Zadajte znova. Dodržte možnosti." << '\n';
			}
		}

		switch (std::stoi(volba)) {
			case 1:
				return new filter::FilterUJTyp<std::wstring>(uj::TypUzemJednotka::OBEC);
			case 2:
				return new filter::FilterUJTyp<std::wstring>(uj::TypUzemJednotka::OKRES);
			case 3:
				return new filter::FilterUJTyp<std::wstring>(uj::TypUzemJednotka::KRAJ);
			default:
				return nullptr;
		}
	}

	inline filter::Filter<std::wstring, uj::UzemnaJednotka>* Filtrovanie::getVek(int volba)
	{
		std::wstring pohlavie, vek, min, max;
		bool spravne = false;

		std::wcout << L"Vek: ";
		std::getline(std::wcin, vek);
		std::wcout << L"Pohlavie: ";
		std::getline(std::wcin, pohlavie);


		getMinMax(min, max);

		if (volba == 4) {
			return new filter::FilterUJVekPocet<std::wstring>(std::stoi(vek), pohlavie, std::stoi(min), std::stoi(max));
		}
		else if (volba == 5) {
			return new filter::FilterUJVekPodiel<std::wstring>(std::stoi(vek), pohlavie, std::stoi(min), std::stoi(max));
		}
		else {
			return nullptr;
		}
		
		//return new filter::FilterCriterionInterval<std::wstring, uj::UzemnaJednotka, int>(new crits::CriterionUJVekPocet(std::stoi(vek), pohlavie), std::stoi(min), std::stoi(max));
	}

	inline filter::Filter<std::wstring, uj::UzemnaJednotka>* Filtrovanie::getVekSkup(int volba)
	{
		std::wstring vekSkupina, min, max;
		bool spravne = false;
		std::wcout << L"Veková skupina: ";
		std::getline(std::wcin, vekSkupina);

		getMinMax(min, max);

		if (volba == 6) {
			return new filter::FilterUJVekovaSkupinaPocet<std::wstring>(vekSkupina, std::stoi(min), std::stoi(max));
		}
		else if (volba == 7) {
			return new filter::FilterUJVekovaSkupinaPodiel<std::wstring>(vekSkupina, std::stoi(min), std::stoi(max));
		}
		else {
			return nullptr;
		}
	}


	inline filter::Filter<std::wstring, uj::UzemnaJednotka>* Filtrovanie::getVzdel(int volba)
	{
		std::wstring vzdelanie, min, max;
		bool spravne = false;
		std::wcout << L"Vzdelanie: ";
		std::getline(std::wcin, vzdelanie);

		getMinMax(min, max);

		if (volba == 8) {
			return new filter::FilterUJVzdelaniePocet<std::wstring>(vzdelanie, std::stoi(min), std::stoi(max));
		}
		else if (volba == 9) {
			return new filter::FilterUJVzdelaniePodiel<std::wstring>(vzdelanie, std::stoi(min), std::stoi(max));
		}
		else {
			return nullptr;
		}
	}


	inline structures::SequenceTable<std::wstring, uj::UzemnaJednotka*>* Filtrovanie::getTab(uj::Stat* stat, int moznost)
	{
		switch (moznost) {
			case OBEC_MOZNOST:
				return stat->getObceU();
			case OKRES_MOZNOST:
				return stat->getOkresyU();
			case KRAJ_MOZNOST:
				return stat->getKrajeU();
			default:
				return nullptr;
		}
	}

	inline void Filtrovanie::vypisTabulku(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* filteredTab)
	{
		for (auto uj : *filteredTab) {
			uj->accessData()->vypis();
		}
	}

	inline void Filtrovanie::getMinMax(std::wstring& min, std::wstring& max)
	{
		bool spravne = false;
		while (!spravne) {
			std::wcout << L"Minimum: ";
			std::getline(std::wcin, min);
			std::wcout << L"Maximum: ";
			std::getline(std::wcin, max);

			if (std::stoi(min) >= 0 && std::stoi(min) < std::stoi(max)) {
				spravne = true;
			}
			else {
				std::wcout << L"Zle zadané hodnoty minima a maxima. Znova" << '\n';
			}
		}
	}
}