#pragma once
#include "filtrovanie.h"
#include "selectionCriterion_NajmensiaVekovaSkupina.h"
#include "selectionCriterion_NajvacsiaVekovaSkupina.h"

namespace func
{
	class VyberoveKriteria : public Filtrovanie
	{
	public:
		void spusti(uj::Stat* stat) override;
	private:
		scrits::SelectionCriterion<std::wstring, uj::UzemnaJednotka, int>* getSelCrit(std::wstring& moznost);
		void vypisTabulku(UST* filteredTab, scrits::SelectionCriterion<std::wstring, uj::UzemnaJednotka, int>* crit);
	};

	inline void VyberoveKriteria::spusti(uj::Stat* stat)
	{
		std::wcout << '\n' << L"------------------------------Výberové kritéria------------------------------" << '\n';

		auto tab = Funcionality::zvolUroven(stat);
		UST* filteredTab = nullptr;
		UST* scBestTable = nullptr;
		std::wstring moznost;

		auto scrit = getSelCrit(moznost);

		std::wcout << L"Budete chcie aj filtrova ? [A/N]: ";
		std::getline(std::wcin, moznost);
		if (moznost == L"A" || moznost == L"a") {
			filteredTab = Filtrovanie::filterTable(tab, moznost);
		}

		if (scrit != nullptr) {
			if (filteredTab != nullptr) {
				scBestTable = scrit->selectBest(filteredTab);
			}
			else {
				scBestTable = scrit->selectBest(tab);
			}

			vypisTabulku(scBestTable, scrit);
		}
		else {
			std::wcout << L"Ups...Nieèo sa pokazilo." << '\n' << '\n';
		}

		delete filteredTab;
		delete scBestTable;
		delete scrit;

		std::wcout << '\n' << L"-----------------------------------------------------------------------------" << '\n';
	}

	inline scrits::SelectionCriterion<std::wstring, uj::UzemnaJednotka, int>* VyberoveKriteria::getSelCrit(std::wstring& moznost)
	{
		std::wcout << '\n' << L"Vyberte si z nasledujúcich možností" << '\n';
		std::wcout << L"1 - najmenšia veková skupina" << '\n';
		std::wcout << L"2 - najväèšia veková skupina" << '\n';

		std::wcout << '\n' << L"Vo¾ba: ";
		std::getline(std::wcin, moznost);

		std::wstring vekSkupina;
		std::wcout << L"Veková skupina: ";
		std::getline(std::wcin, vekSkupina);

		if (moznost == L"1") {
			return new scrits::SelectionCriterionNajmensiaVekovaSkupina<std::wstring>(vekSkupina);
		}

		if (moznost == L"2") {
			return new scrits::SelectionCriterionNajvacsiaVekovaSkupina<std::wstring>(vekSkupina);
		}

		return nullptr;
	}

	inline void VyberoveKriteria::vypisTabulku(UST* filteredTab, scrits::SelectionCriterion<std::wstring, uj::UzemnaJednotka, int>* crit)
	{
		std::wcout << '\n' << L"-----------------------------------" << '\n';
		filteredTab->getItemAtIndex(0).accessData()->vypis();
		std::wcout << crit->getCriterion()->evaluate(*filteredTab->getItemAtIndex(0).accessData());
		std::wcout << '\n' << L"-----------------------------------" << '\n';
	}
}