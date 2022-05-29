#pragma once
#include "filtrovanie.h"
#include "quickSorter.h"
#include "conversion.h"

namespace func
{
	class Triedenie : public Filtrovanie
	{
	protected:
		bool vzostupne_;

	public:
		Triedenie();
		virtual ~Triedenie();
		void spusti(uj::Stat* stat) override;

	private:
		void vyberKriterium(std::wstring& moznost, structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaNazvu(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaTypu(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaNadradenosti(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaPrislusnosti(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaVekPocet(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaVekPodiel(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaVekSkupinaPocet(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaVekSkupinaPodiel(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaVzdelaniePocet(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		void utriedPodlaVzdelaniePodiel(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab);
		bool zistiVzostupnost(std::wstring& moznost);
	};

	inline Triedenie::Triedenie() :
		vzostupne_(true)
	{
	}

	inline Triedenie:: ~Triedenie()
	{
	}

	inline void Triedenie::spusti(uj::Stat* stat)
	{
		std::wcout << '\n' << L"----------------------------------Triedenie----------------------------------" << '\n';

		auto tab = Funcionality::zvolUroven(stat);
		UST* filteredTab = nullptr;
		std::wstring moznost;

		
		std::wcout << L"Budete chcie aj filtrova ? [A/N]: ";
		std::getline(std::wcin, moznost);
		if (moznost == L"A" || moznost == L"a") {
			filteredTab = Filtrovanie::filterTable(tab, moznost);
		}

		if (filteredTab != nullptr) {
			vyberKriterium(moznost, filteredTab);
		}
		else if (tab != nullptr) {
			vyberKriterium(moznost, dynamic_cast<UST*>(tab));
		}

		delete filteredTab;

		std::wcout << '\n' << L"-----------------------------------------------------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaNazvu(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, std::wstring> sorter;
		crits::CriterionUJNazov kNazov;
		
		sorter.sort(*tab, kNazov, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kNazov.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaTypu(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, uj::TypUzemJednotka> sorter;
		crits::CriterionUJTyp kTyp;

		sorter.sort(*tab, kTyp, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << uj::Conversion::getInstance().toString(kTyp.evaluate(*item->accessData())) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaNadradenosti(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		/*sort::QuickSorter<std::wstring, uj::UzemnaJednotka, uj::UzemnaJednotka> sorter;
		crits::CriterionUJNadradena kNadradena;

		sorter.sort(*tab, kNadradena, vzostupne_);*/


	}

	inline void Triedenie::utriedPodlaPrislusnosti(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, bool> sorter;

		std::wstring vyssiCelok;

		std::wcout << L"Zadajte nazov príslušného vyššieho celku (napr. Žilinský kraj, Okres Žilina): ";
		std::getline(std::wcin, vyssiCelok);

		crits::CriterionUJPrislusnost kPrislusnost(vyssiCelok);

		sorter.sort(*tab, kPrislusnost, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kPrislusnost.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaVekPocet(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, int> sorter;

		std::wstring pohlavie, vek;

		std::wcout << L"Vek: ";
		std::getline(std::wcin, vek);
		std::wcout << L"Pohlavie: ";
		std::getline(std::wcin, pohlavie);

		crits::CriterionUJVekPocet kVekPocet(std::stoi(vek), pohlavie);

		sorter.sort(*tab, kVekPocet, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kVekPocet.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaVekPodiel(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, double> sorter;

		std::wstring pohlavie, vek;

		std::wcout << L"Vek: ";
		std::getline(std::wcin, vek);
		std::wcout << L"Pohlavie: ";
		std::getline(std::wcin, pohlavie);

		crits::CriterionUJVekPodiel kVekPodiel(std::stoi(vek), pohlavie);

		sorter.sort(*tab, kVekPodiel, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kVekPodiel.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaVekSkupinaPocet(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, int> sorter;

		std::wstring vekSkupina;

		std::wcout << L"Veková skupina: ";
		std::getline(std::wcin, vekSkupina);

		crits::CriterionUJVekovaSkupinaPocet kVekSkupinaPocet(vekSkupina);

		sorter.sort(*tab, kVekSkupinaPocet, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kVekSkupinaPocet.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaVekSkupinaPodiel(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, double> sorter;

		std::wstring vekSkupina;

		std::wcout << L"Veková skupina: ";
		std::getline(std::wcin, vekSkupina);

		crits::CriterionUJVekovaSkupinaPodiel kVekSkupinaPodiel(vekSkupina);

		sorter.sort(*tab, kVekSkupinaPodiel, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kVekSkupinaPodiel.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaVzdelaniePocet(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, int> sorter;

		std::wstring vzdelanie;

		std::wcout << L"Vzdelanie: ";
		std::getline(std::wcin, vzdelanie);

		crits::CriterionUJVzdelaniePocet kVzdelaniePocet(vzdelanie);

		sorter.sort(*tab, kVzdelaniePocet, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kVzdelaniePocet.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::utriedPodlaVzdelaniePodiel(structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{
		sort::QuickSorter<std::wstring, uj::UzemnaJednotka, double> sorter;

		std::wstring vzdelanie;

		std::wcout << L"Vzdelanie: ";
		std::getline(std::wcin, vzdelanie);

		crits::CriterionUJVzdelaniePodiel kVzdelaniePodiel(vzdelanie);

		sorter.sort(*tab, kVzdelaniePodiel, vzostupne_);

		std::wcout << '\n' << L"-----------------------------------" << '\n';
		for (auto item : *tab) {
			item->accessData()->vypis();
			std::wcout << kVzdelaniePodiel.evaluate(*item->accessData()) << '\n';
		}
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}

	inline void Triedenie::vyberKriterium(std::wstring& moznost, structures::UnsortedSequenceTable<std::wstring, uj::UzemnaJednotka*>* tab)
	{	
		vzostupne_ = zistiVzostupnost(moznost);

		std::wcout << L"Pod¾a èísla vyberte s dostupných kritérii" << '\n';
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
		std::getline(std::wcin, moznost);

		int volba = std::stoi(moznost);

		switch (volba) {
			case 1:
				utriedPodlaNazvu(tab);
				break;
			case 2:
				utriedPodlaPrislusnosti(tab);
				break;
			case 3:
				utriedPodlaTypu(tab);
				break;
			case 4:
				utriedPodlaVekPocet(tab);
				break;
			case 5:
				utriedPodlaVekPodiel(tab);
				break;
			case 6:
				utriedPodlaVekSkupinaPocet(tab);
				break;
			case 7:
				utriedPodlaVekSkupinaPodiel(tab);
				break;
			case 8:
				utriedPodlaVzdelaniePocet(tab);
				break;
			case 9:
				utriedPodlaVzdelaniePodiel(tab);
				break;
			default:
				break;
		}
		
	}

	inline bool Triedenie::zistiVzostupnost(std::wstring& moznost)
	{
		std::wcout << L"Chcete triedi vzostupne ? [A/N]: " << '\n';
		std::getline(std::wcin, moznost);

		if (moznost == L"A" || moznost == L"a") {
			return true;
		}

		return false;
	}
}